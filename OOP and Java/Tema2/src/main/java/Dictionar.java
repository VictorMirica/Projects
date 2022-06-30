import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import java.io.File;
import java.io.IOException;
import java.io.Reader;
import java.io.Writer;
import java.nio.file.Files;
import java.util.*;

public class Dictionar {



    // Metoda care citeste cuvintele dintr-un dictionar (json)
    private ArrayList<Word> readFromJson(File file){

        List<Word> wList;

        try {
            Reader reader = Files.newBufferedReader(file.toPath());
            Word[] words = new Gson().fromJson(reader, Word[].class);
            reader.close();
            if(words == null)
                return null;
            wList = Arrays.asList(words);
        } catch (IOException e) {
            System.out.println("No such file");
            return null;
        }

        return new ArrayList<>(wList);
    }

    // Metoda care citeste cuvintele din toate dictionarele,
    // folosita pentru a initializa un LinkedHashMap
    private LinkedHashMap<String, ArrayList<Word>> readAllWords(){

        LinkedHashMap<String, ArrayList<Word>> map = new LinkedHashMap<>();
        File dirPath = new File("dict");
        File[] files = dirPath.listFiles();

        assert files != null;
        for(File file : files) {

            String language = file.getName().substring(0,2);
            ArrayList<Word> wList = readFromJson(file);

            // Se poate ca dictionarul sa fie gol
            if(wList == null)
                continue;

            // Adaugam in map cuvintele citite
            map.put(language,wList);
        }

        return map;
    }

    // Intializam colectia cuvintelor. O vom folosi in urmatoarele metode
    LinkedHashMap<String, ArrayList<Word>> wordMap = readAllWords();

    // Metoda care adauga un cuvant in dictionar
    boolean addWord(Word word, String language){

        ArrayList<Word> wordList = wordMap.get(language);

        // Testam daca exista deja cuvantul
        if(wordList != null)
            for(Word w : wordList){

                // In cazul in care gasim cuvantul, vedem daca acesta este identic
                // sau daca trebuie modificat (adaugare/modificare de definitii/sinonime).
                if(w.getWord().equals(word.getWord())) {
                    boolean modified = false;
                    for (Definition definition : word.getDefinitions()) {
                        if(addDefinitionForWord(word.getWord(), language, definition))
                            modified = true;
                    }
                    return modified;
                }
            }

        // In cazul in care nu exista, il adaugam listei
        if(wordList == null)
            wordList = new ArrayList<>();
        wordList.add(word);

        // Cazul in care trebuie sa adaugam un cuvant dintr-o limba noua
        if(!wordMap.containsKey(language))
            wordMap.put(language,wordList);

        return true;
    }

    // Metoda care sterge un cuvant din dictionar
    boolean removeWord(String word, String language){

        ArrayList<Word> wordList = wordMap.get(language);
        boolean found = false;

        // Cautam cuvantul in lista
        if(wordList != null)
            for(Word w : wordList){
                if(w.getWord().equals(word)) {

                    // Am gasit cuvantul, il eliminam
                    wordList.remove(w);
                    found = true;
                    break;
                }
            }

        return found;
    }

    // Metoda care adauga o definitie noua unui cuvant
    boolean addDefinitionForWord(String word, String language, Definition definition){

        ArrayList<Word> wordList = wordMap.get(language);
        boolean found = false;

        // Cautam cuvantul in lista
        if(wordList != null)
            for(Word w : wordList){
                if(w.getWord().equals(word)) {

                    // Am gasit cuvantul
                    found = true;

                    // Testam daca exista deja o definitie din acelasi dictionar
                    for(Definition def : w.getDefinitions()) {
                        if (def.getDict().equals(definition.getDict()) &&
                            def.getDictType().equals(definition.getDictType()) &&
                            def.getYear() == definition.getYear())

                            // Daca dictionarul este acelasi, vedem daca trebuie adaugat textul la lista deja existenta
                                if(def.getText().containsAll(definition.getText())){
                                    return false;
                                }else{
                                    def.getText().removeAll(definition.getText());
                                    def.getText().addAll(definition.getText());
                                    return true;
                                }
                    }

                    // Adaugam definitia
                    w.getDefinitions().add(definition);
                    break;
                }
            }

        return found;
    }

    // Metoda pentru stergerea unei definitii a unui cuvant
    // String-ul dictionary va fi de forma: nume_an_tip (ex: Dictonar de Sinonime_2002_definitions)
    boolean removeDefinition(String word, String language, String dictionary){

        ArrayList<Word> wordList = wordMap.get(language);
        boolean found = false;
        String[] dict = dictionary.split("_");

        // Cautam cuvantul in lista
        if(wordList != null)
            for(Word w : wordList) {
                if (w.getWord().equals(word)) {

                    // Am gasit cuvantul
                    // Cautam definitia care trebuie stearsa
                    for (Definition def : w.getDefinitions()) {
                        if (def.getDict().equals(dict[0]) && def.getYear() == Integer.parseInt(dict[1]) && def.getDictType().equals(dict[2])) {
                            w.getDefinitions().remove(def);
                            found = true;
                            break;
                        }
                    }
                    break;
                }
            }

        return found;
    }

