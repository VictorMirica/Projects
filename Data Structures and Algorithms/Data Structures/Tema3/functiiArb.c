/*MIRICA Victor - 315CB*/
#include "tarb.h"
//Alfabetul folosit
char alfabet[68] = {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! "};
//Functie care returneaza indexul din vectorul alfabet al caracterului primit
int indexAlfabet(char c){
    int i =0;
    for(;i<68;i++){
        if(alfabet[i] == c){
            return i;
        }
    }
    return -1;
}

//Functie care creeaza un nod/tree trie
TArb ConstrNod(){
    TArb node = (TArb)malloc(sizeof(TNod));
    node->hasInfo = 0;
    node->info = NULL;
    for (int i = 0; i < 68; i++){
        node->character[i] = NULL;
    }

    return node;
}
 
//Functie care introduce un string intr-un trie, la final fiind un pointer catre info
void Insert(TArb arb, char* str, void* info){
    //Incepem la primul nod
    TArb aux = arb;
    while(*str){
        //In caz ca nu exista, creez nodul "literei" urmatoare
        if (aux->character[indexAlfabet(*str)] == NULL){
            aux->character[indexAlfabet(*str)] = ConstrNod();
        } 
        //Nod + caracter urmator
        aux = aux->character[indexAlfabet(*str)]; 
        str++;
    }
    //Introducem informatia in ultimul nod.
    aux->hasInfo = 1;
    aux->info = info;
}
 
//Functie care cauta un string intr-un arbore si returneaza informatia corespondenta
void* findString(TArb arb, char* str){
    if(arb == NULL){
        return NULL;
    }
 
    TArb aux = arb;
    while(*str){
        //Cautam stringul litera cu litera
        aux = aux->character[indexAlfabet(*str)];
        if(aux == NULL){
            return NULL;
        }
        str++;
    } 
    if(aux->hasInfo){
        return aux->info;
    } 
    return NULL;
}
//Functie care intoarce al "which"-lea element din arb, in ordine lexicografica.
//ex: which = 0, intoarca primul element.
void* lexicografic(TArb arb, int* which){
    if (!arb)
        return NULL;
    TArb aux = arb;
    if(aux->info){
        //Am ajuns la info pe care o vrem intoarsa
        if(*which == 0){
            return aux->info;
        }
        //Am ajuns la o info, dar nu e cea dorita, trecem peste ea.
        (*which)=(*which)-1;
    }
    //Recursiv, continuam sa cautam un nod cu informatie
   for (int i=0; i< 68; i++){
        void* info = lexicografic(aux->character[i],which); 
        if(info)
            return info;
    }
    return NULL;
}
//Functie care intoarce, lexicografic, in functie de which, elementul care incepe cu str.
//Functie de autocompletare.
void* autoComplete(TArb arb, char* str, int which){
    if(arb == NULL){
        return NULL;
    }

    TArb aux = arb;
    //Parcurgem stringul pana la finalul sau
    while(*str){
        aux = aux->character[indexAlfabet(*str)];
        if(aux == NULL){
            return NULL;
        }
        str++;
    } 
   //Apelam functia lexicografic de la nodul la care am ajuns
    return lexicografic(aux, &which);
}
//Scrie arborele arb in fisierul out.
void printArb(TArb arb, TFp f, FILE* out){
    if (!arb)
        return;
    TArb aux = arb;
    if(aux->info)
        f(aux->info, out);  //Folosim functia f pentru a scrie in fisier
    for (int i=0; i< 68; i++){
        printArb(aux->character[i], f, out); //Recursivitate.
    }
}

//Intoarce 1 daca nodul primit are fii
int hasChildren(TArb aux){
    for(int i = 0; i < 68; i++){
        if(aux->character[i]){
            return 1;      
        }
    }
    return 0;
}
 
//Functie care stringul str din arbore.
int elimString(AArb aux, char* str, TF freeEl){
    if(*aux == NULL){
        return 0;
    }
    if(*str){
        //Cat timp nu am ajuns la finalul str:
        //Ne asiguram ca nodul curent si urmator nu sunt NULL
        //Apelam recursiv functia pentru urmatorul nod
        //Daca nodul nu mai are fii, eliberam nod.
        if (*aux != NULL && (*aux)->character[indexAlfabet(*str)] != NULL 
            && elimString(&((*aux)->character[indexAlfabet(*str)]), str+1, freeEl) && (*aux)->hasInfo == 0){
            if(!hasChildren(*aux)){
                free(*aux);
                (*aux) = NULL;
                return 1;
            }else{
                return 0;
            }
        }
    }
    //Am ajuns la finalul str, in caz ca avem info:
    if(*str == '\0' && (*aux)->hasInfo){
        // Cazul in care nu mai are fii
        if(!hasChildren(*aux)){
            freeEl((*aux)->info);    
            free(*aux);    //Eliberam nod + element
            (*aux) = NULL;
            return 1;       
        }else{  //Cazul in care are alti fii
            freeEl((*aux)->info);
            (*aux)->hasInfo = 0;    //Doar eliberam elementul.
            return 0;      
        }
    }
 
    return 0;
}
//Functie care elibereaza un arbore si elementele din el
void distruge(TArb arb, TF freeEl){
    if(!arb)
        return;
    for(int i = 0; i < 68; i++){
        if(arb->character[i]){
            distruge(arb->character[i], freeEl);//Recursivitate
        }
    }
    if(arb->hasInfo)
        freeEl(arb->info);
    free(arb);
}
//Functie de eliberare pentru un arbore intreg.
void DistrArb(AArb arb, TF freeEl)
{   
    if(!(*arb))
        return;
    distruge(*arb, freeEl);
    *arb = NULL;
    return;
}