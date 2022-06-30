Mirica Victor 324CB

        Clasa Book
    Metoda readBooks()
  Metoda care intoarce un array care contine toate cartile, initializate, din fișierul books.in.
Pentru citirea fisierelor ne vom folosi de un BufferedReader care va citi linie cu linie, preluând
linia in Stringul "line". Atata timp cat linia nu este null, o vom impartii intr-un array de stringuri
numit attributes folosindu-ne de metoda split() cu parametrul "###", doarece cunoastem faptul ca diferitele
campuri din fisier sunt despartite prin acest delimitator.
  Initializam campurile de tip String ale obiectului prin atribuirea elementului respectiv din array-ul de 
atribute. In cazul campurilor de tip int, va trebui mai inai sa parsăm stringul.
  In cazul campului createdOn, care este de tipul Calendar, vom folosi un obiect de tipul SimpleDateFormat
pe care il vom formata cu pattern-ul dorit: "dd.MM.yyyy HH:mm:ss". Vom atribui campului createdOn o instanta
ca lui Calendar, caruia ii vom seta timpul in formatul dat de variabila sdf.
  Pentru a initializa campul authors vom avea nevoie de un array cu toti autorii. Ne folosim de metoda readAuthors
din clasa Authors pentru a-i citi din fisier, iar apoi metoda getBooksAuthors, care primeste o carte (in cazul
acesta, this), si un array cu autorii si care initializeaza campul authors al cartii primite ca parametru.
  La final, adaugam cartea in array, incrementam index-ul, si citim urmatoarea linie, pana la EOF.
  
    Metoda getBooksAuthors
  Metoda care initializeaza campul authors dintr-o carte, data ca parametru. Celalalt parametru reprezinta
un array cu toti autorii valabili. Metoda readAuthors nu este apelata in interiorul metodei deoarece aceasta
ar insemna ca trebuie sa citim fisierul authors.in pentru fiecare carte in parte.
  Vom citi fieiserul books-authors.in, preluand informatia din el (similar cu citirea fisierului books.in).
Prima coloana din fisier (attributes[0]), reprezinta id-ul cartii, daca acesta este gasit, vom itera
vectorul de autori comparand id-ul autorilor cu cea de-a doua coloana a fisierului. In cazul in care acestea
sunt egale, vom adauga autorul in array. In final, pentru a concretiza lungimea array-ului, vom apela functia
Array.copyOf, cu parametrii books.authors si i, acest lucru ne va seta noua lungime a array-ului.

    Metoda Publish()
  Aceasta metoda va intoarce un String de forma unui fisier XML. Primul si Ultimul rand din String vor vi
neindentate, restul campurilor vor avea la inceput un caracter de tipul '\t'. In cazul campului createrdOn
ne vom folosi inca odata de un obiect SimpleDateFormat, pentru a afisa data in formatul dorit. In cazul arrayului
de autori, folosim Array.toString.


        Clasa Language
    Metoda readLanguages
  Metoda care citeste fisierul languages.in si intoarce un array cu obiecte de tip Language. Functioneaza identic
cu restul initializarilor/citirilor de pana acum (ex: readBooks())


        Clasa Author
    Metoda readAuthor
  Metoda care citeste fisierul authors.in si intoarce un array cu obiecte de tip Author. Functioneaza identic
cu restul initializarilor/citirilor de pana acum.


        Clasa Country
    Metoda readCountries
  Metoda care citeste fisierul countries.in si intoarce un array cu obiecte de tip Country. Functioneaza identic
cu restul initializarilor/citirilor de pana acum.


        Clasa EditorialGroup
    Metoda readEditorialGroups
  Metoda care citeste grupurile editoriale din fisierul editorial-groups.in si reintoarce un array de obiecte
EditoarialGroup, initializate. Citirea din fisier si initializarea campurilor este identica cu celelalte metode
de citire (readBooks()). In plus, deoarece aceasta clasa are un camp de tip Book[], ne vom folosi de o metoda
ajutatoare, getEditorialGroupBooks(), care are doi parametrii, grupul editorial si un array care contine 
toate cartile din fisierul books.in. Aceasta metoda are o implementare si o functionalitate similara cu metoda
clasei Book, getBooksAuthors, care initializeaza campul de autori al unei carti.

    Metoda getEditoralGroupBooks
  Precizat si mai sus, aceasta metoda functioneaza identic cu metoda getBooksAuthors, a carei implementari este
