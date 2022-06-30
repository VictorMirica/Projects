ACDLRN%:&vxuwzyabg;.

// start: Write Initial Complete Configuration
// At the start of a computation,
// then, the tape of U contains a pair of e symbols marking the start of the
// tape, the standard description of T , written on the succeeding F-squares,
// and the symbol :: in the next F-square.
start                         H                    f(b1, b1, %)

b1                            R,R,P:,R,R,PD,R,R,PA,R,R,PD     anf

// anf: Mark Current Configuration
// The m-configuration anf looks for the last
// colon on the tape, marks the following configuration, part of the current
// complete configuration of T , with the symbol y, and then moves to
// m-configuration kom
anf            *               H                q(anf1,:)


anf1           *               H                con(kom,y)

// kom: Find Next Instruction
// U must now look for the instruction applicable to
// the current configuration of T.
kom             ;               R,Pz,L          con(kmp, x)
                z               L,L             kom
                *               L               kom

// kmp: Compare Configurations
// Next, the current configuration, marked with y,
// must be compared with the configuration in the current instruction, marked
// with x.  If they differ, any remaining x and y marks are erased and U moves
// back to m- configuration anf to inspect the next instruction. If they are the
// same, the applicable instruction has been located and U moves to
// m-configuration sim.
kmp             *               H               cpe(e(e(anf, x), y), sim, x, y)

// sim: Mark Instruction
// In m-configuration sim, the configuration in the
// current instruction is marked with blanks; this positions the machine after
// the configuration, and the rest of the instruction is marked up as follows.
// The z markings are then removed and the machine moves to the m-configuration
// mk.
sim                             H               f'(sim1,sim1,z)

