/*MIRICA Victor - 315CB*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct trie{
    int hasInfo;
    void* info;
    struct trie* character[68];
} TNod, *TArb, **AArb;

char alfabet[68];

typedef int (*TF)(void*); 
typedef int (*TFp)(void*, FILE*);

int indexAlfabet(char c);
TArb ConstrNod();
void Insert(TArb head, char* str, void* info);
void* findString(TArb head, char* str);
int hasChildren(TArb aux);
int elimString(AArb aux, char* str, TF freeEl);
void DistrArb(AArb arb, TF freeEl);
void* autoComplete(TArb arb, char* str, int which);
void* lexicografic(TArb arb, int* which);
void printArb(TArb arb, TFp f, FILE* out);