explicata in detaliu (linia 20).

    Metoda Publish
  Aceasta metoda intoarce un String de forma unui fisier XML. Deoarece in acest String trebuie listate toate
cartile din campul books al clasei, ne vom folosi de un for-loop care cicleaza obiectele de tip Book ale campului,
concatenând la string campurile acestora.


        Clasa PublishingBrand
    Metoda readPublishingBrands
  Aceasta metoda de citire/initializare, functioneaza identic cu alte metode de citire (readEditorialGroups()).

    Metoda getPublishingBrandBooks
  Metoda folosita in initializarea campului de carti al clasei. Aceasta functioneaza similar cu celelalte metode
de initializare a acestui camp, regasite in celelalte clase ce implementeaza IPublishingArtifact (getEditoralGroupBooks())

    Metoda Publish
  Metoda care intoarce Stringul de tip XML, functioneaza identic cu Publish() din clasa EditorialGroup.


        Clasa PublishingRetailer
    Metoda readPublishingReatilers
  Aceasta metoda citeste si initializeaza toate obiectele de tip PublishingRetailer, in fisierul publishing-retailers.in.
Deoarece aceasta clasa are un camp de tip Country[] si un camp de tip IPublishingArtifac[] vom incepe prin a citi
aceste obiecte, apeland metodele de initializare respective, si pastrandu-le in 4 array-uri.
  Pentru citirea din fisier, vom actiona similar cu alte citiri, initializand campurile ID si name.
  De asemenea, vom folosi metodele getPublishingRetailerCountries si getPublishingRetailerArtifacts, care fac legatura
intre un retailer si Tari, respectiv publishingArtifacts, si initializeaza campurile retailerului primit ca parametru.
  
    Metoda getPublishingRetailerCountries
  Similara cu alte metode de cross-reference, aceasta metoda va initializa campul countries al unui PublishingRetailer,
citind fisierul publishing-retailers-countries.in si comparand ID-urile din acesta.

    Metoda getPublishingRetailerArtifacts
  Aceasta metoda va initializa campul publishingArtifacts al unui retailer.
  Avem trei clase ce implementeaza interfata IPublishingArtifact. De asemenea, avem trei fisiere de intrare care
ne vor face legatura intre ID-ul retailer-ului si artefactul respectiv. Vom citi si vom adauga obiecte in array
in aceasta ordine: publishing-retailers-books.in, publishing-retailers-editorial-groups.in si ublishing-retailers-publishing-brands.in.
  Citirile din fiecare respectiv se vor face similar cu celelalte metode care citesc fisiere pentru cross-referecne
intre doua obiecte.

    Metoda toString
  Metoda folosita in testare. Aceasta este mentionata in cadrul clasei PublishingRetailer deoarece are cateva specificatii.
  Pentru a parcurge si a afisa array-ul publishingArtifacts, nu putem folosi un Arrays.toString(), asadar iteram campul
si testam, pe rand, daca obiectul este instanta uneia din cele trei clase care implementeaza aceasta interfata. 


        Interfata IPublishingArtifact
  Aceasta interfata, implementata de Book, EditorialGroup si PublishingBrand prezinta doar metoda Publish().


        Clasa Administration
  In aceasta clasa se vor implementa si testa metode ce se folosesc de Clasele scrise pana acum. In implementare
acestor metode vom avea nevoie sa citim din fisier array-ul cu obiecte de tip PublishingRetailer si Language.
Inaintea implementarii metodelor, vom initializa aceste array-uri cu mateodele de read, specifice celor doua clase.

    Metoda getBooksForPublishingRetailerID
  Aceasta metoda primeste un retailerID si intoarce un array cu cartile acestuia. Pentru inceput, trebuie sa identificam
retailer-ul. Pentru asta vom itera prin arrayul de retaileri, si vom retine retailer-ul gasit, in cazul in care acesta nu 
este gasit, vom arunca o exceptie.
  In continuare vom itera arrayul de publishingArtifacts. Din implementarea acestuia, cunoastem ca avem trei Obiecte diferite.
