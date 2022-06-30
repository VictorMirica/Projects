/*MIRICA Victor - 315CB*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include "TLista.h"

typedef struct
{ 
	size_t 	dime; 
	TLista ic;
	TLista sc;
} TCoada, *AQ;

#define IC(a) 	(((AQ)(a))->ic)
#define SC(a) 	(((AQ)(a))->sc)
#define DIMEC(a) (((AQ)(a))->dime)								
#define VIDA(a)         ((((AQ)a)->ic == NULL && ((AQ)a)->sc == NULL))

typedef int (*TF)(void*); 
typedef int (*TFCmp)(void*, void*);

void* InitQ(size_t d); //Initializare coada
int IntrQ(void* a, void* ae); 
int ExtrQ(void* a, void* ae); 
void ResetQ(void* a, TF freeEl);   //Resetare caoda
void DistrQ(void** a, TF freeEl);  //Distrugere coada
int ConcatQ(void *ad, void *as);	//Concateneaza coada sursa peste coada destinatie