package com.aventura;

import com.io.Logger;
import com.pokemon.Pokemon;

import java.util.ArrayList;

public class Trainer {

    // Clasa care reprezinta un jucator
    private final String name;
    private final int age;
    private final ArrayList<Pokemon> pokemons = new ArrayList<>();

    public Trainer(String name, int age) {
        this.name = name;
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }

    // Getter pentru fiecare pokemon
    public Pokemon getPokemon1(){
        return pokemons.get(0);
    }

    public Pokemon getPokemon2(){
        return pokemons.get(1);
    }

    public Pokemon getPokemon3(){
        return pokemons.get(2);
    }

    // Intoarce cel mai puternic pokemon al jucatorului
    public Pokemon getStrongestPokemon(){
        Pokemon strongest = null;
        int max = 0;
        for (Pokemon pokemon : pokemons) {
            if(pokemon.getStats() > max){
                max = pokemon.getStats();
                strongest = pokemon;
            }

            if(pokemon.getStats() == max)
                if (strongest != null && pokemon.getName().name().compareTo(strongest.getName().name()) < 0)
                    strongest = pokemon;
        }
        return strongest;
    }

    // Adauga un pokemon, folosita la initializare
    public boolean addPokemon(Pokemon pokemon) {
        if(pokemons.size() == 3)
            return true;
        if(pokemons.contains(pokemon)) {
            Logger.errorMsg("Too many of the same pokemon\n");
            Logger.close();
            return false;
        }
        pokemons.add(pokemon);
        return true;
    }

}
