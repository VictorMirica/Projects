TaskZero
    Dupa ce am initializat fiecare element din matrice cu '.', afisez matricea

TaskOne
    Intializez matricea, citesc n - nr de randuri. Pentru fiecare rand, stiu ca se citesc x,y,d,cuvant in aceasta ordine, cu spatii intre ele.
    Initializez doua variabile cu 0, par1 si par2, care functioneaza precum 2 indexi. de fiecare tada cand par2 (indexul din dreapta), ajunge la un spatiu, new line
    sau '\0', atribui valoarea dintre par1 si par2 lui x,y,d sau cum, depinzand al catelea ' ' este. (prima oara voi atribui x, dupa y etc).
    Dupa ce am toate valorile, atribui spatiilor respective din matrice literele cuvantului si trec la urmatorul rand.

functia calcScor
    Aceasta functie calculeaza scorurile, cu tot cu bonusuri.
    initializez whichP cu zero, variabila care se incrementeaza de fiecare data cand atribui un punctaj unui jucator, pentru a 'sari' intre jucatori.
    pentru fiecare linie citita, initializez variabile x,y,z si sirul de caractere cuv, precum am facut si la TaskOne.
    Testez daca cuvantul se poate dubla sau tripla. Elimin cuvantul scris pe tabela din vectorul words(eliminarea doar inlocuieste prima litera a cuvantului
    din vectorul words cu '-', in acest fel, acesta nu va mai fi ales niciodata). Citesc tabela bonus, pe orizontala sau verticala, in urma cuvantului. Daca acesta
    se poate dubla/tripla, testez daca acesta se va dubla/tripla, si daca da, de cate ori. Adaug punctele de baza, adaugand scor[cuv[j] - 'A'], pentru fiecare litera.
    Daca se va tripla/dubla, inmultesc scorul si il adaug player-ului respectiv, dupa care schimb urmatorul player care va primi puncte.

TaskTwo
    Dupa ce initializez matricea si citesc n, deoarece nu am nevoie de bonus, setez xx si yy (sirurile de caractere ce reprezinta conditia de bonus) la '--'.
    Apelez functia calcScor si printez scorurile.

TaskThree
    Acesta este taskTwo, doar ca incluzand bonusuri, asa ca citesc xx si yy, dupa care apelez calcScor si pritnez scorurile.

functia findWord
    Aceasta functie gaseste cuvantul OPTIM (nu primul), care va fi introdus pe tabela de joc.
    Iau fiecare cuvant din vectorul words si testez daca se potriveste ORIUNDE pe tabela de joc. In continuare, testez daca se poate dubla sau tripla dupa care 
    testez daca incape pe verticala sau pe orizontala. Dupa aceasta, in cazul in care incape pe una sau doua directii, testez daca se va 'intalni' cu alt cuvant
    acest lucru il testez facandu-ma sigur ca cuvantul va intampina pe toata lungimea lui, pe directia aleasa, doar caracterul '.'.
    Dupa ce calculam daca cuvantul se va tripla/dubla si de cate ori, ii vom calcula punctajul. Daca punctajul acestui cuvant ne va ajuta sa castigam sau sa egalam
    SI este mai mare decat cuvantul cu punctajul cel mai mare gasit pana acum (highscore), atunci vom seta un nou highscore, si ii vom tine minte pozitia pe axa x,y,
    directia si cuvantul in sine. Daca acesta are punctajul EGAL cu highscore-ul, testam daca linia curenta este mai mica decat linia cuvantul castigator, daca aceasta
    este mai mica, avem un nou cuvant castigator, daca acestea sunt egale, fac acelasi test si pentru coloane.
    Fac aceste teste si pe orizontala, si pe verticala (in cazul in care cuvnatul merge pus pe ambele directii).
    Dupa ce gasesc cuvantul castigator, in cazul in care rulez fucntia de mai multe ori, elimin cuvantul din vectorul words.

TaskFour
    Dupa ce citesc n, stringurile bonus si apelez functia calcScor (pentru a plasa cuvintele pe tabela de joc), testez, fara sa tin seama de punctaj, care este 
    PRIMUL cuvant din vectorul words care poate sa intre pe tabela de joc, il introduc si printez tabela

TaskFive
    Dupa ce citesc n, stringurile bonus si apelez functia calcScor, apelez functia findWord. daca nu gasesc niciun cuvant (highscore = 0), vom afisa Fail!.
    Daca am gasit un cuvant castigator, il plasez pe tabela de joc si printez tabela.

TaskSix 
    Dupa ce citesc n is stringurile bonus, fac un for loop pentru fiecare linie citita. In loop voi apela calcScor pentru a calcula scorul playerului 1 si pentru
    a-i plasa fiecare cuvant, unul cate unul, in tabela de joc. Dupa plasarea unui cuvant, apelez functia findWord la tabela de joc curenta. In cazul in care, dupa 
    apelare highscor este tot 0 (nu am gasit un cuvant care sa intreaca punctajul lui Player 1, dar tot trebuie sa aleg un cuvant), voi apela din nou findWord, de 
    data asta, considerand punctajul lui p1 (punctajul pe care trebuie sa il intrec cu cuvantul respectiv) 0, in acest fel, pe tabela de joc voi nu voi printa cuvantul
    care va bate punctajul lui p1, acesta fiind neexistent, doar ca voi introduce a doua cea mai buna optiune.
    Dupa citirea tuturor liniilor, afisez tabela de joc urmata de player-ul care a castigat.

Main
    In functia main, citesc de la tastatura un numar de la 0 la 6, si apelez functia taskului respectiv.
