package com.pokemon;

import com.io.Observator;
import com.item.Item;

import java.util.ArrayList;

public class Pokemon {

    private final PokemonType name;
    private int hp;
    private int attack;
    private int defense;
    private int specialDefense;
    private final boolean special;
    private final Ability ability1;
    private final Ability ability2;

    private final ArrayList<Item> items = new ArrayList<>();

    private boolean stunned = false;
    private boolean dodging = false;

    // DP: memeto si observator
    private PokemonMemento backup;
    public Observator observator = new Observator(this);


    public Pokemon(PokemonType name, int hp, int attack, int defense, int specialDefense, boolean special, Ability ability1, Ability ability2) {
        this.name = name;
        this.hp = hp;
        this.attack = attack;
        this.defense = defense;
        this.specialDefense = specialDefense;
        this.special = special;
        this.ability1 = ability1;
        this.ability2 = ability2;
        backup = savePokemon();
    }

    public PokemonType getName() {
        return name;
    }

    public int getHp() {
        return hp;
    }

    public int getAttack() {
        return attack;
    }

    public int getDefense() {
        return defense;
    }

    public int getSpecialDefense() {
        return specialDefense;
    }

    public Ability getAbility1() {
        return ability1;
    }

    public Ability getAbility2() {
        return ability2;
    }

    public boolean isSpecial() {
        return special;
    }

    public boolean isStunned() {
        return stunned;
    }

    public boolean isDodging(){ return dodging; }

    public void setHp(int hp) {
        this.hp = hp;
    }

    protected void setAttack(int attack) {
        this.attack = attack;
    }

    protected void setDefense(int defense) {
        this.defense = defense;
    }

    protected void setSpecialDefense(int specialDefense) {
        this.specialDefense = specialDefense;
    }

    public void setStunned(boolean stunned) {
        this.stunned = stunned;
        notifyObservator(1);
    }

    public void setDodging(boolean dodging) {
        this.dodging = dodging;
        notifyObservator(2);
    }


    public void addItem(Item item){
        if(items.contains(item))
            return;
        if(items.size() == 3)
            return;
        items.add(item);
    }

    private void notifyObservator(int state) {
        if(state == 1)
            observator.notificaStun();
        else
            observator.notificaDodge();
    }

    public void attachObservator(Observator observator){
        this.observator = observator;
    }

    // Intoarce totalul de stats al pokemonului
    // Metoda folosita pentru a determina cel mai puternic pokemon al unui player
    public int getStats(){
        return hp+attack+defense+specialDefense;
    }

    // Metoda save, pentru memento
    private PokemonMemento savePokemon(){
        return new PokemonMemento(this, hp, attack, defense, specialDefense);
    }

    // Metoda pentru healUp la finalul unei batalii (in cazul in care pierde)
    public void healUp(){
        backup.restore();

        dodging = false;
        stunned = false;
    }

    // Updateaza stats unui pokemon, in functie de ce iteme are
    // Metoda folosita dupa citirea unui pokemon.
    public void updateStats(){

        for (Item item : items) {

            hp += item.getHp();
            defense += item.getDefense();
            specialDefense += item.getSpecialDefense();
            if(special)
                attack += item.getSpecialAttack();
            else
                attack += item.getAttack();
        }

        backup = savePokemon();
    }

    // Updateaza stats unui pokemon cand acesta castiga.
    // +1 la toate stats
    public void levelUp(){
        backup.restore();
        hp++;
        attack++;
        defense++;
        specialDefense++;
        backup = savePokemon();

        dodging = false;
        stunned = false;
    }

    public void coolAbilities(){
        if(ability1 == null)
            return;
        ability1.decCooldown();
        ability2.decCooldown();
    }

    @Override
    public String toString() {
        return  name +
                ": hp= " + hp +
                ", attack= " + attack +
                ", defense= " + defense +
                ", specialDefense= " + specialDefense +
                ", special= " + special ;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Pokemon pokemon = (Pokemon) o;
        return name == pokemon.name;
    }

}