sim1                            H               con(sim2, #)

sim2            A               H               sim3
                *               L,Pu,R,R,R      sim2

sim3            *               L,Py            e(mk,z)
                A               L,Py,R,R,R      sim2

// mk: Mark Complete Configuration
// In m-configuration mk, the current complete
// configuration, found after the last colon on the tape, is marked up as
// follows and terminated with a colon, and the machine moves the
// m-configuration sh.
mk                              H               q(mk1, :)

mk1             *               R,R             mk1
                A               L,L,L,L         mk2

mk2             C               R,Px,L,L,L      mk2
                :               H               mk4
                D               R,Px,L,L,L      mk3

mk3             *               R,Pv,L,L,L      mk3
                :               H               mk4

mk4                             H               con(l(l(mk5)),#)

mk5             *               R,Pw,R          mk5
                #               P:              sh

// sh: Show Output In m-configuration sh, the current instruction is examined to
// see if T produces any output. If it does, the appropriate symbol is written
// to U ’s tape before the machine moves to m-configuration inst.
sh                              H               f(sh1,inst,u)

sh1             *               L,L,L           sh2

sh2             D               R,R,R,R         sh3
                *               H               inst

sh3             C               R,R             sh4
                *               H               inst

sh4             C               R,R             sh5
                *               H               pe2(inst, 0, :)

sh5             C               H               inst
                *               H               pe2(inst, 1, :)

// inst: Write New Complete Configuration In m-configuration inst the new com-
// plete configuration is written at the end of the tape.
inst                            H               q(l(inst1), u)

inst1           L               R,E             ce5(ov, v, y, x, u, w)
                N               R,E             ce5(ov, v, x, y, u, w)
                R               R,E             ce5(q(inst2, A), v, x, u, y, w)

inst2                           R,R             inst3

inst3           #               PD              ov
                *               H               ov

// ov: Erase All Marks Finally, in m-configuration ov, all marks are removed
// from the tape and U returns to state anf to find and execute the next
// instruction of T .
ov                              H               e(anf)

// The m-function f(C, B, a)  finds the leftmost occurrence on the tape of the
// symbol a, and then moves to m-configuration C. If there is no occurrence of a
// on the tape, the machine moves to m-configuration B.
f(Y, X, a)      &               L               f1(Y, X, a)
                *               L               f(Y, X, a)

f1(Y, X, a)     a               H               Y
                #               R               f2(Y, X, a)
                *               R               f1(Y, X, a)

f2(Y, X, a)     a               H               Y
                #               R               X
                *               R               f1(Y, X, a)

// The m-function e(C, B, a) erases the leftmost occurrence on the tape of the
// symbol a, and then moves to m-configuration C. If there is no occurrence of a
// on the tape, the machine moves to m-configuration B
e(Y, X, a)                      H               f(e1(Y, X, a), X, a)

e1(Y, X, a)     *               E               Y


// The m-function e(B, a)  erases all occurrences on the tape of the symbol a, and
// then moves to m-configuration B.
e(X, a)                         H               e(e(X, a),X,a)

// The m-function pe(C, b)  prints the symbol b at the end of the sequence of
// symbols on the tape, and then moves to m-configuration C.
pe(Y, b)                        H               f(pe1(Y, b),Y,b)

pe1(Y, b)       *             R,R               pe1(Y,b)
                #             Pb                Y

// Prints two symbols at the end of the tape.
pe2(Y,a,b)                      H               pe(pe(Y,b),a)

// The m-function l(C) performs the basic operation L, and then moves to
// m-configuration C.
l(Y)             *              L               Y


// The m-function f′(C, B, a)  finds the leftmost occurrence on the tape of the
// symbol a, moves one square to the left, and then moves to m-configuration C.
// If there is no occurrence of a on the tape, the machine moves to
// m-configuration B.
f'(Y, X, a)                     H               f(l(Y), X, a)

// The m-function c(C, B, a)  finds the leftmost symbol on the tape marked with
// the symbol a, copies it to the end of the tape, and then moves to m-
// configuration C. If there is no symbol marked with a on the tape, the machine
// moves to m-configuration B
c(Y, X, a)                      H               f'(c1(Y), X, a)

c1(Y)           b                H              pe(Y, b)

// The m-function ce(C, B, a) finds the leftmost symbol on the tape marked with
// the symbol a, copies the symbol to the end of the tape, and then erases the
// symbol and moves to m-configuration C. If there is no symbol marked with a on
// the tape, the machine moves to m-configuration B.
ce(Y, X, a)                     H               c(e(Y, X, a),X,a)

// The m-function ce(B, a) copies all symbols marked with a to the end of the
// tape, erases them, and then moves to m-configuration B.
ce(X, a)                        H               ce(ce(X, a), X, a)

ce5(X, a, b, c, d, e)           H               ce(ce(ce(ce(ce(X, e), d), g), b), a)

// The m-function cp(C, A, G, a, b)  compares the first symbol on the tape
// marked with a and the first symbol marked with b. If there are no symbols
// marked with a or b, the machine moves to m-configuration G; if both exist,
// and the marked symbols are the same, it moves to m-configuration C;
// otherwise, it moves to m-configuration A.
cp(Y, Z, X, a, b)               H               f'(cp1(Y, Z, b), f(Z, X, b),a)

cp1(Y, Z, X)    g                 H             f'(cp2(Y, Z, g),Z,b)

cp2(Y, Z, g)    g                 H             Y
                *                 H             Z

// The m-function cpe(C, U, G, a, b)  does the same as cp(C, U, G, a, b) , but
// if symbols marked with a and b exist and are the same, the a and b are erased
cpe(Y, Z, X, a, b)               H              cp(e(e(Y, Y, b), Y, a), Z, X, a, b)

// The m-function cpe(U, G, a, b) compares the sequences of symbols on the tape
// marked with a and b. So long as they are the same, the as and bs are erased.
// If the sequences are identical, the machine moves to m-configur ation G when
// all the marks have been removed; it moves to m-configur- ation U when a
// difference is detected.
cpe(Z, G, a, b)                 H               cpe(cpe(Z, G, a, b), Z, G, a, b)

// The m-function q(C) moves to the end of the tape, identified by two
// consecutive blank squares, and then moves to m-configuration C.
q(Y)            *               R               q(Y)
                #               R               q1(Y)

q1(Y)           *               R               q(Y)
                #               H               Y


// The m-function q(C, a)  finds the last occurrence of a on the tape, and then
// moves to m-configuration C.
q(Y, a)                         H               q(q1(Y, a))

q1(Y, a)        a               H               Y
                *               L               q1(Y, a)

// The m-function e(C) erases all marks from the tape, and then moves to
// m-configuration C.
e(Y)            &               R               e1(Y)
                *               L               e(Y)

e1(Y)           *               R,E,R           e1(Y)
                #               R               Y

// An auxiliary table con(C, α)  is defined to carry out the common task of
// marking a configuration with a given symbol α.
con(Y, a)       *               R,R             con(Y,a)
                A               L,Pa,R          con1(Y,a)

con1(Y,a)       A               R,Pa,R          con1(Y,a)
                D               R,Pa,R          con2(Y,a)

con2(Z,a)       C               R,Pa,R          con2(Z,a)
                *               R,R             Z
