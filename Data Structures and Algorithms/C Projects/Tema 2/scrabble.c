#include "./util/scrabble.h"
#include "./util/print_board.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

char game_board[15][15];
int scor[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

void taskZero(){
    
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            game_board[i][j] = '.';
        }
    }

    print_board(game_board);

}

void taskOne(){
    int n;
    char str_n[20];

    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            game_board[i][j] = '.';
        }
    }

    fgets(str_n, 10, stdin);
    n = strtol(str_n, NULL, 0);

    for(int i = 0; i < n; i++){
        char text[100];
        int x = 0, y = 0, d = 0, cuvlen = 0;
        int par1 = 0;
        int par2 = 0;
        char str_y[50], str_x[50], str_d[50], cuv[50];

        memset(cuv, '\0', sizeof cuv);        
        memset(text, '\0', sizeof text);
        memset(str_x, '\0', sizeof str_x);
        memset(str_n, '\0', sizeof str_n);
        memset(str_y, '\0', sizeof str_y);
    
        fgets(text, 100, stdin);

        for(int j = 0; j < 4; j++){
            while(1){
                if((text[par2] == ' ') | (text[par2] == '\0') | (text[par2] == '\n')){

                    switch (j){
                    case 0:
                        strncpy(str_y, (text + par1), par2-par1);
                        y = strtol(str_y, NULL, 0);
                        break;
                    case 1:
                        strncpy(str_x, (text + par1), par2-par1);
                        x = strtol(str_x, NULL, 0);
                        break;
                    case 2:
                        strncpy(str_d, (text + par1), par2-par1);
                        d = strtol(str_d, NULL, 0);
                        break;
                    case 3:
                        strncpy(cuv, (text + par1), par2-par1);
                        cuvlen = par2-par1;
                        break;
                    default:
                        break;
                    }
                    par2++;
                    par1 = par2;
                    break;
                }
                par2++;
            }
        }

        game_board[y][x] = cuv[0];
        if(d == 0){
            for(int j = 1; j < cuvlen; j++){
                game_board[y][x + j] = cuv[j];
            }
        }else{
            for(int j = 1; j < cuvlen; j++){
                game_board[y + j][x] = cuv[j];   
            }
        }
    }

    print_board(game_board);
}

void calcScor(int* n, int* points,int* p1Points, int* p2Points, char* str_n, char* str_xx, char* str_yy ){
    int whichP =0;
    for(int i = 0; i < *n; i++){
        char text[100];
        int x = 0, y = 0, d = 0, cuvlen = 0;
        int par1 = 0;
        int par2 = 0;
        char str_y[50], str_x[50], str_d[50], cuv[50];
        int canTriple = 0;
        int canDouble = 0;
        int willTriple = 0;
        int willDouble = 0;
        int doubleCount = 0;
        int tripleCount = 0;
        int res1=1;
        int res2=1;
                

        memset(cuv, '\0', sizeof cuv);        
        memset(text, '\0', sizeof text);
        memset(str_x, '\0', sizeof str_x);
        memset(str_n, '\0', sizeof 20);
        memset(str_y, '\0', sizeof str_y);
    
        fgets(text, 100, stdin);

        for(int j = 0; j < 4; j++){
            while(1){
                if((text[par2] == ' ') | (text[par2] == '\0') | (text[par2] == '\n')){

                    switch (j){
                    case 0:
                        strncpy(str_y, (text + par1), par2-par1);
                        y = strtol(str_y, NULL, 0);
                        break;
                    case 1:
                        strncpy(str_x, (text + par1), par2-par1);
                        x = strtol(str_x, NULL, 0);
                        break;
                    case 2:
                        strncpy(str_d, (text + par1), par2-par1);
                        d = strtol(str_d, NULL, 0);
                        break;
                    case 3:
                        strncpy(cuv, (text + par1), par2-par1);
                        cuvlen = par2-par1;
                        break;
                    default:
                        break;
                    }
                    par2++;
                    par1 = par2;
                    break;
                }
                par2++;
            }
        }

        if((cuv[cuvlen-1] == *(str_yy + 1)) & (cuv[cuvlen-2] == *str_yy)){
            canTriple = 1;
        }

        for(int j = 0; j < (cuvlen - 1); j++){
            if((cuv[j+1] == *(str_xx +1)) & (cuv[j] == *str_xx)){
                canDouble = 1;
            }
        }

        for(int j = 0; j < 100; j++){
            int count = 0;
            for(int k=0; k<cuvlen; k++){
                if(cuv[k] == words[j][k]){
                    count++;
                }
            }
            if(count == cuvlen){
                memset(words[j], '-', 1);
                break;
            }
        }

        if(d == 0){
            for(int j = 0; j < cuvlen; j++){
                game_board[y][x + j] = cuv[j];
                if (canTriple){
                    if (bonus_board[y][x+j] == 2){
                        willTriple = 1;
                        tripleCount++;
                    }
                }
                if(canDouble){
                    if (bonus_board[y][x+j] == 1){
                        willDouble = 1;
                        doubleCount++;
                    }
                }
            }
        }else{
            for(int j = 0; j < cuvlen; j++){
                game_board[y + j][x] = cuv[j];  
                if (canTriple){
                    if (bonus_board[y + j][x] == 2){
                        willTriple = 1;
                        tripleCount++;
                    }
                }
                if(canDouble){
                    if (bonus_board[y+j][x] == 1){
                        willDouble = 1;
                        doubleCount++;
                    }
                }
            }
        }

        for (int j = 0; j < cuvlen; j++){
            *points += scor[cuv[j] - 'A'];
        }
    
        if(willTriple){
            while (tripleCount != 0) {
                res2 *= 3;
                --tripleCount;
            }
            *points = (*points*res2);
        }

        if(willDouble){
            while (doubleCount != 0) {
                res1 *= 2;
                --doubleCount;
            }
            *points = (*points*res1);
        }
        


        if (whichP % 2 == 0){
            *p1Points += *points;
        }else{
            *p2Points += *points;
        }
        whichP++;
        *points = 0;
    }
}

