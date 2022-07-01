/*MIRICA Victor - 315CB*/
#include "TCoada.h"

void* InitQ(size_t d)
{ 
	AQ a = (AQ)malloc(sizeof (TCoada));			
  	if (!a) return NULL;
  	a->dime = d;
	a->ic = NULL;
	a->sc = NULL;
  	return (void *)a;
}


int IntrQ(void *a, void *ae)   
{ 
	TLista aux;
	aux = (TLista)malloc(sizeof(TCelula));
	if(!aux) return 0;

	aux->info = malloc(DIMEC(a));
	if(!aux->info) return 0;
	memcpy(aux->info, ae, DIMEC(a));
	
	if(VIDA(a)){
		aux->urm = NULL;
		IC(a) = aux; SC(a) = aux;
		return 1;
	}else{
		aux->urm = NULL;
		SC(a)->urm = aux;
		SC(a) = aux;
		return 1;
	}
}

int ExtrQ (void *a, void *ae)  
{ 
	if(VIDA(a)) return 0;

	TLista aux = IC(a);
	IC(a) = aux->urm;
	memcpy(ae, aux->info, DIMEC(a));
	free(aux->info);
	free(aux);
	
	if(IC(a) == NULL) SC(a) = NULL;
	return 1;
}

void ResetQ(void *a, TF freeEl)       
{ 
	DistrugeL(&IC(a), freeEl);
	IC(a) = SC(a) = NULL;
}  

void DistrQ(void **a, TF freeEl)     
{ 
	ResetQ(*a, freeEl);
	free(*a);
	*a = NULL;
}

int ConcatQ(void *ad, void *as) 
{ 
	if(VIDA(as)) return 0;
	if(VIDA(ad)){
		IC(ad) = IC(as);
		SC(ad) = SC(as);
		IC(as) = SC(as) = NULL;
		return 1;
	}
	SC(ad)->urm = IC(as);
	SC(ad) = SC(as);
	IC(as) = SC(as) = NULL;
	return 1;
}


