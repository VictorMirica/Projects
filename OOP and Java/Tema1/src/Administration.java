//Mirica Victor 324CB

import java.util.Arrays;
import java.util.Comparator;

public class Administration {

    //Citim reatilerii si limbile, vom avea nevoie de cel putin unul din cele doua arrayuri in toate
    //metodele care urmmeaza sa fie implementate
    private static final PublishingRetailer[] prs = PublishingRetailer.readPublishingReatilers();
    private static final Language[] allLanguages = Language.readLanguages();

    //Metoda care intoarce un array cu cartile unui retailer, primit ca parametru.
    private static Book[] getBooksForPublishingRetailerID(int publishingRetailerID) throws ExceptieArg {
        Book[] books = new Book[1000];
        PublishingRetailer pr = null;

        //Iteram array-ul de retailer, cautand-ul pe cel primit ca parametru
        for(PublishingRetailer publishingRetailer: prs){
            if (publishingRetailer.getID() == publishingRetailerID) {
                pr = publishingRetailer;
                break;
            }
        }

        int i = 0;
        if (pr == null)
            throw new ExceptieArg();

        //Odata ce am gasit retailer-ul trebuie sa adaugam cartile
        //acestuia prin 3 metode, in toate cele trei cazuri de PublishingArtifacts
        for(IPublishingArtifact pa : pr.getPublishingArtifacts()){

            //In cazul in care obiectul este o carte, acesta trebuie pur si simplu adaugat in array
            if(pa instanceof  Book){
                books[i] = (Book)pa;
                i++;
            }

            //In cazul in care acesta este un editorail group sau un publisher,
            //Vom itera arrayul de carti al obiectului respectiv, adaugand fiecare carte
            //in array-ul care trebuie intors de metoda
            if(pa instanceof  EditorialGroup){
                Book[] egBooks = ((EditorialGroup) pa).getBooks();
                int j = 0;
                while(j != egBooks.length) {
                    books[i] = egBooks[j];
                    j++;
                    i++;
                }
            }
            if(pa instanceof  PublishingBrand){
                Book[] pbBooks = ((PublishingBrand) pa).getBooks();
                int j = 0;
                while(j != pbBooks.length) {
                    books[i] = pbBooks[j];
                    j++;
                    i++;
                }
            }
        }

        books = Arrays.copyOf(books, i);

        //duplicatele trebuie eliminate
        //sortam arrary-ul
        Arrays.sort(books, new Comparator<Book>() {
            @Override
            public int compare(Book o1, Book o2) {
                return o1.getID() - o2.getID();
            }
        });

        //eliminam elementele care apar de mai multe ori
        int k = 1;
        Book[] returnBooks = new Book[1000];
        returnBooks[0] = books[0];
        for(int j = 0; j < i-1; j++){
            if(books[j].getID() != books[j+1].getID()) {
                returnBooks[k] = books[j + 1];
                k++;
            }
        }

        returnBooks = Arrays.copyOf(returnBooks, k);
        return returnBooks;
    }

    //Metoda care intoarce un array de obiecte de tip Language al unui retailer.
    //ID-ul retailer-ului este unicul parametru.
    private static Language[] getLanguagesForPublishingRetailerID(int publishingReatilerID){
        Book[] books = new Book[0];
        //Preluam cartile retailer-ului
        try {
            books = getBooksForPublishingRetailerID(publishingReatilerID);
        } catch (ExceptieArg e) {
              System.out.println(e.getMessage());
        }

        //Citim limbile din fisierul languages.in
        //Vom avea nevoie pentru cross-reference
        Language[] languages = new Language[4];

        int i = 0;

        //Fiecare carte are campul languageID, iteram vectorul de carti
        for(Book b : books){
            for (Language l : allLanguages) {

                //Am gasit limba care trebuie adaugata in array
                if (b.getLanguageID() == l.getID()) {

                    //Nu vrem sa avem de mai multe ori aceeas limba in vector asadar
                    //folosim un flag
                    int duplicate = 0;
                    for(int k = 0; k < i; k++){

                        //iteram array-ul limbilor, testam daca avem deja limba gasita
                        //in cazul in care aceasta nu se afla, o vom adauga
                        if (languages[k].getID() == b.getLanguageID()) {
                            duplicate = 1;
                            break;
                        }
                    }
                    if(duplicate == 0) {
                        languages[i] = l;
                        i++;
                    }
                    break;
                }
            }
        }

        languages = Arrays.copyOf(languages, i);
        return languages;
    }