void taskTwo(){

    int points = 0;
    int p1Points = 0;
    int p2Points = 0;
    int n;
    char str_n[20];
    char str_xx[2] = {'-','-'};
    char str_yy[2] = {'-','-'};

    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            game_board[i][j] = '.';
        }
    }

    fgets(str_n, 10, stdin);
    n = strtol(str_n, NULL, 0);

    calcScor(&n, &points, &p1Points, &p2Points, str_n, str_xx, str_yy );


    printf("Player 1: %d Points\n", p1Points);
    printf("Player 2: %d Points\n", p2Points);
}



void taskThree(){
    int points = 0;
    int p1Points = 0;
    int p2Points = 0;
    int n;
    char str_n[20];
    char str_xx[2];
    char str_yy[2];

    fgets(str_xx, 5, stdin);
    fgets(str_yy, 5, stdin);

    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            game_board[i][j] = '.';
        }
    }

    fgets(str_n, 10, stdin);
    n = strtol(str_n, NULL, 0);

    calcScor(&n, &points, &p1Points, &p2Points, str_n, str_xx, str_yy );

    printf("Player 1: %d Points\n", p1Points);
    printf("Player 2: %d Points\n", p2Points);
}

void findWord(int* p1Points, int* p2Points, char* str_xx, char* str_yy, int* highScore ,int* isVertical, int* isHorizontal, int* winnerX, int* winnerY, char** cuvantCastigator){
    int points = 0;
    for(int k=0; k<100; k++){
        for (int i=0; i<15;i++){
            for(int j=0; j<15; j++){
                if(words[k][0] == game_board[i][j]){
                    int orizontal = 1;
                    int vertical = 1;
                    int canTriple = 0;
                    int canDouble = 0;

                    if((words[k][(int)strlen(words[k])-1] == *(str_yy +1)) & (words[k][(int)strlen(words[k])-2] == *str_yy)){
                            canTriple = 1;
                        }

                    for(int l = 0; l < ((int)strlen(words[k]) - 1); l++){
                        if((words[k][l+1] == *(str_xx + 1)) & (words[k][l] == *str_xx)){
                            canDouble = 1;
                        }
                    }

                    if((j+(int)strlen(words[k])>15)){
                        orizontal=0;
                    }
                    if((i+(int)strlen(words[k])>15)){
                        vertical=0;
                    }
                    if(orizontal){
                        for(int l=1; l<(int)strlen(words[k]); l++){
                            if(game_board[i][j+l] != '.'){
                                orizontal = 0;
                            }
                        }
                    }
                    if(orizontal){
                        points = 0;
                        int willTriple = 0;
                        int willDouble = 0;
                        int tripleCount =0;
                        int doubleCount =0;
                        int res1 = 1;
                        int res2 = 1;
                        
                        for(int l = 0; l < ((int)strlen(words[k])); l++){
                            if (canTriple){
                                if (bonus_board[i][j+l] == 2){
                                    willTriple = 1;
                                    tripleCount++;
                                }
                            }
                            if(canDouble){
                                if (bonus_board[i][j+l] == 1){
                                    willDouble = 1;
                                    doubleCount++;
                                }
                            }
                        }

                        for (int l = 0; l < ((int)strlen(words[k])); l++){
                            points += scor[words[k][l] - 'A'];
                        }
                    
                        if(willTriple){
                            while (tripleCount != 0) {
                                res2 *= 3;
                                --tripleCount;
                            }
                            points = (points*res2);
                        }

                        if(willDouble){
                            while (doubleCount != 0) {
                                res1 *= 2;
                                --doubleCount;
                            }
                            points = (points*res1);
                        }
                        
                        if((*p2Points+points >= *p1Points) & (*p2Points+points >= *highScore)){
                            int winner=1;
                            if(*highScore == *p2Points+points){
                                winner = 0;
                                if(i < *winnerX){
                                    winner=1;
                                }
                                if((i == *winnerX) & (j < *winnerY)){
                                    winner=1;
                                }
                            }
                            if(winner){
                                *highScore = *p2Points+points;
                                *isHorizontal = 1;
                                *isVertical = 0;
                                *winnerX=i;
                                *winnerY=j;
                                *cuvantCastigator = calloc((int)strlen(words[k]), sizeof(char));
                                for (int l = 0; l < (int)strlen(words[k]); l++){
                                    *(*cuvantCastigator + l)=words[k][l];
                                }
                            }
                        }

                       
                    }
                    if(vertical){
                        for(int l=1; l<(int)strlen(words[k]); l++){
                            if(game_board[i+l][j] != '.'){
                                vertical = 0;
                            }
                        }
                    }
                    if(vertical){
                        points = 0;
                        int willTriple = 0;
                        int willDouble = 0;
                        int tripleCount =0;
                        int doubleCount =0;
                        int res1 = 1;
                        int res2 = 1;
                        
                        for(int l = 0; l < ((int)strlen(words[k])); l++){
                            if (canTriple){
                                if (bonus_board[i + l][j] == 2){
                                    willTriple = 1;
                                    tripleCount++;
                                }
                            }
                            if(canDouble){
                                if (bonus_board[i+l][j] == 1){
                                    willDouble = 1;
                                    doubleCount++;
                                }
                            }
                        }

                        for (int l = 0; l < ((int)strlen(words[k])); l++){
                            points += scor[words[k][l] - 'A'];
                        }
                    
                        if(willTriple){
                            while (tripleCount != 0) {
                                res2 *= 3;
                                --tripleCount;
                            }
                            points = (points*res2);
                        }

                        if(willDouble){
                            while (doubleCount != 0) {
                                res1 *= 2;
                                --doubleCount;
                            }
                            points = (points*res1);
                        }
                        
                       if((*p2Points+points >= *p1Points) & (*p2Points+points >= *highScore)){
                            int winner=1;
                            if(*highScore == *p2Points+points){
                                winner=0;
                                if(i < *winnerX){
                                    winner=1;
                                }
                                if((i == *winnerX) & (j < *winnerY)){
                                    winner=1;
                                }
                            }
                            if(winner){
                                *highScore = *p2Points+points;
                                *isHorizontal = 0;
                                *isVertical = 1;
                                *winnerX=i;
                                *winnerY=j;
                                *cuvantCastigator = calloc((int)strlen(words[k]), sizeof(char));
                                for (int l = 0; l < (int)strlen(words[k]); l++){
                                    *(*cuvantCastigator + l)=words[k][l];
                                }
                            }
                        }                        
                    }
                }
            }
        }
    }
    for(int j = 0; j < 100; j++){
        int count = 0;
        for(int k=0; k<(int)strlen(*cuvantCastigator); k++){
            if(*(*cuvantCastigator + k) == words[j][k]){
                count++;
            }
        }
        if(count == (int)strlen(*cuvantCastigator)){
            memset(words[j], '-', 1);
            break;
        }
    }
}

