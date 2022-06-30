
Mirica Victor - 324CB - Tema 2


Pentru makefile, cat si pentru restul temei (fisierele sursa), am inceput de la
skeletul folosit in lab 8.


In makefile, am adaugat is campul ID, folosit pentru a rula subscriber.


In fisierul helpers.h am definit structuri ajutatoare:
    topic - structura unui topic, ce contine topicul in sine, si un indicator (1/0)
            care indica daca aceasta trebuie pastrata pentru store and forward (sf).
    msg - structura unui mesaj trimis de UDP, asa cum se observa in enunt.
    toSend - structura unui mesaj ce trebuie trimis unui TCP, acesta, pe langa informatiile
             primite de la UDP (struct msg), mai are o adresa ip, si un port.   
    flux - fluxul de date trimise de un client TCP (subscribe, unsubscribe, exit).
           Aceasta contine un int tip care va fi 0, 1 sau 2, in functie de comanda 
           data de la tastatura de client si o structura de tip topic, la care acesta
           se va abona/dezabona. (In cazul exit, aceasta este redundanta).
    clientTcp - Reprezinta un client TCP, asa cum va fi retinut de catre server.
                Aceasta contine un identificator online (1/0), un id si socket-ul pe care
                se afla.
                De asemenea, aceasta contine si doi vectori, cu lungimile lor:
                topicList, o lista de topics la care clientul este abonat.
                sfList, o lista de measaje ce trebuie trimise clientul cand acesta
                se va reconecta. (sf)
    Tcelula si Tlist - Voi folosi un linked list pentru a stoca informatii despre subscriberi,
    precum mesajele stored si topics la care acestia sunt abonati
    


SUBSCRIBER:


In fisierul subscriber.c am facut functionalitatea unui subscriber de a trimite comenzi
de la tastatura si de a primi mesajele la topicele la care este abonat, de la clientii UDP.
Pentru inceput, ca in laborator, vom crea cele doua multimi de citire si le vom goli.

O sa deschid socket-ul TCP (SOCK_STREAM) si preluez portul din argumentele date. 
Setez familia, portul si adresa ip pentru adresa socket-ului. 

Deschid o conexiune cu serverul si trimit o datagrama cu id-ul meu. 
Urmeaza sa dezactivez algoritmul lui nagle pentru socket-ul nostru.

In multimea de citire vom seta doi file descriptori: socket-ul pe care vom primi date si 
input-ul de la tastatura. 

Atribui multimii de citire temporare read_fds si resetez buffer-ul pe care primesc datele.
Urmeaza sa verific daca am unul dintre cele doua cazuri: Citire de la tastatura sau date 
din socket.

In cazul citirii de la tasatura am alte 3 cazuri.
    exit: In acest caz, voi schimba vloarea de tip a datagramei pe care urmeaza sa o 
trimit in 0, restul structurii este redundanta. Trimit datele pe socket si inchid 
socket-ul.
    subscibe: In acest caz, tipul datagramei va fi 1. De asemenea, trebuie sa preiau
din buffer, folosind functia sscanf topicul si daca are doresc capabilitate de sf. 
Printez la stdout mesajul aferent.
De tinut cont ca memorie pentru datagrama a fost deja alocata.
Odata preluate, trimit pe socket folosind send().
    unsubscribe: Functionalitate foarte similara cu subscribe, doar ca aceasta 
datagrama va avea tipul 2.

Aceasta conventie de tip, (0, 1 sau 2), va fi verificata la primirea datagramei 
de catre server si prelucrata corespunzator.

In cazul primirii unui mesaj de la server, stim ca trebuie sa primim o structura de 
tip toSend. Folosim functia recv(). Verificam daca lungimea mesajului este una 
corespunzatoare, stiind ca recv() intoarce de asemenea si lungimea mesajului.
Structura primita de noi deja contine port-ul, continutul si ip-ul (in valoare
de uint32_t, vol folosi inet_ntoa() pentru a-l pune in formal human readable). 
Tot ce trebuie de facut este sa transformam tipul de date din uint8_t-ul primit
in string-ul corespunzator (asa cum este descris in enunt). Imi voi aloca un char* in
care voi retine string-ul care va trebui printat in locul tipului de date.


