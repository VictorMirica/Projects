package com.io;

import com.aventura.Trainer;
import com.item.*;
import com.pokemon.*;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class GetFileInfo {

    // Aici se vor citi informatiile din fisier
    // Fisierul va arata in urmatorul fel ( parametrii cu " " sunt optionali)
    // nume
    // varsta
    // pokemon 1 "item1" "item2" "item3"
    // ...

    public static Trainer[] readTrainerInfo(File file) throws FileNotFoundException {
        Scanner scanner = new Scanner(file);
        Trainer[] trainers = new Trainer[2];
        PokemonFactory pokemonFactory = PokemonFactory.Instanta();
        ItemDirector director = new ItemDirector();
        ItemBuilder builder = new ItemBuilder();


        for(int k = 0; k < 2; k++) {
            String nume = scanner.nextLine();
            int age;
            try {
                age = Integer.parseInt(scanner.nextLine());
            } catch (NumberFormatException e){
                Logger.errorMsg("Wrong number of pokemon\n");
                Logger.close();
                return null;
            }
            Trainer trainer = new Trainer(nume, age);

            for(int j = 0; j < 3; j++){
                try {
                    String line = scanner.nextLine();
                    String[] words = line.split(" ");
                    Pokemon pokemon = pokemonFactory.creeazaPokemon(PokemonType.valueOf(words[0].toLowerCase()));
                    for(int i = 1; i < words.length; i++) {
                        director.construct(words[i].toLowerCase(), builder);
                        pokemon.addItem(builder.getResult());
                    }
                    pokemon.updateStats();
                    if(!trainer.addPokemon(pokemon)){
                        return null;
                    }
                } catch (IllegalArgumentException | NoSuchElementException e){
                    Logger.errorMsg("Wrong number of pokemon\n");
                    Logger.close();
                    return null;
                }
            }

            trainers[k] = trainer;
        }


        return trainers;
    }
}
