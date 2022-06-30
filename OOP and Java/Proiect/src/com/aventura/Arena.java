package com.aventura;

import com.io.Logger;
import com.pokemon.Pokemon;
import com.pokemon.PokemonFactory;
import com.pokemon.PokemonType;

import java.util.Random;

public class Arena {

    // Dupa cititre, incepe aventura.

    public static Trainer fight(Trainer player1, Trainer player2){
        int winner;
        //Event 1
        Arena.event(player1.getPokemon1(), player2.getPokemon1());
        //Event 2
        Arena.event(player1.getPokemon2(), player2.getPokemon2());
        //Event 3
        Arena.event(player1.getPokemon3(), player2.getPokemon3());
        //Event 4
        winner = Arena.event(player1.getStrongestPokemon(), player2.getStrongestPokemon());

        if(winner == 0)
            return null;
        if(winner == 1)
            return player1;
        return player2;
    }

    // Prezinta un eveniment, intoarce 1 daca a castigat player1, 2 daca a castigat player2, 0 in caz de draw
    private static int event(Pokemon pokemon1, Pokemon pokemon2){
        PokemonFactory pokemonFactory = PokemonFactory.Instanta();
        Pokemon winner;
        Random rand = new Random();

        Logger.logEventStart();

        // Cele trei tipuri de lupte trebuie luate in ordine aleatoare
        while(true) {
            int i = rand.nextInt(3);
            switch (i) {
                // Cei doi antrenori se bat cu neutrel1
                case 0 -> {
                    winner = Battle.battle(pokemon1, pokemonFactory.creeazaPokemon(PokemonType.neutrel1));
                    if(winner != pokemon1)
                        return 2;
                    winner = Battle.battle(pokemon2, pokemonFactory.creeazaPokemon(PokemonType.neutrel1));
                    if(winner != pokemon2)
                        return 1;
                }
                // Cei doi antrenori se bat cu un neutrel2
                case 1 -> {
                    winner = Battle.battle(pokemon1, pokemonFactory.creeazaPokemon(PokemonType.neutrel2));
                    if(winner != pokemon1)
                        return 2;
                    winner = Battle.battle(pokemon2, pokemonFactory.creeazaPokemon(PokemonType.neutrel2));
                    if(winner != pokemon2)
                        return 1;
                }
                // Cei doi antrenori se dueleaza
                case 2-> {
                    winner = Battle.battle(pokemon1, pokemon2);
                    if(winner == null)
                        return 0;
                    if(winner == pokemon1)
                        return 1;
                    return 2;
                }
            }
        }
    }
}
