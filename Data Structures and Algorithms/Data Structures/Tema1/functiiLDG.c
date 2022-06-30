/* MIRICA Victor - 315CB */
#include "structuri.h"

//functia de inserare in lista generica, la finalul listei
int InsLG(TLDG* l, void* e)
{	
	TLDG aux = malloc(sizeof(TCelulaG));
	if(!aux)
	    return 0;
	aux->info = e;
	if((*l) == NULL){
		*l = aux;
		aux->urm = aux;
		aux->pre = aux;
		return 1;
	}
	aux->urm = *l;
	aux->pre = (*l)->pre;
	(*l)->pre->urm = aux;
	(*l)->pre = aux;

	return 1;
}
//functia de inserare in lista generica inainte de un element dat (el)
int InsBeforeLG(TLDG* l, void* e, TLDG el)
{ 
	TLDG aux = malloc(sizeof(TCelulaG));
	if(!aux)
	    return 0;
	aux->info = e;
	aux->urm = el;
	if(el == (*l)){
		aux->pre =el->pre;
		(*l) = aux;
		if(el->urm == el){
			el->urm = aux;
		}
	}else{
		aux->pre = el->pre;
		el->pre->urm = aux;
	}
	el->pre = aux;
	return 1;
}
//functia de afisare a listei generice
void AfiL(TLDG l, TF afisareEL, FILE* f)
{
	if(l == NULL) {
        fprintf(f,"VIDA\n");
        return;
    }

	TLDG aux = l;
	for(; aux != l->pre; aux = aux->urm) {
		afisareEL(aux->info, f);
		fprintf(f," ");
    }
	afisareEL(aux->info, f);
	fprintf(f," ");
	fprintf(f,"\n");
}