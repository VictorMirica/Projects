/*MIRICA Victor - 315CB*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "TStiva.h"
//Structuri
typedef struct {
    int id;
	char* nume;
	float rating;
    int nrSez;
    int top;
    AQ sezoane;
} TSerial;

typedef struct {
    int nrEp;
    AQ episoade;
} TSezon;

typedef struct {
    int nrMinute;
} TEpisod;
//Functii de eliberare
int freeEpisod(void* a){
    TEpisod* ep = (TEpisod*)a;
    free(ep);
    return 1;
}

int freeSezon(void* a){
    TSezon* sezon = (TSezon*)a;
    DistrugeL(&IC(sezon->episoade), freeEpisod);
    free(sezon->episoade);
    free(sezon);
    return 1;
}

int freeSerial(void* a){
    TSerial* serial = (TSerial*)a;
    DistrugeL(&IC(serial->sezoane), freeSezon);
    free(serial->nume);
    free(serial->sezoane);
    free(serial);
    return 1;
}
//Functiile de comparatie si de cautare a numelui unui serial
int cmpSeriale(void * e1, void * e2)
{
	TSerial * s1 = (TSerial *) e1;
	TSerial * s2 = (TSerial *) e2;
	if(s1->rating > s2->rating)
		return 1;

	if ((s1->rating == s2->rating) && (strcmp(s1->nume,s2->nume) < 0)) 
		return 1;
        
	return 0;
}

int findName(void * e1, void * e2)
{
	TSerial* s1 = (TSerial*) e1;
	char* n2 = (char*) e2;
    char* n1 = s1->nume;
	if(!strcmp(n1,n2))
		return 1;
	return 0;
}
//Functie pentru initializarea unui serial
TSerial* addSerial(FILE* in, int top){
    TSerial* serial = malloc(sizeof(TSerial));  //initializarea serialului
    serial->nume = malloc(50);
    if(top){
        serial->id = 4;
        fscanf(in, "%d %s %f %d ", &serial->top, serial->nume, &serial->rating, &serial->nrSez);  
    }else{
        serial->top = 0;
        fscanf(in, "%d %s %f %d ", &serial->id, serial->nume, &serial->rating, &serial->nrSez);  
    }
    serial->sezoane = InitQ(sizeof(TSezon));
    for(int i = 0; i < serial->nrSez; i++){     
        TSezon* sezon = malloc(sizeof(TSezon)); //initializarea sezoanelor
        fscanf(in, "%d ", &sezon->nrEp);
        sezon->episoade = InitQ(sizeof(int));               
        for(int j = 0; j < sezon->nrEp; j++){
            TEpisod* episod = malloc(sizeof(TEpisod));  //initializare episod
            fscanf(in, "%d ", &episod->nrMinute);    
            IntrQ(sezon->episoade, episod);         //adaugare episod in coada
            free(episod);
        }
        IntrQ(serial->sezoane, sezon);         //introducere sezon in coada 
        free(sezon);
    }
    return serial;
}
//Functie pentru initializarea unui sezon, folosita la adaugarea unui sezon nou
TSezon* addSezon(FILE* in, int nrEp){
    TSezon* sezon = malloc(sizeof(TSezon)); //initializare sezon
    sezon->episoade = InitQ(sizeof(int));               
    sezon->nrEp = nrEp;
    for(int i = 0; i < nrEp; i++){
        TEpisod* episod = malloc(sizeof(TEpisod));  //initializare episod
        fscanf(in, "%d ", &episod->nrMinute);    
        IntrQ(sezon->episoade, episod);         //adaugare episod in coada
        free(episod);
    }
    return sezon;
}
//Functie folosita ca argument la eliminarea unui serial din lista topTen. Functia decrementeaza campul top.
int decrementTop(void* a){
    TSerial* serial = (TSerial*) a;
    (serial->top)--;
    return 1;
}

int main( int argc, char *argv[] ){
    //Testare pentru a rula functia corect din linia de comanda + deschidere fisiere
    if(argc != 3){
        printf("Programul a fost rulat incorect din linia de comanda\n");
        return 0;
    }
    FILE *in, *out;
    in = fopen(argv[1], "rt");
    out = fopen(argv[2], "wt");
    if (in == NULL)
		return 0;
    if (out == NULL)
		return 0;

    //Initializare liste, stive si cozi.
    TLista trending = NULL;
    TLista documentare = NULL;
    TLista tutoriale = NULL;
    TLista topTen = NULL;
    void* watchLater = InitQ(sizeof(TSerial));
    if(!watchLater)
        return 0;
    void* currentlyWatching = InitS(sizeof(TSerial));
    if(!currentlyWatching)
        return 0;
    void* history = InitS(sizeof(TSerial));
    if(!history)
        return 0;
    int posLater = 0; //variabila care va retine cate elemente sunt in coada later

    //Citirea fisierului de intrare
    while (!feof(in)){      
        char comanda[50];
        fscanf(in, "%s ", comanda);
        if(strcmp(comanda,"add") == 0){  //adauga un serial intr-o lista de categorie
            TSerial* serial = addSerial(in, 0);
            int pos;
            if(serial->id == 1){                        //introducere serial in lista
               pos = InsL(&trending, serial, cmpSeriale);
            }
            if(serial->id == 2){
                pos = InsL(&documentare, serial, cmpSeriale);
            }
            if(serial->id == 3){
                pos = InsL(&tutoriale, serial, cmpSeriale);
            }
            fprintf(out, "Serialul %s a fost adaugat la pozitia %d.\n", serial->nume, pos);
        }
        if(strcmp(comanda,"add_sez") == 0){ //adauga un sezon nou unui serial
            char nume[50];
            int nrEp;
            fscanf(in, "%s %d ", nume, &nrEp);
            TSezon* sezon = addSezon(in, nrEp); //creeare sezon
            TSerial* serial = NULL;
            serial = cautaSerialL(trending,nume,findName);  //cautare serial in liste/stive/cozi
            if(!serial)
                serial = cautaSerialL(documentare,nume,findName);
            if(!serial)
                serial = cautaSerialL(tutoriale,nume,findName);
            if(!serial)
                serial = cautaSerialL(topTen,nume,findName);
            if(!serial)
                serial = cautaSerialL(IC(watchLater), nume, findName);
            if(!serial)
                serial = cautaSerialL(VF(currentlyWatching), nume, findName);
            IntrQ(serial->sezoane, sezon);              //adaugarea efectiva a sezonului nou, in coada de sezoane
            free(sezon);  
            fprintf(out,"Serialul %s are un sezon nou.\n", nume);
        }
        if(strcmp(comanda,"add_top") == 0){         //adauga un serial in lista topTen
            TSerial* serial = addSerial(in, 1);     //initializare serial
            serial = InsTop(&topTen, serial, serial->top);     //inserare serial
            if(serial != NULL){
                freeSerial(serial);
            }
            fprintf(out,"Categoria top10: [");
            TLista p = topTen;
            for(; p->urm != NULL; p=p->urm){
                fprintf(out, "(%s, %.1f), ", ((TSerial*)(p->info))->nume, ((TSerial*)(p->info))->rating);
            }
            fprintf(out, "(%s, %.1f)].\n", ((TSerial*)(p->info))->nume, ((TSerial*)(p->info))->rating);
        }
        if(strcmp(comanda,"later") == 0){       //adaugarea unui serial in coada watchLater
            char nume[50];
            int top = 0;
            posLater++;                             //Incrementam nuamrul de elemente din coada wLater
            fscanf(in, "%s ", nume);
            TSerial* serial = NULL;
            TLista* lista = NULL;
            serial = cautaSerialL(trending,nume,findName);      //cautam serialul in cele 4 liste
            lista = &trending;
            if(!serial){
                serial = cautaSerialL(documentare,nume,findName);
                lista = &documentare;
            }
            if(!serial){
                serial = cautaSerialL(tutoriale,nume,findName);
                lista = &tutoriale;
            }
            if(!serial){
                serial = cautaSerialL(topTen,nume,findName);
                lista = &topTen;
                top = 1;
            }
            IntrQ(watchLater, serial);                      //introducem serialul in coada, si il eliminam din lista in care l-am gasit
            eliminaSerial(lista, serial, top, decrementTop);
            free(serial);
            fprintf(out, "Serialul %s se afla in coada de asteptare pe pozitia %d.\n", nume, posLater);
        }
        if(strcmp(comanda,"watch") == 0){           //Vizionam un serial.
            char nume[50];
            int durata;
            int top = 0;
            fscanf(in, "%s %d ", nume, &durata);
            TSerial* serial = NULL;
            TLista* lista = NULL;
            if(cautaSerialL(VF(currentlyWatching), nume, findName)){        //Cautam serialul, incepand cu stiva currentlyWatching
                serial = malloc(sizeof(TSerial));                           
                void* help = InitS(sizeof(TSerial));
                if(!help)
                    return 0;
                int extrage = 1;
                while(extrage){                          
                    Pop(currentlyWatching, serial);   
                    if(strcmp(serial->nume, nume) != 0)
                        Push(help, serial);
                    else
                        extrage = 0;
                }
                Rastoarna(currentlyWatching, help);
                free(help);
            }else{                              //Cautam serialul in celelalte liste/cozi
                serial = cautaSerialL(trending,nume,findName);
                lista = &trending;
                if(!serial){
                    serial = cautaSerialL(documentare,nume,findName);
                    lista = &documentare;
                }
                if(!serial){
                    serial = cautaSerialL(tutoriale,nume,findName);
                    lista = &tutoriale;
                }
                if(!serial){
                    serial = cautaSerialL(topTen,nume,findName);
                    lista = &topTen;
                    top = 1;
                }
                if(!serial){                //cautam serialul in coada watchLater
                    posLater--;
                    top = 2;  
                    int extrage = 1, brk = 0;
                    serial = malloc(sizeof(TSerial));
                    void* ajutor = InitQ(sizeof(TSerial));
                    while(extrage){
                        if(!ExtrQ(watchLater, serial)){
                            free(serial);
                            brk = 1;
                            break;
                        }
                        if(strcmp(serial->nume, nume) != 0){
                            IntrQ(ajutor, serial);
                        }
                        else
                            extrage = 0;
                    }
                    ConcatQ(ajutor, watchLater);
                    ConcatQ(watchLater, ajutor);
                    free(ajutor);
                    if(brk){
                        posLater++;
                        break;        //nu exista serialul
                    }
                }
                
                if(top != 2){           //In cazul in care am gasit serialul intr-o lista, il eliminam din aceasta
                    eliminaSerial(lista, serial, top, decrementTop);
                }
            }
            while(durata > 0){           //Incepem sa vizionam serialul. Ne oprim fie cand el nu mai are sezoane, fie cand am terminat durata
                if(IC(serial->sezoane) == NULL){
                    break;
                }
                TSezon* sezon = malloc(sizeof(TSezon));
                ExtrQ(serial->sezoane, sezon); 
                while(IC(sezon->episoade) != NULL){
                    TEpisod* episod = malloc(sizeof(TEpisod));           
                    ExtrQ(sezon->episoade, episod);        
                    if(durata == episod->nrMinute){
                        durata = 0;
                        free(episod);
                        (sezon->nrEp)--;
                        if(IC(sezon->episoade)){
                            void* ajutor = InitQ(sizeof(TSezon));
                            IntrQ(ajutor, sezon);
                            ConcatQ(ajutor, serial->sezoane);
                            ConcatQ(serial->sezoane,ajutor);
                            free(sezon);
                            free(ajutor);
                            break;
                        }else{      
                            (serial->nrSez)--;
                            freeSezon(sezon);
                            break;
                        }
                    }else{
                        if(durata > episod->nrMinute){
                            durata -= episod->nrMinute;
                            free(episod);
                            (sezon->nrEp)--;
                            if(IC(sezon->episoade) == NULL){
                                (serial->nrSez)--;
                                freeSezon(sezon);
                                break;
                            }
                        }else{
                            episod->nrMinute -= durata;
                            durata = 0;
                            void* ajutor1 = InitQ(sizeof(TEpisod));
                            void* ajutor2 = InitQ(sizeof(TSezon));
                            IntrQ(ajutor1, episod);
                            IntrQ(ajutor2, sezon);
                            ConcatQ(ajutor1, sezon->episoade);
                            ConcatQ(sezon->episoade, ajutor1);
                            ConcatQ(ajutor2, serial->sezoane);
                            ConcatQ(serial->sezoane,ajutor2);
                            free(episod);
                            free(sezon);
                            free(ajutor1);
                            free(ajutor2);
                            break;
                        }
                    }
                }
            }
            Push(currentlyWatching, serial);        //introducem serialul in stiva currently watching
            if(IC(serial->sezoane) == NULL){
                fprintf(out, "Serialul %s a fost vizionat integral.\n", nume);//Daca am vizionat tot serialul, il introducem in history
                Push(history, serial);
                Pop(currentlyWatching, serial);       
            }         
            free(serial);
        }
        if(strcmp(comanda,"show") == 0){        //Afisam o lista/coada/stiva in fisierul de iesire
            char nume[50];
            fscanf(in, "%s ", nume);
            fprintf(out, "Categoria %s: [", nume);
            TLista p = topTen;
            if(strcmp(nume, "1") == 0){ 
                p = trending;
            }
            if(strcmp(nume, "2") == 0){
                p = documentare;
            }
            if(strcmp(nume, "3") == 0){
                p = tutoriale;
            }
            if(strcmp(nume, "top10") == 0){
                p = topTen;
            }
            if(strcmp(nume, "later") == 0){
                p = IC(watchLater);
            }
            if(strcmp(nume, "watching") == 0){
                p = VF(currentlyWatching);
            }
            if(strcmp(nume, "history") == 0){
                p = VF(history);
            }   
            if(p == NULL){
                
                fprintf(out, "].\n");
            }else{
                for(; p->urm != NULL; p=p->urm){
                    fprintf(out, "(%s, %.1f), ", ((TSerial*)(p->info))->nume, ((TSerial*)(p->info))->rating);
                }
                fprintf(out, "(%s, %.1f)].\n", ((TSerial*)(p->info))->nume, ((TSerial*)(p->info))->rating);                                                                     
            }
        }

    }
    //Eliberare liste/cozi/stive + inchidere fisiere.
    DistrugeL(&documentare, freeSerial);
    DistrugeL(&trending, freeSerial);
    DistrugeL(&tutoriale, freeSerial);
    DistrugeL(&topTen, freeSerial);
    DistrugeL(&(IC(watchLater)), freeSerial);
    free(watchLater);
    DistrugeL(&(IC(currentlyWatching)), freeSerial);
    free(currentlyWatching);
    DistrugeL(&(VF(history)), freeSerial);
    free(history);
    fclose(in);
    fclose(out);
}


