package com.aventura;

import com.io.Logger;
import com.pokemon.Pokemon;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Battle{

    // O batalie
    public static Pokemon battle(Pokemon pokemon1, Pokemon pokemon2){
        Pokemon winner;
        Pokemon loser;

        Logger.logBattle(pokemon1, pokemon2);
        ExecutorService executor = Executors.newFixedThreadPool(2);

        while(pokemon1.getHp() > 0 && pokemon2.getHp() > 0){

            // Fiecare pokemon din batalie isi va executa miscarile pe un thread
            // Deci vom avea 2 threaduri
            executor.execute(new Fighter(pokemon1, pokemon2));

            executor.execute(new Fighter(pokemon2, pokemon1));

            try {
                Thread.sleep(5);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            Logger.logActionResults(pokemon1, pokemon2);

        }

        executor.shutdown();
        // Cei doi pokemoni se lupta pana cand unul sau amandoi scad sub 0 hp

        // Draw
        if(pokemon1.getHp() <= 0 && pokemon2.getHp() <= 0){
            pokemon1.healUp();
            pokemon2.healUp();

            Logger.logBattleDraw();
            return null;
        }

        if(pokemon1.getHp() > 0 && pokemon2.getHp() <= 0){
            winner = pokemon1;
            loser = pokemon2;
        } else{
            winner = pokemon2;
            loser = pokemon1;
        }

        // La final, castigatorul va primi level up.
        winner.levelUp();
        loser.healUp();

        Logger.logBattleWinner(winner);

        return winner;
    }

}