    //Metoda care intoarce un array de tari, primeste ca parametru un ID al unei carti.
    //Putem accesa campul de tari doar din calasa PublishingRetailer, asadar
    //va trebui sa cautam prin toti retailerii cartea dorita
    private static Country[] getCountriesForBookID(int bookID){
        Country[] countries = new Country[249];

        //Citim retailers
        int i = 0;

        //Pentru fiecare retailer, preluam lista cu carti a acestora
        //deoarece o carte poate avea mai multi retaileri
        for (PublishingRetailer pr : prs) {
            Book[] books = new Book[0];
            try {
                books = getBooksForPublishingRetailerID(pr.getID());
            } catch (ExceptieArg e) {
                  System.out.println(e.getMessage());
            }

            for(Book b: books){
                if(b.getID() == bookID){

                    //Am gasit cartea in cadrul acestui retailer
                    for(int j = 0; j < pr.getCountries().length ; j++) {

                        //Preluam array-ul de tari al acestui retailer
                        //Testam daca nu avem deja tara in array-ul ce trebuie intors
                        //In cazul in care aceasta nu se afla in array, o adaugam.
                        int duplicate = 0;
                        for (int k = 0; k < i; k++) {
                            if (pr.getCountries()[j].getID() == countries[k].getID())
                                duplicate = 1;
                        }
                        if(duplicate == 0) {
                            countries[i] = pr.getCountries()[j];
                            i++;
                        }
                    }
                    break;
                }
            }
        }

        countries = Arrays.copyOf(countries,i);
        return countries;
    }

    //Metoda care intoarce intersectia dintre array-urile de carti a 2 retaileri
    private static Book[] getCommonBooksForRetailerIDs(int retailerID1, int retailerID2){

        //Facem rost de cele doua array-uri pentru cartile celor doi retaileri
        Book[] books1 = new Book[0];
        Book[] books2 = new Book[0];
        try {
            books1 = getBooksForPublishingRetailerID(retailerID1);
            books2 = getBooksForPublishingRetailerID(retailerID2);
        } catch (ExceptieArg e) {
              System.out.println(e.getMessage());
        }

        Book[] books = new Book[1000];
        int i = 0;

        //Iteram cele doua array-uri, in cazul in care gasim
        //doua obiecte cu același ID, adăugam obiectul in array-ul ce trebuie intors.
        for(Book b1: books1){
            for(Book b2: books2){
                if(b1.getID() == b2.getID()){
                    books[i] = b1;
                    i++;
                    break;
                }
            }
        }

        books = Arrays.copyOf(books, i);
        return books;
    }

    //Metoda care intoarce reuiniunea celor doua array-uri de carti a 2 retaileri
    private static Book[] getAllBooksForRetailerIDs (int retailerID1, int retailerID2){

        //Facem rost de cele doua array-uri pentru cartile celor doi retaileri
        Book[] books1 = new Book[0];
        Book[] books2 = new Book[0];
        try {
            books1 = getBooksForPublishingRetailerID(retailerID1);
            books2 = getBooksForPublishingRetailerID(retailerID2);
        } catch (ExceptieArg e) {
              System.out.println(e.getMessage());
        }

        //Gasim cartile comune, nu apelam metoda getCommonBooksForRetailerIDs deoarece
        //asta ar insemna sa apleam dinnou metodele getBooksForPublishingRetailerID
        //pentru cei doi retaileri
        Book[] commonBooks = new Book[1000];
        int i = 0;
        for(Book b1: books1){
            for(Book b2: books2){
                if(b1.getID() == b2.getID()){
                    commonBooks[i] = b1;
                    i++;
                    break;
                }
            }
        }
        commonBooks = Arrays.copyOf(commonBooks, i);


        //Vom face reuniunea direct in arrray-ul primului retailer
        i = books1.length;
        books1 = Arrays.copyOf(books1, 1000);

        //Iteram array-ul celui de-al doilea retailer
        for(Book b: books2){

            //Vom avea un flag, intial 0, care indica daca cartea se
            //afla si in array-ul cu carti comune.
            int common = 0;
            for(Book cb: commonBooks){
                if (b.getID() == cb.getID()) {
                    common = 1;
                    break;
                }
            }
            if(common == 0){
                books1[i] = b;
                i++;
            }
        }

        books1 = Arrays.copyOf(books1, i);
        return books1;
    }

    //Cele cinci metode de testare, cu cate cinci exemple fiecare
    public static void testFunct1(){
        Book[] books = new Book[0];
        //1
        System.out.println("Exemplu 1 (getBooks ID 1) :\n");
        try {
            books = Administration.getBooksForPublishingRetailerID(1);
        } catch (ExceptieArg e) {
            System.out.println(e.getMessage());
        }
        for (Book b: books)
            System.out.println(b.Publish());
        //2
        System.out.println("Exemplu 2 (getBooks ID 2) :\n");
        try {
            books = Administration.getBooksForPublishingRetailerID(2);
        } catch (ExceptieArg e) {
              System.out.println(e.getMessage());
        }
        for (Book b: books)
            System.out.println(b.Publish());
        //3
        System.out.println("Exemplu 3 (getBooks. RetailerID 3) :\n");
        try {
            books = Administration.getBooksForPublishingRetailerID(3);
        } catch (ExceptieArg e) {
            System.out.println(e.getMessage());
        }
        for (Book b: books)
            System.out.println(b.Publish());
        //4
        System.out.println("Exemplu 4 (getBooks. RetailerID 4) :\n");
        try {
            books = Administration.getBooksForPublishingRetailerID(4);
        } catch (ExceptieArg e) {
            System.out.println(e.getMessage());
        }
        for (Book b: books)
            System.out.println(b.Publish());
        //5
        System.out.println("Exemplu 5 (getBooks. RetailerID 5) :\n");
        try {
            books = Administration.getBooksForPublishingRetailerID(5);
        } catch (ExceptieArg e) {
            System.out.println(e.getMessage());
        }
        for (Book b: books)
            System.out.println(b.Publish());
    }

