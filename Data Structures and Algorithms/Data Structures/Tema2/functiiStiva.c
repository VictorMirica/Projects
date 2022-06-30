/*MIRICA Victor - 315CB*/
#include "TStiva.h"

/* creeaza stiva vida cu elemente de dimensiune d;
	   este necesar si un al doilea parametru = numar maxim elemente in coada */
void *InitS(size_t d)      
{ 
	ASt a = (ASt)malloc(sizeof (TStiva));			
  	if (!a) return NULL;
  	a->dime = d;
	a->vf = NULL;

  	return (void *)a;
}

int Push(void *a, void *ae)     
{ 
	TLista aux;
	aux = (TLista)malloc(sizeof(TCelula));
	if(!aux) return 0;

	aux->info = malloc(DIMES(a));
	if(!aux->info) return 0;
	memcpy(aux->info, ae, DIMES(a));

	aux->urm = VF(a);
	VF(a) = aux;
	return 1;
}

int Pop(void *a, void *ae)      
{ 
	TLista aux = VF(a); 
	if(aux == NULL) return 0;
	VF(a) = aux->urm;
	memcpy(ae, aux->info, DIMES(a));
	free(aux->info);
	free(aux);
	return 1;
}

void ResetS(void *a, TF freeEl)          
{ 	
	DistrugeL(&VF(a), freeEl);
	VF(a) = NULL;
}

void DistrS(void **a, TF freeEl)           
{ 
	ResetS(*a, freeEl); 		
	free(*a); 		
  	*a = NULL;         
}

int Rastoarna(void *ad, void *as)  
{ 
	if(DIMES(as) != DIMES(ad)) return 0;
	if(VF(as) == NULL) return 0;	

	TLista p = VF(as);
	TLista u;
	while(p){
		u = p->urm;
		p->urm = VF(ad);
		VF(ad) = p;
		p = u;
	}
	VF(as) = NULL;
	return 1;
}