    // Metoda care traduce un cuvant
    String translateWord(String word, String fromLanguage, String toLanguage){

        // Luam cuvintele din cele doua dictionare
        // In cazul in care unul din limbi este engleza, nu avem nevoie de dictionar
        ArrayList<Word> wordListFrom = null;
        if(!fromLanguage.equals("en")) {
            wordListFrom = wordMap.get(fromLanguage);
        }

        ArrayList<Word> wordListTo = null;
        if(!toLanguage.equals("en")) {
            wordListTo = wordMap.get(toLanguage);
        }

        String translated = null;
        String wordEn = null;
        int plural = -1;
        int singular = -1;

        // Cautam cuvantul in primul dictionar, preluam traducerea sa in engleza
        // De asemenea, vom atribui variabilelor "plural" si "singular" valorile indecsilor
        // din lista de forme de singular, respectiv de plural, in cazul in care cuvantul cautat
        // face parte din aceste doua liste.
        if(wordListFrom != null)
            for(Word w: wordListFrom)
                if(w.getWord().equals(word) || w.getPlural().contains(word) || w.getSingular().contains(word)) {
                    wordEn = w.getWord_en();
                    if(w.getPlural().contains(word))
                        plural = w.getPlural().indexOf(word);
                    if(w.getSingular().contains(word))
                        singular = w.getSingular().indexOf(word);
                    break;
                }

        // In cazul in care traducem din engleza, atunci traducerea in engleza este chiar cuvantul
        if(fromLanguage.equals("en"))
            wordEn = word;

        // Cautam cuvantul in celalalt dictionar, ii aflam traducerea
        if(wordListTo != null)
            for(Word w :wordListTo)
                if(w.getWord_en().equals(wordEn)) {
                    translated = w.getWord();
                    if(plural != -1)
                        translated = w.getPlural().get(plural);
                    if(singular != -1)
                        translated = w.getSingular().get(singular);
                    break;
                }

        // In cazul in care trebuie sa traducem in engleza, traducerea este chiar campul cuvantului in engleza
        if(toLanguage.equals("en"))
            translated = wordEn;

        if(translated == null)
            translated = word;
        return translated;
    }

    // Metoda care traduce o poropozitie
    String translateSentence(String sentence, String fromLanguage, String toLanguage){
        
        String[] translated = sentence.split(" ");
        for(int i = 0; i < translated.length; i++){
            translated[i] = translateWord(translated[i],fromLanguage,toLanguage);
        }

        return String.join(" ", translated);
    }

    // Metoda care traduce o propozitie in trei variante diferite
    ArrayList<String> translateSentences(String sentence, String fromLanguage, String toLanguage){

        String translated = translateSentence(sentence,fromLanguage,toLanguage);
        ArrayList<String> sentences = new ArrayList<>(List.of(translated));
        String[] words = translated.split(" ");

        ArrayList<Word> wordList = wordMap.get(toLanguage);

        for(int j = 0; j < 2 ; j++) {
            for (int i = 0; i < words.length; i++) {

                // Cautam sinonimele cuvantului
                if(wordList != null)
                    for(Word word: wordList)
                        if(word.getWord().equals(words[i]) || word.getPlural().contains(words[i]) || word.getSingular().contains(words[i]))
                            for(Definition def : word.getDefinitions())

                                // In cazul in care cuvantul are un dicitionar de sinonime valabil
                                // Si avem destule sinonime in acesta, atunci il inlocuim
                                if(def.getDictType().equals("synonyms") && j < def.getText().size())
                                    words[i] = def.getText().get(j);

            }

            sentences.add(String.join(" ", words));
            words = translated.split(" ");
        }

        // In cazul in care am avut mai putin de 3 variante diferite ale propozitiei
        // Nu trebuie sa avem propozitii duplicate
        Set<String> set = new HashSet<>(sentences);
        sentences.clear();
        sentences.addAll(set);
        return sentences;
    }

    // Metoda care intoarce definitiile si sinonimele unui cuvant
    ArrayList<Definition> getDefinitionsForWord(String word, String language){

        ArrayList<Word> wordList = wordMap.get(language);

        ArrayList<Definition> definitions = new ArrayList<>();

        // Cautam cuvantul in dictionarul respectiv
        if(wordList != null)
            for(Word w: wordList)
                if(w.getWord().equals(word))
                    definitions.addAll(w.getDefinitions());

        // Defintiile trebuie sortate in functie de anul dictionarului
        definitions.sort(new Comparator<Definition>() {
            @Override
            public int compare(Definition o1, Definition o2) {
                return o1.getYear() - o2.getYear();
            }
        });

        return definitions;
    }