SERVER:

Folosesc doua functii pentru prelucrarea listelor. Una de insert, care introduce un element
in lista, si una de remove, care elimina un element din lista. Aceste functii, precum si 
stuct TList, au fost preluate din laboratoarele de Structuri de Date (anul 1).

Pentru server vom avea vectorul alocat clients, in care vom tine toti clientii TCP.
De asemena vom avea o variabila sockLen, ce va reprezenta marimea unei structuri sockaddr.
Ca si in laborator, aceasta variabila este folosita doar in functia accept(), deoarece un 
parametru al acesteia trebuie sa fie un pointer catre o variabila ce contine 
dimensiunea structurii. (din manual unix: "The addrlen argument is a value-result argument: the 
caller must initialize it to contain the size (in bytes) of the structure pointed to by addr").

In continuare, similar cu fisierul subscriber, dezactivam buffering-ul la afisare cu setvbuf(),
dupa care creez cele doua multimi de descriptori si le golesc. Pentru server va trebui sa 
deschid un socket tcp, ca la client, dar si un socket udp (SOCK_DGRAM). Adresele socket-urilor udp
si tcp vor fi aceleasi. Le facem bind si dezactivam algoritmul Nagle pentru socket-ul TCP.
Putem specifica de asemenea reutilizarea unui port folosit cu setsockopt().

Ascultam dupa conexiunile clientilor pe socket-ul tcp si adaugam cele 2 socket-uri si stdin la 
multimea de descriptori. Decidem care este descriptorul maxim dintre cele doua.

In loop, incepem similar ca in cazul subscriber, ne initializam multimea de descriptori
temporara, apelam functia select() si resetam buiffer-ul.

In continuare, ascultam fiecare intrare, pe fiecare socket cu un for de la 0 la fdmax (descris mai sus).
In cazul in care gasim un file descriptor set in multimea de file descriptori, vom avea una din urmatoarele patru
variante:

    Am primit o comanda de la tastatura. Cum singura comanda legala este "exit", o verificam. Inchdem toate
socket-urile clientilor conectati, inchidem socket-urile udp si tcp si oprim serverul din functiune. :(
Pentru inchiderea socket-ului unui client, trecem prin toti acestia, (numarul de clienti maxim este dat
de fdmax), verificam daca au file descriptorul set (clientul exista), inchidem socketul
si il scoatem din multimea de descriptori.

    Cazul numarul doi implica o cerere de conexiune pe socket-ul TCP. O vom accepta pe un new socket apeland accept().
Deoarece in subscriber.c voi trimite aici, prin intermediul buffer-ului id-ul (10 octeti),
acum este momentul sa il primesc si sa il pastrez in variabila buffer (recv()). Odata ce avem ID-ul,
trebuie sa cautam clientul. Iterez prin toti clientii (for pana la fdmax), si compar ID-urile.
Aici urmeaza alte trei cazuri: Nu am gasit clientul, am gasit clientul si am gasit clientul dar 
acesta este deja conectat. In cazul unui client nou, intoroduc noul socketfd in multimea de descriptori
si updatez daca e nevoie fdmax. Folosind o functie auxiliara setClient(), ii setez unei structuri de tip 
client id-ul, socket-ul si il fac online. 
Printez mesajul aferent.
In cazul in care eceasta este gasit si nu este online, inseamna ca s-a reconectat un  client mai vechi,
ii updatam socket-ul pe care s-a reconectat si afisam mesajul aferent la stdout. Aici vine si vorba 
despre procesul de sf. Toate mesajele din store trebuie trimise. Parcurg lista de sf si trimit 
toate mesajele din ea, apeland functia send pe socket-ul clientului gasit. La final, deoarece lista
este acum goala si clientul reconectat, setez capul listei si variabila online cu NULL respectiv 1.
Ultimul caz reprezinta incercarea cuiva de a se conecta cu un ID care deja exista, Doar trebuie
sa afisez mesajul aferent si sa inchid conexiunea catre clientul respectiv.

    Un al treilea caz este receptionarea unei conexiuni pe socket-ul pentru clienti UDP. In acest pas
va trebui sa primesc o datagrama de la un client UDP, sa o parsez/prelucrez conform cerintei, si sa 
o trimit mai departe toti subscriberilor. Pentru a primi informatiile, folosesc recvfrom in loc de recv,
deoarece trebuie specificata si destinatia. Imi creez o structura toSend. Deja pot sa initializez campurile
port si ip, acestea fiind primite de la recvfrom, in adresa socket. Buffer-ul va fi o structura de tip msg,
cum spune si in enunt, cu un topic, un tip de date uint8_t si un continut.
Topicul poate fi copiat in mesajul care va fi trimis "as is". In cazul continutului, acesta trebuie formatat
in functie de tipul de date.
Verificam cele patru tipuri de date.
    In cazul 0, Avem un Int, cu un octet de semn la inceput. Preiau din mesaj octatul de semn si continutul.
Este specificat ca continutul in format uint32_t este formatat conform network byte order, asadar vom apela 
ntohl pe el (host byte order long). Verificam octetul de semn pentru a decide semnul continutului, dupa care
il transformam in string cu sprintf. Updatam tipul de date si in datagrama ce va fi trimisa (acelasi ca si in cea primita).
    In cazul tipului de date 1, short real, vom extrage short-ul (uint16_t) din continut. Acestui numar 
trebuie sa ii aplicam modul dupa ce il transformam in netowrk byte order (de data asta short, deci ntohs).
Urmeaza sa il impartim la 100 si sa trimitem mai departe, cu 2 zecimale.
    In cazul tip date 2, avem un float. Aici, precum si in cazul 0, preluam octetul de semn si continutul.
La final, mai avem inca un octet unsigned (uint8_t) ce reprezinta putearea lui 10 la care trebuie sa impartim
continutul. Dupa impartirea numarului la 10^putere si deciderea semnului, acesta va fi trimis.
    In cazul tip date 3, avem un string, care trebuie doar sa fie copiat in continutului mesajului care urmeaza sa fie trimis.
    Am ajuns la structura finala, aceasta este gata sa fie trimisa. Iterez prin toti clientii.
La fiecare client, iterez prin topicile la care acesta este abonat (lista topicList).
Daca gasim topica pe care am primit-o de la udp, trebuie sa facem o ultima verificare.
In cazul in care clientul este online, ii trimitem direct, pe socket-ul sau, mesajul.
In cazul in care acesta este offline, verificam daca are functionalitatea de store and forward la acest topic.
(sf == 1). In cazul in care aceasta este pornita, adaugam mesajul compus in lista de mesaje.
    Ultimul caz este receptionarea unui flux de date de la un client TCP, adica daca acesta vrea sa se deconecteze,
sau sa se aboneze/dezaboneze de la un topic.
Dupa ce primim intr-un buffer mesajul, il transpunem intr-o structura de tip flux. Acesta a fost trimisa sub aceasta forma
tot de noi, in fisierul subscriber.c. Incepem prin a identifica clientul care a trimis mesajul. Iterez prin toti clientii,
si caut clientul care se afla pe socket-ul pe care am primit datastream-ul.
Odata aflat, urmeaza sa verific ce tip de comanda a dat, am specificat ca trebuie sa urmez valoarea campului type.
    In cazul in care acesta este 0, subscriberul vrea sa se deconecteze (A scris exit). Dupa ce afisez mesajul aferent,
Ii schimb campul online in 0 si inchid conexiunea pe care acesta se afla.
    Daca tipul este 1, acesta vrea sa se aboneze la un topic. Trebuie verificat mai intai daca acesta a facut o greseala
si a vrut sa se aboneze la un topic la care este deja abonat. Iteram prin lista sa de abonari, verificand daca topicul
primit in datagrama se gaseste acolo. In cazul contrar, adaugam o noua intrare in lista de topics.
    Ultimul caz, tipul 2, este primit cand user-ul vrea sa se dezaboneze la un topic. Similar cu cazul de abonare. Prima
oara trebuie sa fim sigur ca acesta chiar era abonat in the first place la topic-ul precizat in mesaj.
Iteram lista de abonamente si verificam.
Daca acesta este gasit, ii putem pastra pozitia in lista intr-o variabila. In continuare, elemin intrarea din lista
apeland functia removeList.