void taskFour(){
    int n;
    char str_n[20];
    char str_xx[2];
    char str_yy[2];
    int points = 0;
    int p1Points = 0;
    int p2Points = 0;

    fgets(str_xx, 5, stdin);
    fgets(str_yy, 5, stdin);

    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            game_board[i][j] = '.';
        }
    }

    fgets(str_n, 10, stdin);
    n = strtol(str_n, NULL, 0);

    calcScor(&n, &points, &p1Points, &p2Points, str_n, str_xx, str_yy );


    for(int k=0; k<100; k++){
        for (int i=0; i<15;i++){
            for(int j=0; j<15; j++){
                if(words[k][0] == game_board[i][j]){
                    int orizontal = 1;
                    int vertical = 1;
                    if((j+(int)strlen(words[k])>15)){
                        orizontal=0;
                    }
                    if((i+(int)strlen(words[k])>15)){
                        vertical=0;
                    }
                    if(orizontal){
                        for(int l=1; l<(int)strlen(words[k]); l++){
                            if(game_board[i][j+l] != '.'){
                                orizontal = 0;
                            }
                        }
                    }
                    if(orizontal){
                        for(int l=1; l<(int)strlen(words[k]); l++){
                            game_board[i][j+l] = words[k][l];
                        }
                        print_board(game_board);
                        return;
                    }
                    if(vertical){
                        for(int l=1; l<(int)strlen(words[k]); l++){
                            if(game_board[i+l][j] != '.'){
                                vertical = 0;
                            }
                        }
                    }
                    if(vertical){
                        for(int l=1; l<(int)strlen(words[k]); l++){
                            game_board[i+l][j] = words[k][l];
                        }
                        print_board(game_board);
                        return;
                    }
                }
            }
        }
    }
}

