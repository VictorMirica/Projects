01.

start       #       L       add1
            *       R       start

//incepem de la finalul cuvantului
//adaugam 1, de trei ori

add1        0       P1,H    go(add2)
            1       P0,L    add1
            #       P1,H    go(add2)

go(S)       #       L       S
            *       R       go(S)

add2        0       P1,H    go(add3)
            1       P0,L    add2
            #       P1,H    go(add3)

add3        0       P1,H    accept
            1       P0,L    add3
            #       P1,H    accept           