    public static void testFunct2(){
        Language[] languages;
        //6
        System.out.println("Exemplu 6 (getLanguages. RetailerID 6) :\n");
        languages = Administration.getLanguagesForPublishingRetailerID(6);
        for(Language l : languages)
            System.out.println(l);
        //7
        System.out.println("Exemplu 7 (getLanguages. RetailerID 7) :\n");
        languages = Administration.getLanguagesForPublishingRetailerID(7);
        for(Language l : languages)
            System.out.println(l);
        //8
        System.out.println("Exemplu 8 (getLanguages. RetailerID 8) :\n");
        languages = Administration.getLanguagesForPublishingRetailerID(8);
        for(Language l : languages)
            System.out.println(l);
        //9
        System.out.println("Exemplu 9 (getLanguages. RetailerID 9) :\n");
        languages = Administration.getLanguagesForPublishingRetailerID(9);
        for(Language l : languages)
            System.out.println(l);
        //10
        System.out.println("Exemplu 10 (getLanguages. RetailerID 28) :\n");
        languages = Administration.getLanguagesForPublishingRetailerID(28);
        for(Language l : languages)
            System.out.println(l);
    }

    public static void testFunct3(){
        Country[] countries;
        //11
        System.out.println("Exemplu 11 (getCountries. BookID 204) :\n");
        countries = getCountriesForBookID(204);
        for(Country c : countries)
            System.out.println(c);
        //12
        System.out.println("Exemplu 12 (getCountries. BookID 224) :\n");
        countries = getCountriesForBookID(224);
        for(Country c : countries)
            System.out.println(c);

        //13
        System.out.println("Exemplu 13 (getCountries. BookID 262) :\n");
        countries = getCountriesForBookID(262);
        for(Country c : countries)
            System.out.println(c);

        //14
        System.out.println("Exemplu 14 (getCountries. BookID 275) :\n");
        countries = getCountriesForBookID(275);
        for(Country c : countries)
            System.out.println(c);

        //15
        System.out.println("Exemplu 15 (getCountries. BookID 291) :\n");
        countries = getCountriesForBookID(291);
        for(Country c : countries)
            System.out.println(c);

    }

    public static void testFunct4(){
        Book[] books;
        //16
        System.out.println("Exemplu 16 (getCommonBooks. RetailerID 1 si 2) :\n");
        books = getCommonBooksForRetailerIDs(1,2);
        for(Book b : books)
            System.out.println(b.Publish());

        //17
        System.out.println("Exemplu 17 (getCommonBooks. RetailerID 3 si 4) :\n");
        books = getCommonBooksForRetailerIDs(3,4);
        for(Book b : books)
            System.out.println(b.Publish());

        //18
        System.out.println("Exemplu 18 (getCommonBooks. RetailerID 5 si 6) :\n");
        books = getCommonBooksForRetailerIDs(5,6);
        for(Book b : books)
            System.out.println(b.Publish());

        //19
        System.out.println("Exemplu 19 (getCommonBooks. RetailerID 7 si 8) :\n");
        books = getCommonBooksForRetailerIDs(7,8);
        for(Book b : books)
            System.out.println(b.Publish());

        //20
        System.out.println("Exemplu 20 (getCommonBooks. RetailerID 9 si 10) :\n");
        books = getCommonBooksForRetailerIDs(9,10);
        for(Book b : books)
            System.out.println(b.Publish());

    }

    public static void testFunct5(){
        Book[] books;
        //21
        System.out.println("Exemplu 21 (getAllBooks. RetailerID 1 si 2) :\n");
        books = getAllBooksForRetailerIDs(1,2);
        for(Book b : books)
            System.out.println(b.Publish());
        //22
        System.out.println("Exemplu 22 (getAllBooks. RetailerID 3 si 4) :\n");
        books = getAllBooksForRetailerIDs(3,4);
        for(Book b : books)
            System.out.println(b.Publish());
        //23
        System.out.println("Exemplu 23 (getAllBooks. RetailerID 5 si 6) :\n");
        books = getAllBooksForRetailerIDs(5,6);
        for(Book b : books)
            System.out.println(b.Publish());
        //24
        System.out.println("Exemplu 24 (getAllBooks. RetailerID 7 si 8) :\n");
        books = getAllBooksForRetailerIDs(7,8);
        for(Book b : books)
            System.out.println(b.Publish());
        //25
        System.out.println("Exemplu 25 (getAllBooks. RetailerID 9 si 10) :\n");
        books = getAllBooksForRetailerIDs(9,10);
        for(Book b : books)
            System.out.println(b.Publish());
    }

    public static void main(String[] args) {
        testFunct1();
        testFunct2();
        testFunct3();
        testFunct4();
        testFunct5();
    }
}

//Exceptie in cazul in care metoda primeste un ID invalid.
class ExceptieArg extends Exception{
    public ExceptieArg() {
        super("Invalid ID\n");
    }
}
