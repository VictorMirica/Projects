package com.aventura;

import com.io.GetFileInfo;
import com.io.Logger;

import java.io.File;
import java.io.FileNotFoundException;

public class Main {

    // Observator - pokemon - stunned + dodge
    // Memento - pokemon - levelUp(takeSnapshot), updateStats(restore)
    // Builder - items
    // Factory - pokemon
    // Singleton - pokemonFactory

    // tipurile de teste:
    // test 10 - un pokemon in minus        |
    // test 9 - un pokemon in plus          | Expected: Mesaj in systemOut + Skip to next input file
    // test 8 - acelasi pokemon de 2 ori    |
    //
    // test 7 - acelasi item de 2 ori -> expected ignorare item duplicat
    // test 6 - mai mult de 3 iteme -> expected continuare doar cu primele 3 iteme
    // test 5 - fiecare pokemon are cate o sabiuta
    // test 4 - toti pokemonii au maximul de iteme
    // test 3 - itemele sunt mirrored
    // test 2 - nimeni nu are iteme :(
    // test 1 - nimic special

    // Fisierele de input respectiv output (log) se afla in com.io.inputs/outputs
    // Pentru output, vom scrie true daca afisarea se va face in fisier, false in caz de sout.

    public static void main(String[] args) {
        Trainer player1;
        Trainer player2;

        // Sunt 10 fisiere de input
        for(int i = 1; i <= 10; i++) {
            Logger.start(i);
            File file = new File("./src/com/io/inputs/input" + i);
            try {
                Trainer[] trainers = GetFileInfo.readTrainerInfo(file);
                if(trainers == null)
                    continue;
                player1 = trainers[0];
                player2 = trainers[1];
            } catch (FileNotFoundException e) {
                Logger.errorMsg("File not found\n");
                Logger.close();
                return;
            }

            if (player1 != null && player2 != null) {
                Logger.logArenaStart(player1, player2);
                Trainer winner = Arena.fight(player1, player2);
                if (winner == null) {
                    Logger.logBattleDraw();
                } else
                    Logger.logArenaWinner(winner);
                Logger.close();
            }
        }
    }
}
