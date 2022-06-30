//Mirica Victor 324CB

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.text.SimpleDateFormat;
import java.util.Arrays;

public class PublishingBrand implements IPublishingArtifact {
    private int ID;
    private String name;
    private Book[] books;

    public int getID() {
        return ID;
    }
    public Book[] getBooks() {
        return books;
    }
    public String getName() {
        return name;
    }

    //metoda primeste ca argument un publishing brand si un vector de carti
    public void getPublishingBrandBooks(PublishingBrand publishingBrand, Book[] books){
        publishingBrand.books = new Book[100];
        int i = 0;

        //Citim fisierul care face legatura intre carti si publishing brands
        try (BufferedReader br = Files.newBufferedReader(Path.of("init/publishing-brands-books.in"))) {
            br.readLine();
            String line = br.readLine();
            while (line != null) {
                String[] attributes = line.split("###");
                if(publishingBrand.ID == Integer.parseInt(attributes[0])){
                    //Odata ce gasim publishing brandul, iteram array-ul de carti pentru a cauta
                    //cartea ai carui ID corespunde celei de-a doua coloane a fisierului
                    for(Book b : books){
                        if(b.getID() == Integer.parseInt(attributes[1])) {
                            //Am gasit cartea cu ID-ul respeciv, o vom adauga in array.
                            publishingBrand.books[i] = b;
                            i++;
                            break;
                        }
                    }
                }
                line = br.readLine();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
        publishingBrand.books = Arrays.copyOf(publishingBrand.books, i);
    }

    //metoda care citeste publishing brands din fisierul publishing-brands.in
    public static PublishingBrand[] readPublishingBrands(){
        PublishingBrand[] publishingBrands = new PublishingBrand[317];

        //Avem nevoie de un array cu toate cartile, care va fi dat ca argument
        //metoda getEditorialGroupBooks pentru initializarea campului books.
        Book[] books = Book.readBooks();

        int i = 0;
        try (BufferedReader br = Files.newBufferedReader(Path.of("init/publishing-brands.in"))) {
            br.readLine();
            String line = br.readLine();
            while (line != null) {
                //Atributele sunt despartite prin "###"
                String[] attributes = line.split("###");
                PublishingBrand publishingBrand = new PublishingBrand();
                publishingBrand.ID = Integer.parseInt(attributes[0]);
                publishingBrand.name = attributes[1];

                //Ne folosim de aceasta metoda ca sa intializam array-ul de carti al obiectului
                publishingBrand.getPublishingBrandBooks(publishingBrand, books);

                publishingBrands[i] = publishingBrand;
                i++;
                line = br.readLine();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }

        return publishingBrands;
    }


    //metoda reintoarce un string de forma unui fisier XML
    @Override
    public String Publish() {
        //Capul fisierului (id + nume)
        String s =  "<xml>\n" +
                "\t<publishingBrand>>\n" +
                "\t\t<ID>"+this.ID+"</ID>\n" +
                "\t\t<Name>"+this.name+"</Name>\n" +
                "\t</publishingBrand>>\n" +
                "\t<books>\n";

        //Cartile fisierului
        for(Book b : books){
            s = s +         "\t\t<book>\n"+
                    "\t\t\t<title>"+b.getName()+"</title>\n" +
                    "\t\t\t<subtitle>"+b.getSubtitle()+"</subtitle>\n" +
                    "\t\t\t<isbn>"+b.getISBN()+"</isbn>\n" +
                    "\t\t\t<pageCount>"+b.getPageCount()+"</pageCount>\n" +
                    "\t\t\t<keywords>"+ b.getKeywords()+"</keywords>\n" +
                    "\t\t\t<languageID>"+b.getLanguageID()+"</languageID>\n" +
                    "\t\t\t<createdOn>"+(new SimpleDateFormat("dd.MM.yyyy HH:mm:ss").format(b.getCreatedOn().getTime()))+"</createdOn>\n" +
                    "\t\t\t<authors>"+ Arrays.toString(b.getAuthors())+"</authors>\n" +
                    "\t\t</book>\n";
        }

        //Coada fisierului
        s = s +
                "\t</books>\n" +
                "</xml>";
        return s;
    }

    public static void main(String[] args) {
        PublishingBrand[] pb = PublishingBrand.readPublishingBrands();
        for(PublishingBrand p : pb){
            System.out.println(p.Publish());
        }
    }
}
