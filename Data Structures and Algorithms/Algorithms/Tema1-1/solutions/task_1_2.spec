0 1 #
start
accept
start 1 q0 1 R
start 0 q1 0 H
start # start # R
q0 # q1 # H
q0 0 q2 0 R
q0 1 q2 1 R
q2 # q1 # H
q2 0 q3 0 R
q2 1 q3 1 R
q3 # q4 # L
q3 0 q5 0 H
q3 1 q5 1 H
q4 0 q6 0 L
q4 # q6 # L
q4 1 q6 1 L
q6 1 q5 1 H
q6 0 q7 0 R
q6 # q6 # H
q7 0 q1 0 H
q7 1 q5 1 H
q7 # q7 # H
q5 0 q8 0 H
q5 # q8 # H
q5 1 q8 1 H
q1 0 q9 0 L
q1 # q9 # L
q1 1 q9 1 L
q10 # accept 0 H
q10 0 q10 # R
q10 1 q10 # R
q9 # q10 # R
q9 0 q9 0 L
q9 1 q9 1 L
q11 # accept 1 H
q11 0 q11 # R
q11 1 q11 # R
q8 # q11 # R
q8 0 q8 0 L
q8 1 q8 1 L