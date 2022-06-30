//Mirica Victor 324CB

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class Country {
    private int ID;
    private String countryCode;

    public int getID() {
        return ID;
    }

    //metoda care citeste tarile din fisierul countries.in
    public static Country[] readCountries(){
        Country[] countries = new Country[249];
        int i = 0;
        try (BufferedReader br = Files.newBufferedReader(Path.of("init/countries.in"))) {
            br.readLine();
            String line = br.readLine();
            while (line != null) {
                //Atributele sunt despartite prin "###"
                String[] attributes = line.split("###");
                Country country = new Country();
                country.ID = Integer.parseInt(attributes[0]);
                country.countryCode = attributes[1];

                countries[i] = country;
                i++;
                line = br.readLine();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }

        return countries;
    }

    @Override
    public String toString() {
        return "Country= " +
                "countryCode: " + countryCode;
    }
}
