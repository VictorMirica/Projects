package com.io;

import com.aventura.Trainer;
import com.pokemon.Pokemon;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Logger {

    // Clasa statica, folosita pentru scrierea in logger ce se intampla
    // la inceputul, la finalul si in timpul unei batalii
    private static BufferedWriter bufferedWriter;
    private static final boolean toFile;

    static {
        Scanner scanner = new Scanner(System.in);
        toFile = scanner.nextBoolean();
        scanner.close();
    }

    private static void write(StringBuilder str) {

        try {
            bufferedWriter.write(String.valueOf(str));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void logBattle(Pokemon pokemon1, Pokemon pokemon2){
        StringBuilder str = new StringBuilder("Battle: " + pokemon1.getName() + " vs " + pokemon2.getName());
        str.append("\n");
        str.append(pokemon1);
        str.append("\n");
        str.append(pokemon2);
        str.append("\n\n");

        if(toFile) {
            write(str);
        }else
            System.out.println(str);

    }

    public static void logAction(Pokemon pokemon, String string){
        String str = pokemon.getName() + string + "\n";

        if(toFile) {
            write(new StringBuilder(str));
        }else
            System.out.println(str);
    }

    public static void logActionResults(Pokemon pokemon, Pokemon enemy){
        StringBuilder str = new StringBuilder( pokemon.getName() + " hp : " + pokemon.getHp());
        str.append("\n");
        str.append(enemy.getName()).append(" hp : ").append(enemy.getHp());
        str.append("\n\n");

        if(toFile) {
            write(str);
        }else
            System.out.println(str);
    }

    public static void logArenaStart(Trainer player1, Trainer player2){
        String str = "Arena: " + player1.getName() + " vs " + player2.getName() +"\n";

        if(toFile) {
            write(new StringBuilder(str));
        }else
            System.out.println(str);
    }

    public static void logEventStart(){
        String str = """
                ==============================================================

                """;

        if(toFile) {
            write(new StringBuilder(str));
        }else
            System.out.println(str);
    }

    public static void  logBattleWinner(Pokemon pokemon){
        String str = pokemon.getName() + " won!\n" +
                pokemon.getName() + " leveled up! " + pokemon + "\n\n\n";

        if(toFile) {
            write(new StringBuilder(str));
        }else
            System.out.println(str);
    }

    public static void logBattleDraw(){
        String str = "draw!" + "\n";

        if(toFile) {
            write(new StringBuilder(str));
        }else
            System.out.println(str);
    }

    public static void logArenaWinner(Trainer trainer){
        String str = trainer.getName() + " aged " + trainer.getAge() + " won!" + "\n";

        if(toFile) {
            write(new StringBuilder(str));
        }else
            System.out.println(str);

    }

    public static void errorMsg(String str){
        if(toFile) {
            write(new StringBuilder(str));
        }else
            System.out.println(str);
    }

    public static void start(int i){
        //citire

        try {
            FileWriter fileWriter = new FileWriter("./src/com/io/logs/log" + i, false);
            bufferedWriter = new BufferedWriter(fileWriter);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void close(){
        try {
            bufferedWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
