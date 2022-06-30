Mirica Victor-Nicolae 324CB
 
    Demonstratie reducere kClique ≤p SAT

Deoarece SAT este NPC, stim ca orice problema NP (spre exemplu k-Clique) se
poate reduce la SAT.

n reprezinta numarul de noduri din graf
k reprezinta marimea clicii pe care vrem sa o indentificam.

Literali:

Primim ca input graful G=(V,E)
Literalii vor fi de tipul x(i,v), 1 ≤ i ≤ k, 1 ≤ v ≤ n.
Acestia vor reprezenta faptul ca nodul v este al i-lea nod din clică.

Clauze:

1.  Pentru fiecare i (1 ≤ i ≤ k), trebuie sa fie un not in clică care să ii
    corespundă.

2.  Pentru fiecare i,j (1 ≤ i < j ≤ k), nodul din clică care ii corespunde lui
    i este diferit de cel care ii corespunde lui j.

3.  Pentru fiecare două noduri u,v care nu sunt legate de o muchie (u,v)∉E,
    u si v nu pot face parte din aceeasi clică.

Forma normal conjunctivă rezultata va fi satisfiabilă dacă si numai dacă graful G 
are o clică de lungime k in el.

Această reducere are Θ(n^2*k^2) clauze. Dupa cum observam faptul ca k "variază", adică
este proprotional cu n, putem ajunge la o complexitate polinomială. Stiim ca k < n 
asadar vom spune că k este in O(n). Inlocuind, ajungem la o complexitate polinomiala
indicată de termenul O(n^2) asadar, T polinomială.


    Compararea timpului de executie dintre cei doi algoritmi

Timpi pentru categoria 1:
    BACKTRACKING TOTAL TIME: 0.066s
    REDUCTION TOTAL TIME: 3.810s
    REDUCTION / BACKTRACKING: 57.727

Timpi pentru categoria 2:
    BACKTRACKING TOTAL TIME: 0.099s
    REDUCTION TOTAL TIME: 25.937s
    REDUCTION / BACKTRACKING: 261.989

Timpi pentru categoria 3:
    BACKTRACKING TOTAL TIME: 0.175s
    REDUCTION TOTAL TIME: 2.845s
    REDUCTION / BACKTRACKING: 16.257

Cele trei categorii de teste sunt impartite pe anumite criterii:
    Categoria 1 - se cauta clici de marimi similare cu numarul de noduri. Graful are
                  numar relativ mic de noduri, si un numar mare de muchii.
    Categoria 2 - se cauta clici de marimi mici in grafuri cu un numar foarte mare
                  de noduri.
    Categoria 3 - se cauta clici de marimi similare cu numarul de noduri. Comparativ
                  cu categoria 1, graful are un numar mai mic de muchii.

Observăm faptul ca, in cazul categoriei 2, algoritmul de reducere este mult mai
lent, având in vedere numarul foarte mare de noduri. Algoritmul trebuie sa parcurgă
toate nodurile, asadar, intr-o situatie in care graful are un numar mare de noduri,
putem spune că metoda de backtracking este mai eficientă, mai ales cand cautam o
clică de mărimi mici. Aceasta se opreste la idendificarea primei k-clique, nefiind
nevoită să parcurgă toate nodurile grafului, decât in cazul in care clica nu există.

In categoriile 1 si 3, se cauta clici de marimi similare cu numarul de noduri. 
Algoritmul de backtracking functioneaza la un timp similar pe ambele categorii:
    Categoria 1 - 4 teste - 0.06s
    Categoria 3 - 11 teste - 0.175s
Timpul de executie creste liniar cu numarul de teste.
Totusi, in cazul algoritmului de reducere, observăm faptul că, cu toate că avem
un numar de teste de trei ori mai mare, timpul de executare este mai mic:
    Categoria 1 - 4 teste - 3.8s
    Categoria 3 - 11 teste - 2.8s
Asadar, putem sa determinam ca aceasta scadere in timp are legatura cu numarul
de muchii, marimea clicilor cautate si numarul de noduri fiind similare intre
cele doua categorii. Putem deduce ca algoritmul de reducere este mai eficient
intr-un graf cu un numar mai mic de muchii.

Am observat faptul ca algoritmul de backtracking este mai eficient in cazul 
in care avem un numar mare de noduri. Mai ales in cazul in care marimea clicii
cautate este foarte mica, comparativ cu numarul de noduri.

Pe de alta parte, algoritmul de reducere are o eficienta crescuta pe grafuri 
de marimi mici, cu un numar redus de muchii.