    // Metoda pentru exportarea unui dictionar
    // Metoda care scrie un ArrayList de cuvinte intr-un dictionar
    void exportDictionary(String language){

        // Ordonam lista cu definitii ale cuvintelor
        ArrayList<Word> wordList = wordMap.get(language);
        for(Word w : wordList)
            w.getDefinitions().sort(new Comparator<Definition>() {
                @Override
                public int compare(Definition o1, Definition o2) {
                    return o1.getYear() - o2.getYear();
                }
            });

        // Ordonam lista de cuvinte
        wordList.sort(new Comparator<Word>() {
            @Override
            public int compare(Word o1, Word o2) {
                return o1.getWord().compareTo(o2.getWord());
            }
        });

        // Exportam dictionarul
        Gson gson = new GsonBuilder().setPrettyPrinting().create();
        File file = new File("dict/" + language + "_dict.json");

        try {
            Writer writer = Files.newBufferedWriter(file.toPath());
            gson.toJson(wordList, writer);
            writer.close();
        } catch (IOException e) {
            System.out.println("No such file");
        }
    }

    // Vom testa metodele
    public static void main(String[] args){

        Dictionar dictionar = new Dictionar();

        // Adauga un cuvant
        Definition definition = new Definition("Dicționar de sinonime","synonyms",1998, new ArrayList<>(Arrays.asList("mărţână","gloabă")));
        Word word = new Word("cal","horse","noun",new ArrayList<>(List.of("cal")),new ArrayList<>(List.of("cai")),new ArrayList<>(List.of(definition)));
        // Vom adauga cuvantul in dictionar -> expected true
        System.out.println(dictionar.addWord(word,"ro"));
        // Incercam sa adaugam cuvantul iar, acesta deja exista -> expected false
        System.out.println(dictionar.addWord(word,"ro"));

        // Sterge un cuvant
        // Stergem un cuvant care exista -> expected true
        System.out.println(dictionar.removeWord("jeu","fr"));
        // Stergem un cuvant care nu exista -> expected false
        System.out.println(dictionar.removeWord("oui","fr"));

        // Adauga o definitie
        Definition definition2 = new Definition("Dicționarul explicativ al limbii române (ediția a II-a revăzută și adăugită)","definitions",2009,
                                                new ArrayList<>(List.of("Animal domestic erbivor, cu copita nedespicată, folosit la călărie și la tracțiune")));
        // Adaugam o definitie noua -> expected true
        System.out.println(dictionar.addDefinitionForWord("cal","ro",definition2));
        // Adaugam o definitie care deja exista -> expected false
        System.out.println(dictionar.addDefinitionForWord("cal","ro",definition2));

        // Sterge o definitie
        // Stergem o definitie care exista -> expected true
        System.out.println(dictionar.removeDefinition("câine","ro","Dicționarul explicativ al limbii române (ediția a II-a revăzută și adăugită)_2009_definitions"));
        // Stergem o definitie dintr-un dictionar care nu exista -> expected false
        System.out.println(dictionar.removeDefinition("câine","ro","Dicționarul explicativ al limbii române (ediția a II-a revăzută și adăugită)_1990_definitions"));


        // Traduce un cuvant
        System.out.println(dictionar.translateWord("chats","fr","ro"));
        // Traducem un cuvant care nu exista
        System.out.println(dictionar.translateWord("șoarece","ro","en"));

        // Traduce o propozitie
        System.out.println(dictionar.translateSentence("pisică merge","ro","en"));
        // Traduce o propozitie cu un cuvant care nu exista
        System.out.println(dictionar.translateSentence("pisici merge","ro","fr"));

        // Traduce o propozitie in mai multe feluri
        System.out.println(dictionar.translateSentences("cat dog walk horse", "en","ro"));
        // Traduce o propozitie in mai multe feluri, dintr-un dictionar care nu exista
        System.out.println(dictionar.translateSentence("chats", "fr","cn"));

        // Intoarce definitiile si sinonimele unui cuvant
        System.out.println(dictionar.getDefinitionsForWord("cal","ro"));
        // Intoarce definitiile si sinonimele unui cuvant care nu exista
        System.out.println(dictionar.getDefinitionsForWord("om","ro"));

        // Export dictionary
        for(String lang : dictionar.wordMap.keySet())
            dictionar.exportDictionary(lang);


        // Afiseaza toate cuvintele
        // Asa ar trebui sa arate dictionarele in cazul in care le exportăm
        for(String s : dictionar.wordMap.keySet()) {
            System.out.println(s);
            for(Word w : dictionar.wordMap.get(s))
                System.out.println(w);
        }
    }
}
