package com.pokemon;

public class PokemonMemento {

    // Memento pentru clasa pokemon
    // Aceasta va tine minte o fosta "versiune" a pokemonului (hp, attack etc.)
    // Dupa o lupta, pokemonul va fi intors la starea lui anterioara (healUp)
    // Dupa un levelUp, starea noua a pokemonului va fi memorata

    private final Pokemon pokemon;
    private final int hp;
    private final int attack;
    private final int defense;
    private final int specialDefense;

    public PokemonMemento(Pokemon pokemon, int hp, int attack, int defense, int specialDefense) {
        this.pokemon = pokemon;
        this.hp = hp;
        this.attack = attack;
        this.defense = defense;
        this.specialDefense = specialDefense;
    }

    public void restore(){
        pokemon.setHp(hp);
        pokemon.setAttack(attack);
        pokemon.setDefense(defense);
        pokemon.setSpecialDefense(specialDefense);
    }


}
