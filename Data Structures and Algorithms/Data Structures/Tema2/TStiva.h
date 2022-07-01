/*MIRICA Victor - 315CB*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include "TCoada.h"

typedef struct
{ 
	size_t 	dime; 				
	TLista vf; 		
} TStiva, *ASt;

#define DIMES(a) (((ASt)(a))->dime)
#define VF(a) 	(((ASt)(a))->vf)

typedef int (*TF)(void*); 
typedef int (*TFCmp)(void*, void*);

void* InitS(size_t d);   //Initializare stiva
int Push(void* a, void* ae);
int Pop (void* a, void* ae);  
void ResetS (void* a, TF freeEl);  //Resetare stiva
void DistrS (void** a, TF freeEl); //Distrugere stiva
int Rastoarna(void* ad, void* as);   //Rastoarna stiva sursa in stiva destinatie