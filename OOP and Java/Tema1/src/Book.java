//Mirica Victor 324CB

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Calendar;

public class Book implements IPublishingArtifact{
    private int ID;
    private String name;
    private String subtitle;
    public String ISBN;
    private int pageCount;
    private String keywords;
    private int languageID;
    private Calendar createdOn;
    private Author[] authors;

    //getters
    public int getID() {
        return ID;
    }
    public String getName() {
        return name;
    }
    public String getSubtitle() {
        return subtitle;
    }
    public String getISBN() {
        return ISBN;
    }
    public int getPageCount() {
        return pageCount;
    }
    public String getKeywords() {
        return keywords;
    }
    public int getLanguageID() {
        return languageID;
    }
    public Calendar getCreatedOn() {
        return createdOn;
    }
    public Author[] getAuthors() {
        return authors;
    }

    //metoda care citeste toate cartile din fisierul de intrare
    public static Book[] readBooks(){
        Book[] books = new Book[1000];
        //apelam metoda care citeste autorii din fisierul de intrare
        Author[] authors = Author.readAuthors();

        int i = 0;
        try (BufferedReader br = Files.newBufferedReader(Path.of("init/books.in"))) {
            //citim fisierul books.in linie cu linie
            br.readLine();
            String line = br.readLine();
            while (line != null) {
                //atributele sunt despartite de stringul "###"
                String[] attributes = line.split("###");
                Book book = new Book();
                book.ID = Integer.parseInt(attributes[0]);
                book.name = attributes[1];
                book.subtitle = attributes[2];
                book.ISBN = attributes[3];
                book.pageCount = Integer.parseInt(attributes[4]);
                book.keywords = attributes[5];
                book.languageID = Integer.parseInt(attributes[6]);

                //Pentru formatarea datei, folosim un obiect de tipul SimpleDateFormat
                SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy HH:mm:ss");
                book.createdOn = Calendar.getInstance();
                book.createdOn.setTime(sdf.parse(attributes[7]));

                //apelam metoda care primeste cartea(this) si array-ul de autori
                //aceasta atribuie cartii autorii respectivi, citind fisierul books-authors.in
                book.getBooksAuthors(book, authors);

                books[i] = book;
                i++;
                line = br.readLine();
            }

        } catch (IOException | ParseException ioe) {
            ioe.printStackTrace();
        }

        return books;
    }

    //metoda care face legatura dintre o carte si autorii sai
    //primeste ca parametru cartea a carui camp trebuie scris
    public void getBooksAuthors(Book book, Author[] authors){
        book.authors = new Author[10];
        int i = 0;
        //citim fisierul linie cu linie
        try (BufferedReader br = Files.newBufferedReader(Path.of("init/books-authors.in"))) {
            br.readLine();
            String line = br.readLine();
            while (line != null) {
                //atributele sunt desparite de stringul "###"
                String[] attributes = line.split("###");
                //am gasit o linie in care apare ID-ul cartii, trebuie sa adaugam autorul respectiv
                if(book.ID == Integer.parseInt(attributes[0])){
                    for(Author a : authors){
                        //iteram array-ul cu autori, cautand dupa id
                        if(a.getID() == Integer.parseInt(attributes[1])) {
                            //am gasit autorul, acesta e adaugat in campul cartii
                            book.authors[i] = a;
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
        book.authors = Arrays.copyOf(book.authors, i);
    }

    //metoda reintoarce un string de forma unui fisier XML
    @Override
    public String Publish(){
        return "<xml>\n" +
                    "\t<title>"+this.name+"</title>\n" +
                    "\t<subtitle>"+this.subtitle+"</subtitle>\n" +
                    "\t<isbn>"+this.ISBN+"</isbn>\n" +
                    "\t<pageCount>"+this.pageCount+"</pageCount>\n" +
                    "\t<keywords>"+ this.keywords+"</keywords>\n" +
                    "\t<languageID>"+this.languageID+"</languageID>\n" +
                    "\t<createdOn>"+(new SimpleDateFormat("dd.MM.yyyy HH:mm:ss").format(this.createdOn.getTime()))+"</createdOn>\n" +
                    "\t<authors>"+ Arrays.toString(this.authors)+"</authors>\n" +
                "</xml>";
    }

    public static void main(String[] args){
        Book[] books = Book.readBooks();
        for(Book b: books){
            System.out.println(b.Publish());
        }
    }
}