Verificam daca elementul este o instanta de Book, caz in care putem pur si simplu sa adaugam cartea in array si sa crestem indexul.
in cazul obiectelor EditorialGroup sau  PublishingBrand, vom adauga, carte cu carte, folosind 2 iteratori, caritle Obiectului respectiv
in arrary-ul books, pe care il vom intoarce in final.

    Metoda getLanguagesForPublishingRetailerID
  Metoda care primeste un retailerID si intoarce un array de Language, limbile in care sunt scrise cartile acestuia.
  Apelam functia explicata mai sus pentru a face rost de un Array cu cartile acestui retailer. Singurul mod in care
putem sa facem rost de obiecte de tipul Language este prin entitatea Book. Iteram vectorul de carti, iar la fiecare
carte vom face o verificare, in cazul in care am adaugat deja aceasta limba in array. Comparam campurile ID ale celor doua obiecte.
Odata gasita, verificam daca limba se afla deja in vector cu un simplu for-loop si un flag (duplicate).
  In cazul in care aceasta este o limbă nouă, o adaugam vectorului.

    Metoda getCountriesForBookID
  Aceasta metoda intoarce tarile in care este publicata o carte, primeste ca parametru un bookID.
  Deoarece putem accesa entitatea Country doar prin intermediul unui obiect de tip PublishingRetailer, si avand in
vedere faptul ca o carte poate face parte din mai multi publishing retaileri (asadar fiind publicata in mai multe tari),
va trebui sa iteram tot array-ul cu obiecte de tipul PublishingRetailer. In cazul fiecarui retailer, vom avea nevoie de cartile
acestuia. Apelam functia getBooksForPublishingRetailerID pentru fiecare ratiler in parte.
  In continuare, vom itera array-ul de carti, cautand cartea cu ID-ul primit ca parametru. Dupa ce o vom gasi, vom adauga
tarile acelui retailer in array-ul countries, pe care metoda il va intoarce. In cazul duplicatelor, procedam similar cu
metoda de mai sus, folosindu-ne de un flag si un for loop.
  Odata ce am introdus tarile unui retailer in array, putem sa trecem la urmatorul => break.

    Metoda getCommonBooksForRetailerIDs
  Aceasta metoda primeste doua retailerIDs si intoarce un array de carti, valabile la ambii retaileri.
  Preluam array-urile de carti a celor doi retaileri. Iteram cele doua array-uri, in cazul in care gasim un obiect
Book cu acelasi ID, il vom adauga in al trei-lea array (books), pe care il vom intoarce la final.

    Metoda getAllBooksForRetailerIDs
  Metoda intoarce reuniunea de carti a doi retaileri. Similar cu metoda de mai sus incepem prin a prelua array-urile 
de Book ale celor doi retaileri, folosind metoda getBooksForPublishingRetailerID(). Gasim cartile comune, nu apelam 
metoda getCommonBooksForRetailerIDs deoarece asta ar insemna sa apleam dinnou metodele getBooksForPublishingRetailerID
pentru cei doi. Odata ce avem array-ul commonBooks, cu intersectia celor doi retailer, putem sa formam reuniunea direct
in array-ul de carti al unuia dintre retaileri, am ales books1.
  In legatura cu lungimea array-ului, o vom retine intr-o variabila i, dupa care ii vom mari lungimea maxima pentru a putea
introduce mai multe carti in acesta. Folosim Arrays.copyOf pentru un numar maxim de 1000 de carti. La finalul metodei
vom refolosi Arrays.copyOf cu parametrul i, care va reprezenta noua lungime.
  Iteram cel de-al doilea array de carti si ne vom folosi de un flag (common) pentru a vedea daca trebuie sau nu sa introducem
cartea. Pentru fiecare carte, vom face o verificare cu continutul commonBooks, in cazul in care aceasta nu se afla in arrayul 
precizat, va fi adaugata in books1.


    Metodele de test
 In continuare se afla 5 metode care testeaza cele 5 metode explicate mai sus. Fiecare metoda test va avea cate 5
teste, pentru un total de 25 de teste
 (testFunct1 -> testele 1-5)
 (testFunct2 -> testele 6-10)  
  etc.

  Aceste metode vor fi apelate pe rand, in main.

  La finalul clasei se afla si o exceptie, care este apelata in cazul in care apelam un test cu un ID invalid.
Mesajul oferit este "Invalid ID".

    

