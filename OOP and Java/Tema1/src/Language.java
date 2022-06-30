//Mirica Victor 324CB

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class Language {
    private int ID;
    private String code;
    private String name;

    public int getID() {
        return ID;
    }

    //metoda care citeste limbile din fisierul languages.in
    public static Language[] readLanguages(){
        Language[] languages = new Language[4];
        int i = 0;
        try (BufferedReader br = Files.newBufferedReader(Path.of("init/languages.in"))) {
            br.readLine();
            String line = br.readLine();
            while (line != null) {
                //Atributele sunt despartite prin "###"
                String[] attributes = line.split("###");
                Language language = new Language();
                language.ID = Integer.parseInt(attributes[0]);
                language.code = attributes[1];
                language.name = attributes[2];

                languages[i] = language;
                i++;
                line = br.readLine();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }

        return languages;
    }

    @Override
    public String toString() {
        return "Language= " +
                "ID: " + ID +
                ", code: " + code +
                ", name: " + name;
    }
}
