01XB.

start           #       PB      shiftleft
                *       L       start

//marcam cu B locul unde incep numerele in BIN
//(inceputul cuvantului)
//La inceput vom shifta cuvantul la stanga cu o casuta

shiftleft   #       R       cpy
            *       L      shiftleft
            
cpy         #       L         removex
            X       R         cpy
            B       R         cpy
            *       PX,L      move(*)

move(d)     #       Pd,R    cpy
            X       Pd,R    cpy
            *       L       move(d)

//Pentru shiftare ne vom folosi de un X
//acest X va fi sters la finalul shiftarii
//dupa stergere, se testeaza daca am shiftat tot cuv

removex     X       P#,L       testend
            *       L          removex

testend     B       P#,L       goend
            *       H          gotob

//Mergem la finalul cuvantului (in BCD)
//si testam grupui de 4 biti 

gotob       B       H          nextfour(check)
            *       L          gotob

nextfour(S)    *       L      left(S)

left(S)        *       L      left1(S)

left1(S)       *       L      left2(S)

left2(S)     *       L      S

//veirifcam bit cu bit, cei 4 biti
//Acestia se vor compara cu 5 (0b101)

check       #       R      check1
            *       H      compare

check1      #       R      shiftleft1
            *       L      compare 

shiftleft1   #       R      shiftleft1
             *       H      cpy

compare     1       H      greater     
            *       R      compare1

compare1    0       L      less 
            1       R      compare2

compare2    1       L      left2(greater)
            0       R      compare3
            
compare3    1       L      left1(greater)
            0       L      left1(less)

//Daca bitii sunt mai mici, trecem la urmatorii 4

less        *       H      nextfour(check)

//Daca acestia sunt mai mari, vom adauga 3

greater     *       H      right(add)

right(S)    *       R      right1(S)

right1(S)   *       R      right2(S)

right2(S)   *       R      S

add         0       P1,R    carry(add1)
            1       PX,L    add
            #       P1,R    carry(add1)

add1        0       P1,R    carry(add2)
            1       PX,L    add1
            #       P1,R    carry(add2)

add2        0       P1,R    carry(left(nextfour(check)))
            1       PX,L    add2
            #       P1,R    carry(left(nextfour(check)))

carry(S)       X       P0,R    carry(S)
               *       L       S

//Mergem din 4 in 4 biti, pana la inceput pentru
//a formata corect cuvantul

goend       #       L       nextfour(format)
            *       R       goend

format      #       R       checkformat
            *       H       nextfour(format)
            
checkformat #       P0,R    checkformat
            *       H       accept
