//Mirica Victor 324CB

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Arrays;

public class PublishingRetailer {
    private int ID;
    private String name;
    private IPublishingArtifact[] publishingArtifacts;
    private Country[] countries;

    public Country[] getCountries() {
        return countries;
    }

    public int getID() {
        return ID;
    }
    public IPublishingArtifact[] getPublishingArtifacts() {
        return publishingArtifacts;
    }

    //metoda care citeste publishing retailers din fisierul ppublishing-retailers.in
    public static PublishingRetailer[] readPublishingReatilers(){
        PublishingRetailer[] prs = new PublishingRetailer[31];

        //Vom avea nevoie de tari, carti, editorialgroups si publishingbrands.
        //acestea trebuie citite folosind metodele lor statice
        Country[] countries = Country.readCountries();
        Book[] books = Book.readBooks();
        EditorialGroup[] egs = EditorialGroup.readEditorialGroups();
        PublishingBrand[] pbs = PublishingBrand.readPublishingBrands();

        int i = 0;
        try (BufferedReader br = Files.newBufferedReader(Path.of("init/publishing-retailers.in"))) {
            br.readLine();
            String line = br.readLine();
            while (line != null) {
                String[] attributes = line.split("###");
                PublishingRetailer pr = new PublishingRetailer();
                pr.ID = Integer.parseInt(attributes[0]);
                pr.name = attributes[1];

                //Folosim metoda pentru a initializa array-ul countries al obiectului
                pr.getPublishingRetailerCountries(pr,countries);

                //Folosim metoda pentru a initializa array-ul de publishingArtifacts al obiectului
                pr.getPublishingRetailerArtifacts(pr,books,egs,pbs);

                prs[i] = pr;
                i++;
                line = br.readLine();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }

        return prs;
    }

    //Aceasta metoda primeste un publishing retailer si array-ul cu tarile din fisierul countries.in
    public void getPublishingRetailerCountries(PublishingRetailer pr, Country[] countries){
        pr.countries = new Country[50];
        int i = 0;

        //Citim fisierul de legatura
        try (BufferedReader br = Files.newBufferedReader(Path.of("init/publishing-retailers-countries.in"))) {
            br.readLine();
            String line = br.readLine();
            while (line != null) {
                String[] attributes = line.split("###");

                if(pr.ID == Integer.parseInt(attributes[0])){

                    //Odata ce am gasit pe prima coloana publishing retailer-ul, cautam prin arrayul de
                    //tari id-ul care crespunde cu cea de-a doua coloana din fisier
                    for(Country c : countries){
                        if(c.getID() == Integer.parseInt(attributes[1])) {

                            //Dupa ce gasim obiectuld e tip Country potrivit, il adaugam arrayului
                            pr.countries[i] = c;
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
        
        //Finalizam lungimea array-ului
        pr.countries = Arrays.copyOf(pr.countries, i);
    }

    //Aceasta metoda va intoarce in campul publishingArtifacts al retailer-ului primit ca parametru
    //De asemenea, aceasta are nevoie de array-urile cartilor din fisierul books.in,
    //grupurilor editoriale din editorial-groups.in si publishing brandurile din publishing-brands.in
    public void getPublishingRetailerArtifacts(PublishingRetailer pr, Book[] books, EditorialGroup[] egs, PublishingBrand[] pbs){
        pr.publishingArtifacts = new IPublishingArtifact[200];
        int i = 0;

        //Prima oara vom citi din fisierul care face legatura in retailer si cartile publicate direct de autor
        try (BufferedReader br = Files.newBufferedReader(Path.of("init/publishing-retailers-books.in"))) {
            br.readLine();
            String line = br.readLine();
            while (line != null) {
                String[] attributes = line.split("###");
                if(pr.ID == Integer.parseInt(attributes[0])){

                    //Cautam linia pe care apare id-ul ratailer-ului
                    for(Book b : books){
                        if(b.getID() == Integer.parseInt(attributes[1])) {

                            //Am gasit cartea ai carei ID corespunde liniei pe care ne aflam
                            pr.publishingArtifacts[i] = b;
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

        //In continuare, citim fisierul care face legatura dintre retailer si grupurile editoriale
        try (BufferedReader br = Files.newBufferedReader(Path.of("init/publishing-retailers-editorial-groups.in"))) {
            br.readLine();
            String line = br.readLine();
            while (line != null) {
                String[] attributes = line.split("###");
                if(pr.ID == Integer.parseInt(attributes[0])){

                    //Cautam linia pe care apare id-ul ratailer-ului
                    for(EditorialGroup eg : egs){
                        if(eg.getID() == Integer.parseInt(attributes[1])) {

                            //Am gasit editorial group-ul al carui ID corespunde liniei pe care ne aflam
                            pr.publishingArtifacts[i] = eg;
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


        //In final, vom citi fisierul de legatura dintre retailer si publishing brand-uri
        try (BufferedReader br = Files.newBufferedReader(Path.of("init/publishing-retailers-publishing-brands.in"))) {
            br.readLine();
            String line = br.readLine();
            while (line != null) {
                String[] attributes = line.split("###");
                if(pr.ID == Integer.parseInt(attributes[0])){

                    //Cautam linia pe care apare id-ul ratailer-ului
                    for(PublishingBrand pb : pbs){
                        if(pb.getID() == Integer.parseInt(attributes[1])) {

                            //Am gasit publisher-ul al carui ID corespunde liniei pe care ne aflam
                            pr.publishingArtifacts[i] = pb;
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

        pr.publishingArtifacts = Arrays.copyOf(pr.publishingArtifacts, i);
    }

    //Metoda toString, folosita in testare
    @Override
    public String toString() {

        //Numele, id-ul si tarile
        String s = "PublishingRetailer= " +
                "ID: " + ID +
                ", name: " + name+
                ", countries: " + Arrays.toString(countries);
        s = s + "\n";

        //Deoarece publishingArtifacts este un array de Interfete
        //vom intoarce doar numele fiecarui element din array
        //in metoda de ce tip de obiect este acesta.
        for(IPublishingArtifact pa : publishingArtifacts){

            if(pa instanceof  Book){
                s = s + ((Book) pa).getName() + ", ";
            }

            if(pa instanceof  EditorialGroup){
                s = s + ((EditorialGroup) pa).getName() + ", ";
            }

            if(pa instanceof  PublishingBrand){
                s = s + ((PublishingBrand) pa).getName() + ", ";
            }
        }

        return s;
    }

    public static void main(String[] args) {
        PublishingRetailer[] prs = PublishingRetailer.readPublishingReatilers();
        for(PublishingRetailer pr : prs){
            System.out.println(pr);
        }
    }
}
