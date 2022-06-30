X01.

start     #   P#,H    accept
            X   PX,R    start
            c   PX,L    shift(c)

shift(c)    #   Pc,R    return
            X   PX,L    shift(c)
            *   Pc,L    shift(*)

return      X   PX,R    start
            *   P*,R    return
