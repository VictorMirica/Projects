/*MIRICA Victor - 315CB*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct celula
{ 
  void* info;
  struct celula * urm;
} TCelula, *TLista;

typedef int (*TF)(void*); 
typedef int (*TFCmp)(void*, void*);

TLista AlocCelulaL(void*);     //Functie de alocare a unei celule 
void DistrugeL (TLista*, TF freeEL); //Functie de distrugere a listei
size_t LungimeL(TLista);    //Functie de determinare a lungimii listei
int InsL(TLista* aL, void* ae, TFCmp f); //Inserare in lista
void* InsTop(TLista* aL, void* ae, int top); //Inserare in lista, specifica pentru lista topTen.
void* cautaSerialL(TLista a, char* nume, TFCmp f); //Cauta serial in lista
void eliminaSerial(TLista* a, void* ae, int top, TF f); //Elimina serial din lista