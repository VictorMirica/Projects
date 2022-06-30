01XY.

start       #       PY      goend
            *       L       start

//Vom marca inceputul cuvantului cu simbolul Y
//Vom incepe sa mutam simboluri de la final.

goend       #       L       cpy
            X       L       testy
            *       R       goend

//La finalul cuvantului se va afla un # sau X
//in cazul lui X, inainte de a copia simbolul, verificam
//Daca am terminat de copiat tot cuvantul

testy       Y       L       shr
            *       H       cpy

cpy         *       PX      move(*)

move(d)     #       Pd      goend
            *       L       move(d)

//In final, vom shifta cuvantul la dreapta cu un spatiu
//in scopul de a-l elimina pe Y

shr         #       R       end
            Y       L       shr
            *       PY,R    shift(*)


shift(d)    *       Pd,L    shr

end         *       P#      accept
