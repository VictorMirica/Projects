/* MIRICA Victor - 315CB */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef int (*TFHash)(char*, int); //functia de hashing

//cele trei structuri: Celula pentru lista dubla generica, capul listei duble generic si tabela hash
typedef struct celulag
{
  void* info;       
  struct celulag *urm;
  struct celulag *pre;   
} TCelulaG, *TLDG; 

typedef struct
{
  size_t M;
  TFHash fh;
  TLDG *v;
} TH;
//functii generice:
typedef void (*TE)(void*); //functie de eliberare
typedef void (*TF)(void*, FILE*); //functia de afisare
typedef int (*TFCmp)(void*, void*); //functia de comparare

int InsLG(TLDG*, void*);
int InsBeforeLG(TLDG* l, void* e, TLDG el);
void AfiL(TLDG, TF, FILE*);

TH* IniTH(size_t M, TFHash fh);
void AfiTH(TH*a, TF afiEl, FILE* f);
void AfiVal(char* key, int codHash, TH* h, TF afiel, TFCmp hasKey, FILE* f);
int InsTH(TH*a, void*e, TFCmp f);
int DelVal(char* key, int codHash, TH*h, TE freeEl, TFCmp hasKey);
void FindKey(char* key, int codHash, TH* h, TFCmp hasKey, FILE* f);
void DistrugeTH(TH** h);