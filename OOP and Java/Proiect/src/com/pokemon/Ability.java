package com.pokemon;

import com.io.Logger;

public class Ability {

    // Clasa care reprezinta o abilitate a unui pokemon
    private final int damage;
    private final boolean stun;
    private final boolean dodge;
    private final int cooldown;
    private int currCooldown;

    public Ability(int damage, boolean stun, boolean dodge, int cooldown) {
        this.damage = damage;
        this.stun = stun;
        this.dodge = dodge;
        this.cooldown = cooldown;
        currCooldown = 0;
    }

    public int getCooldown() {
        return currCooldown;
    }

    // Aceasta se va folosi doar cand campul currentCooldown este 0.
    // Odata folosita, campul currCooldown va fi setat la valoarea cooldown.
    // La fiecare moment din lupta, acesta va fi decrementat pana ajunge
    // din nou la 0
    public void use(Pokemon user, Pokemon enemy){

        currCooldown = cooldown;

        if(dodge)
            user.setDodging(true);

        Logger.logAction(user, this.toString());

        try {
            Thread.sleep(1);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        if(enemy.isDodging()){
            enemy.setDodging(false);
            return;
        }

        if(stun) {
            enemy.setStunned(true);
        }

        enemy.setHp(enemy.getHp() - damage);
    }

    public void decCooldown(){
        if(currCooldown > 0)
            currCooldown--;
    }

    @Override
    public String toString() {
        return " used an ability! " +
                "damage=" + damage +
                ", stun=" + stun +
                ", dodge=" + dodge +
                ", cooldown=" + cooldown;
    }
}
