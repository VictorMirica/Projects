package com.pokemon;

public class PokemonFactory {

    //Factory pentru clasa pokemon
    //De asemenea este si un singleton
    private static PokemonFactory unique;

    private PokemonFactory(){}

    public static PokemonFactory Instanta(){
        if(unique == null)
            unique = new PokemonFactory();
        return unique;
    }

    public Pokemon creeazaPokemon(PokemonType  p) {
        return switch (p) {
            case neutrel1 -> new Pokemon(p, 10, 3, 1, 1, false, null, null);
            case neutrel2 -> new Pokemon(p, 20, 4, 1, 1, false, null, null);

            case pikachu -> new Pokemon(p, 35, 3, 2, 3, true,
                    new Ability(6, false, false, 4), new Ability(4, true, true, 5));

            case bulbasaur -> new Pokemon(p, 42, 5, 3, 1, true,
                    new Ability(6, false, false, 4), new Ability(5, false, false, 3));

            case charmander -> new Pokemon(p, 50, 4, 3, 2, false,
                    new Ability(4, true, false, 4), new Ability(7, false, false, 6));

            case squirtle -> new Pokemon(p, 60, 3, 5, 5, true,
                    new Ability(4, false, false, 3), new Ability(2, true, false, 2));

            case snorlax -> new Pokemon(p, 62, 3, 6, 4, false,
                    new Ability(4, true, false, 5), new Ability(0, false, true, 5));

            case vulpix -> new Pokemon(p, 36, 5, 2, 4, false,
                    new Ability(8, true, false, 6), new Ability(2, false, true, 7));

            case eevee -> new Pokemon(p, 39, 4, 3, 3, true,
                    new Ability(5, false, false, 3), new Ability(3, true, false, 3));

            case jigglypuff -> new Pokemon(p, 34, 4, 2, 3, false,
                    new Ability(4, true, false, 4), new Ability(3, true, false, 4));

            case meowth -> new Pokemon(p, 41, 3, 4, 2, false,
                    new Ability(5, false, true, 4), new Ability(1, false, true, 3));

            case psyduck -> new Pokemon(p, 43, 3, 3, 3, false,
                    new Ability(2, false, false, 4), new Ability(2, true, false, 5));
        };

    }
}
