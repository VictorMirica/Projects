01.

start       1       R       count1
            0       H       less
            *       R       start

//testam daca cuvantul are mai mult sau mai putin
//de 3 simboluri.

count1      #       H       less
            *       R       count2

count2      #       H       less
            *       R       count3

count3      #       L       startcomp
            *       H       greater

//daca acesta are exact 3 caractere, incepem
//comparatia, incepand cu ultimul caracter

startcomp   *       L       compara

compara     1       H       greater
            0       R       final

final       0       H       less
            1       H       greater

//Cuvantul e mai mare, stergem si scriem 1

greater     *      H        rewind(stop(1)) 

rewind(S)   #      R        S
            *      L        rewind(S) 

stop(d)     #      Pd       accept
            *      P#,R     stop(d)           

//cuvantul e mai mic, stergem si scriem 0

less        *      L        rewind(stop(0)) 
