//Mirica Victor 324CB

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class Author {
    private int ID;
    private String firstName;
    private String lastName;

    public int getID() {
        return ID;
    }

    //metoda care citeste autorii din fisierul authors.in
    public static Author[] readAuthors(){
        Author[] authors = new Author[2381];
        int i = 0;
        try (BufferedReader br = Files.newBufferedReader(Path.of("init/authors.in"))) {
            br.readLine();
            String line = br.readLine();
            while (line != null) {
                //Atributele sunt despartite prin "###"
                String[] attributes = line.split("###");
                Author author = new Author();
                author.ID = Integer.parseInt(attributes[0]);
                author.firstName = attributes[1];
                author.lastName = attributes[2];

                authors[i] = author;
                i++;
                line = br.readLine();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }

        return authors;
    }

    @Override
    public String toString() {
        return firstName + " " + lastName;
    }

}
