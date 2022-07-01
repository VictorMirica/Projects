/*MIRICA Victor - 315CB*/
#include <ctype.h>
#include "TLista.h"

int InsL(TLista* aL, void* ae, TFCmp f)
{
	TLista aux = malloc(sizeof(TCelula));
	if(!aux)
	  return 0;

	aux->info = ae;
  if(!(*aL)){
    aux->urm = NULL;
    *aL = aux;
    return 1;
  }

  if(f(ae, (*aL)->info) == 1){
    aux->urm = *aL;
    *aL = aux;
    return 1;
  }

  int pos = 2;
  TLista pre = *aL;
  for(TLista p = (*aL)->urm; p != NULL; p=p->urm, pre=pre->urm){
   if(f(ae, p->info) == 1){  
    aux->urm = p;
    pre->urm = aux;
    return pos;
   }
   pos++;
  }
  aux->urm = NULL;
  pre->urm =aux;
	return pos;
}

void* InsTop(TLista* aL, void* ae, int top){

	TLista aux = malloc(sizeof(TCelula));
	if(!aux)
	  return NULL;

	aux->info = ae;
  if(top == 1){
    aux->urm = *aL;
    *aL = aux;
  }else{
    TLista pre = *aL;
    TLista p = (*aL)->urm;
    for(int i = 0; i < (top - 2); i++){
      p=p->urm;
      pre=pre->urm;
    }
    aux->urm = p;
    pre->urm = aux;
  }

  if(LungimeL(*aL) > 10){
    TLista pre = *aL;
    TLista p = (*aL)->urm;
    for(; p->urm != NULL; p=p->urm, pre = pre->urm){
    }
    pre->urm = NULL;
    void* serial = p->info;
    free(p);
    return serial;
  }
  return NULL;

}

TLista AlocCelulaL(void* e){ 
  TLista aux = (TLista)malloc(sizeof(TCelula)); 
  if (aux)                         
  { aux->info = e;             
    aux->urm = NULL;
  }
  return aux;          
}

void DistrugeL(TLista* aL, TF freeEL){
  TLista aux;
  while(*aL)
  {
    aux = *aL;
    *aL = aux->urm;
    freeEL(aux->info);
    free(aux);
  }
}

size_t LungimeL(TLista a) 
{
	size_t lg = 0;
	for (; a != NULL; a = a->urm)
    lg++;

	return lg;
}

void* cautaSerialL(TLista a, char* nume, TFCmp f){
    if(!a)
      return NULL;
    for (; a != NULL; a = a->urm){
      if(f(a->info, nume)){
        return a->info;
      }
    }
    return NULL;    
}

void eliminaSerial(TLista* a, void* ae, int top, TF f){
  if((*a)->info == ae){
    TLista aux = *a;
    (*a) = (*a)->urm;
    free(aux);
    if(top == 1){
      for(aux = *a; aux != NULL; aux=aux->urm){
        f(aux->info);
      }
    }
    return;
  }

  TLista u = *a;
  TLista p = (*a)->urm;
  for (; p != NULL; p = p->urm, u = u->urm){
    if(p->info == ae){
      u->urm = p->urm;
      free(p);
      if(top == 1){
        for(p = u->urm; p != NULL; p=p->urm){
          f(p->info);
        }
      }
      return;
    }
  }
  return;
}