void taskFive(){
    int points = 0;
    int p1Points = 0;
    int p2Points = 0;
    int n;
    char str_n[20];
    char str_xx[2];
    char str_yy[2];

    fgets(str_xx, 5, stdin);
    fgets(str_yy, 5, stdin);

    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            game_board[i][j] = '.';
        }
    }

    fgets(str_n, 10, stdin);
    n = strtol(str_n, NULL, 0);

    calcScor(&n, &points, &p1Points, &p2Points, str_n, str_xx, str_yy );

    
    int highScore = 0;
    int isVertical = 0;
    int isHorizontal = 0;
    int winnerX = 0;
    int winnerY = 0;
    char* cuvantCastigator;
    cuvantCastigator = calloc(1, sizeof(char));

    findWord(&p1Points, &p2Points, str_xx, str_yy, &highScore , &isVertical, &isHorizontal, &winnerX, &winnerY, &cuvantCastigator);

    
    if (highScore==0){
        printf("Fail!");
        return;
    }
    if(isHorizontal){
        for(int l=1; l<(int)strlen(cuvantCastigator); l++){
            game_board[winnerX][winnerY+l] = cuvantCastigator[l];
        }
        print_board(game_board);
        return;

    }
    if(isVertical){
        for(int l=1; l<(int)strlen(cuvantCastigator); l++){
            game_board[winnerX+l][winnerY] = cuvantCastigator[l];
        }
        print_board(game_board);
        return;

    }

}

void taskSix(){
    int points = 0;
    int p1Points = 0;
    int p1Points2 = 0;
    int p2Points = 0;
    int n;
    char str_n[20];
    char str_xx[2];
    char str_yy[2];
    int one = 1;
    int zero = 0;

    fgets(str_xx, 5, stdin);
    fgets(str_yy, 5, stdin);

    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            game_board[i][j] = '.';
        }
    }

    fgets(str_n, 10, stdin);
    n = strtol(str_n, NULL, 0);

    for(int a = 0; a < n; a++){
        calcScor(&one, &points, &p1Points, &p1Points2, str_n, str_xx, str_yy );
        int highScore = 0;
        int isVertical = 0;
        int isHorizontal = 0;
        int winnerX = 0;
        int winnerY = 0;
        char* cuvantCastigator;
        cuvantCastigator = calloc(1, sizeof(char));
        findWord(&p1Points, &p2Points, str_xx, str_yy, &highScore , &isVertical, &isHorizontal, &winnerX, &winnerY, &cuvantCastigator);
        if(highScore == 0){
            findWord(&zero, &p2Points, str_xx, str_yy, &highScore , &isVertical, &isHorizontal, &winnerX, &winnerY, &cuvantCastigator);
        }
        p2Points = highScore;
        
        if(isHorizontal){
            for(int l=1; l<(int)strlen(cuvantCastigator); l++){
                game_board[winnerX][winnerY+l] = cuvantCastigator[l];
            }
        }
        if(isVertical){
            for(int l=1; l<(int)strlen(cuvantCastigator); l++){
                game_board[winnerX+l][winnerY] = cuvantCastigator[l];
            }
        }
    }

    print_board(game_board);
    if(p1Points > p2Points){
        printf("Player 1 Won!\n");
    }else{
        printf("Player 2 Won!\n");
    }
}


int main(){
    char task[10];
    fgets(task, 10, stdin);

    if(task[0] == '0'){
        taskZero();
        return 1;
    }

    if(task[0] == '1'){
        taskOne();
        return 1;
    }
    
    if(task[0] == '2'){
        taskTwo();
        return 1;
    }

    if(task[0] == '3'){
        taskThree();
        return 1;
    }

    if(task[0] == '4'){
        taskFour();
        return 1;
    }

    if(task[0] == '5'){
        taskFive();
        return 1;
    }

    if(task[0] == '6'){
        taskSix();
        return 1;
    }

}
    