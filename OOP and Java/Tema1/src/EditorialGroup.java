//Mirica Victor 324CB

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.text.SimpleDateFormat;
import java.util.Arrays;

public class EditorialGroup implements IPublishingArtifact{
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

    //metoda primeste ca argument un grup editorial si un vector de carti
    public void getEditorialGroupsBooks(EditorialGroup editorialGroup, Book[] books){
        editorialGroup.books = new Book[100];
        int i = 0;

        //Citim fisierul care face legatura intre carti si grupuri editoriale
        try (BufferedReader br = Files.newBufferedReader(Path.of("init/editorial-groups-books.in"))) {
            br.readLine();
            String line = br.readLine();
            while (line != null) {
                String[] attributes = line.split("###");
                if(editorialGroup.ID == Integer.parseInt(attributes[0])){
                    //Odata ce gasim grupul editorial, iteram array-ul de carti pentru a cauta
                    //cartea ai carui ID corespunde celei de-a doua coloane a fisierului
                    for(Book b : books){
                        if(b.getID() == Integer.parseInt(attributes[1])) {
                            //Am gasit cartea cu ID-ul respeciv, o vom adauga in array.
                            editorialGroup.books[i] = b;
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
        editorialGroup.books = Arrays.copyOf(editorialGroup.books, i);
    }

    //metoda care citeste editorial groups din fisierul editorial-groups.in
    public static EditorialGroup[] readEditorialGroups(){
        EditorialGroup[] editorialGroups = new EditorialGroup[264];
        //Avem nevoie de un array cu toate cartile, care va fi dat ca argument
        //metoda getEditorialGroupBooks pentru initializarea campului books.
        Book[] books = Book.readBooks();

        int i = 0;
        try (BufferedReader br = Files.newBufferedReader(Path.of("init/editorial-groups.in"))) {
            br.readLine();
            String line = br.readLine();
            while (line != null) {
                //Atributele sunt despartite prin "###"
                String[] attributes = line.split("###");
                EditorialGroup editorialGroup = new EditorialGroup();
                editorialGroup.ID = Integer.parseInt(attributes[0]);
                editorialGroup.name = attributes[1];

                //Ne folosim de aceasta metoda ca sa intializam array-ul de carti al obiectului
                editorialGroup.getEditorialGroupsBooks(editorialGroup, books);

                editorialGroups[i] = editorialGroup;
                i++;
                line = br.readLine();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }

        return editorialGroups;
    }

    //metoda reintoarce un string de forma unui fisier XML
    @Override
    public String Publish() {
        //Capul fisierului (id + nume)
        String s =  "<xml>\n" +
                        "\t<editorialGroup>\n" +
                            "\t\t<ID>"+this.ID+"</ID>\n" +
                            "\t\t<Name>"+this.name+"</Name>\n" +
                        "\t</editorialGroup>\n" +
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
        EditorialGroup[] eg = EditorialGroup.readEditorialGroups();
        for(EditorialGroup e : eg){
            System.out.println(e.Publish());
        }
    }
}
