01XY.

start       #       PY      gostart
            *       R       start

//Marcam finalul cuvantului cu Y

gostart     #       R       cpy
            X       R       testy
            *       L       gostart

//Ne mutam la inceput si incepem copierea

testy       Y       R       shl
            *       H       cpy

//In cazul in care un X este urmat de Y
//am shiftat tot cuvantul

cpy         *       PX      move(*)

move(d)     #       Pd      gostart
            *       R       move(d)

//Curatam banda de Y

shl         #       L       end
            Y       R       shl
            *       PY,L    shift(*)


shift(d)    *       Pd,R    shl

end         *       P#      accept
