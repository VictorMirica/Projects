/* MIRICA Victor - 315CB */
#include <stdio.h>
#include <string.h>
#include "structuri.h"
//Structura de tip (cheie, valoare)
typedef struct {
	char key[50];
	char value[50];
} TReg;
//functie pentru generarea codului hash
int codHash(char * key, int M){
    int sum = 0;   
    int i = 0;
    for(; i < strlen(key); i++){
        sum = sum + key[i];
    }
    return (sum%M);
}
//functie care printeaza valoarea pentru o structura TReg data
void printValue(void * element, FILE* f){
    TReg* reg = (TReg*) element;
    fprintf(f, "%s", reg->value);
    return;
}
//functie care printeaza cheia pentru o structura TReg data
void printKey(void * element, FILE* f){
    TReg* reg = (TReg*) element;
    fprintf(f, "%s", reg->key);
    return;
}
//functie de comparare, returneaza 1 daca cele doua chei primite ca argument sunt egale
int hasKey(void * e1, void * e2){
    TReg * reg = (TReg *) e2;
    if (strcmp((char*)e1, reg->key) == 0)
        return 1;
    return 0;
}
//functie de comparare, returneaza 1 daca cele doua elemente au valori sau chei egale, returneaza 2 daca primul element are 
//valoarea cheii mai mare decat cheia celui de-al doi-lea element. Returneaza 0 daca cele doua elemente au valori diferite
//si cheia celui de-al doi-lea este mai mare decat cea a primului element.
int cmpReg(void * e1, void * e2)
{
	TReg * reg1 = (TReg *) e1;
	TReg * reg2 = (TReg *) e2;

	if (strcmp(reg1->key, reg2->key) == 0)
		return 1;

	if (strcmp(reg1->value, reg2->value) == 0) 
		return 1;
    
    if(strcmp(reg1->key, reg2->key) > 0){
        return 2;
    }

	return 0;
}


int main( int argc, char *argv[] ){
    //functia trebuie sa primeasca 3 argumente in linia de comanda M, hash.in, hash.out
    if(argc != 4){
        printf("Programul a fost rulat incorect din linia de comanda\n");
        return 0;
    }
    int M = atoi(argv[1]);
    //initializarea tabelei hash si deschiderea fisierelor text
    TH* h = NULL;
    h = (TH *) IniTH(M, codHash);
	if(h == NULL)
		return 0;
    
    FILE *in, *out;
    char * line = NULL;
	size_t len = 0;
    in = fopen(argv[2], "rt");
    out = fopen(argv[3], "wt");
    if (in == NULL)
		return 0;
    if (out == NULL)
		return 0;
    //citirea fisierului text
    while (getline(&line, &len, in) != -1){      
        //despartirea liniei citite in valorile comanda, cheie si valoare (cand este cazul)(ex: poate fi citita doar o comanda, sau doar o comanda+cheie)
        char *tok, *val,*comanda,*key;
        int freekey = 0;
        int freeval = 0;
        int freecomanda = 0;
        tok = strtok(line, " \n");
        if(tok != NULL){
            comanda = malloc(50);
            if(comanda == NULL)
                return 0;
            strcpy(comanda, tok); 
            if(comanda == NULL)
                return 0;            
            if (comanda[strlen(comanda) - 1] == '\r' || comanda[strlen(comanda) - 1] == '\n')                   
                comanda[strlen(comanda) - 1] = '\0';   
            freecomanda = 1;      
        }
        tok = strtok(NULL, " \n");
        if(tok != NULL){
            key = malloc(50);
            if(key == NULL)
                return 0;
            strcpy(key, tok);
            if(key == NULL)
                return 0;
            if (key[strlen(key) - 1] == '\r' || key[strlen(key) - 1] == '\n') 
                key[strlen(key) - 1] = '\0';
            freekey = 1;  
        }
        tok = strtok(NULL, " \n");
        if(tok != NULL){
            val = malloc(50);
            if(val == NULL)
                return 0;
            strcpy(val, tok);
            if(val == NULL)
                return 0;
            if (val[strlen(val) - 1] == '\r' || val[strlen(val) - 1] == '\n')
                val[strlen(val) - 1] = '\0';
            freeval = 1;
        }
        //Rularea functiilor respective pentru comanda citita
        if(strcmp(comanda,"put") == 0){
            TReg* reg = malloc(sizeof(TReg));
            if(reg == NULL)
                return 0;
            strcpy(reg->key, key);
            if(reg->key == NULL)
                return 0;
            strcpy(reg->value, val);
            if(reg->value == NULL)
                return 0;
            if(!InsTH(h, reg, cmpReg))
                free(reg);
        }
        if(strcmp(comanda,"get") == 0){
            AfiVal(key, codHash(key,h->M), h, printValue, hasKey, out);
            fprintf(out,"\n");
        }
        if(strcmp(comanda,"remove") == 0){
            DelVal(key, codHash(key,h->M), h, free, hasKey);
        }
        if(strcmp(comanda,"find") == 0){
            FindKey(key, codHash(key,h->M), h, hasKey, out);
            fprintf(out,"\n");
        }
        if(strcmp(comanda,"print") == 0){
            AfiTH(h, printValue, out);
        }
        if(strcmp(comanda,"print_bucket") == 0){
            if(atoi(key) < h->M)
                AfiL(h->v[atoi(key)],printValue, out);
        }
        //eliberari
        if(freecomanda){
            free(comanda);
        }
        if(freekey){
            free(key);
        }
        if(freeval){
            free(val);
        }
    }
    free(line);
    fclose(in);
    fclose(out);
    DistrugeTH(&h);
}