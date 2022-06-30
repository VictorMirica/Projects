package com.aventura;

import com.io.Logger;
import com.pokemon.Pokemon;

import java.util.Random;

public class Fighter implements Runnable{

    // Clasa runnable, reprezinta un pokemon care se falta in batalie
    Pokemon pokemon;
    Pokemon enemy;

    public Fighter(Pokemon pokemon, Pokemon enemy) {
        this.pokemon = pokemon;
        this.enemy = enemy;
    }

    @Override
    public synchronized void run() {
            attack(enemy);
    }

    public void attack(Pokemon enemy){

        pokemon.coolAbilities();

        // Testam daca pokemonul este stunned sau daca adversarul se fereste
        if(pokemon.isStunned()){
            try {
                Thread.sleep(1);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            if(enemy.isDodging()){
                enemy.setDodging(false);
            }
            pokemon.setStunned(false);
            return;
        }

        Random rand = new Random();
        int i = 0;

        // Randomly, ataca sau foloseste una din abilitati pe pokemonul inamic
        // In cazul abilitatilor, se testeaza mai intai daca acestea sunt off-cooldown
        while(i != -1) {
            // Cazul neutrel
            if(pokemon.getAbility1() == null){
                damage(enemy);
                break;
            }

            i = rand.nextInt(3);
            switch (i) {
                case 0 -> {
                    if (pokemon.getAbility1().getCooldown() != 0)
                        break;
                    pokemon.getAbility1().use(pokemon, enemy);
                    i = -1;
                }
                case 1 -> {
                    if (pokemon.getAbility2().getCooldown() != 0)
                        break;
                    pokemon.getAbility2().use(pokemon, enemy);
                    i = -1;
                }
                case 2 -> {
                    damage(enemy);
                    i = -1;
                }
            }
        }
    }

    // Atacul simplu
    public void damage(Pokemon enemy){

        // Asteptam sa vedem daca adversarul va da dodge runda asta
        try {
            Thread.sleep(1);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        Logger.logAction(pokemon, " used a normal attack");

        if(enemy.isDodging()){
            enemy.setDodging(false);
            return;
        }

        int damage;
        if(pokemon.isSpecial())
            damage = pokemon.getAttack() - enemy.getSpecialDefense();
        else
            damage = pokemon.getAttack() - enemy.getDefense();

        if(damage > 0)
            enemy.setHp(enemy.getHp()-damage);

    }
}
