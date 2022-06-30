01BX.

//starea start pune un indicator de final 'B' la finalul cuvantului

start     #        PB      shiftright
          *        R       start
           

//Ne intoarcem la inceputul cuvantului si incepem sa comparam

rewind(S)   #       R       S
            *       L       rewind(S)

//Comparam cu 8 => 0b1000 asadar, trebuie sa verificam
//doar priul bit din cei 4

compare     1       H       greater
            0       H       less

//In cazul less, ne mutam la dreapta 4 biti

less        *       R       next(right1)

next(S)     *       R       right(S)

right(S)       *       R       S

right1      *       R       test

//inainte sa comparam dinnou, testam daca am ajuns la finalul cuv

test        B       H       shiftright       
            *       H       compare

//in cazul in care am ajuns la final, shiftam cuvantul la dreapta
//Nu shiftam si indicatorul B, sarim peste el
//La inceputul cuvantului adaugam un 0.

shiftright  *       R       shiftright
            #       L       cpy

cpy         #       R         removex
            X       L         cpy
            B       L         cpy
            *       PX,R      move(*)

move(d)     #       Pd,L    cpy
            X       Pd,L    cpy
            *       R       move(d)

removex     X       P0,R       rewind(testend)
            *       R          removex

//Dupa fiecare shiftare, verificam daca am shiftat tot cuvantul
//aceasta verificare se va face in felul urmator: 
//rewind, dupa care cautam cel puitin un '1' inainte sa 
//ajungem la indicatorul 'B'

testend     1       H          rewind(compare)
            0       R          testend
            B       H          rewind(clean)

//starea clean curata banda de 0 si de B

clean       0       P#,R       clean
            B       P#         accept

greater     *       R       next(sub)

//In cazul in care nuamrul este mai mare ce 8 trebuie scazut 3
//facem 3 scaderi de 1 consecutive, la finalul scaderilor
//cursorul va fi pus la finalul celor 4 biti si se va continua
//compararea urmatorilor 4 biti.

sub         0       P1,L    carry1(sub1)
            1       P0,H    sub1

sub1        0       P1,L    carry1(sub2)
            1       P0,H    sub2

sub2        0       P1,L    carry1(right1)
            1       P0,H    right1

carry1(S)   0       P1,L    carry2(S)
            1       P0,R    S

carry2(S)   0       P1,L    carry3(S)
            1       P0,R    goright(S)

goright(S)  *       R       S

carry3(S)   1       P0,R    goright2(S)

goright2(S)    *       R       goright3(S)

goright3(S)    *        R       S
