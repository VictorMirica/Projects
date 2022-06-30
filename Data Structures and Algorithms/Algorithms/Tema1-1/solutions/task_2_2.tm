01.

start       #       L       sub1
            *       R       start

//incepem de la ultimul bit.
//facem trei scaderi de 1, succesive.
//daca descoperim un 1, il inlocuim cu 0

sub1        0       P1,L    sub1
            1       P0,H    go(sub2)

go(S)       #       L       S
            *       R       go(S)

sub2        0       P1,L    sub2
            1       P0,H    go(sub3)

sub3        0       P1,L    sub3
            1       P0,H    rewind

rewind      #       R       clean
            *       L       rewind

clean       0       P#,R    clean
            *       H       accept
