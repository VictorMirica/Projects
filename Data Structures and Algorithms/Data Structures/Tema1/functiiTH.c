/* MIRICA Victor - 315CB */
#include "structuri.h"
//functia de initializare a tabelei hash
TH* IniTH(size_t M, TFHash fh)
{
    TH* h = (TH *) calloc(sizeof(TH), 1);
    if (!h) {
        printf("eroare alocare\n");
        return NULL;
    }

    h->v = (TLDG *) calloc(M, sizeof(TLDG));
    if(!h->v) {
        printf("eroare alocare\n");
        free(h);
        return NULL;
    }

    h->M = M;
    h->fh = fh;
    return h;
}
//functia de afisare a intregii tabele hash
void AfiTH(TH* h, TF afiEl, FILE* f){
    TLDG p;
    TLDG el;
    int i;
    for(i = 0; i < h->M; i++) {
        p = h->v[i];
        if(p != NULL) {
            fprintf(f, "%d: ", i);
            for(el = p; el != p->pre; el = el->urm){
                afiEl(el->info, f);
                fprintf(f, " ");
            }
            afiEl(el->info, f);
            fprintf(f, " ");
            fprintf(f, "\n");
        }
    }
}
//functia de afisare a unei valori din tabela hash, cautata in functie de cheia oferita ca parametru
void AfiVal(char* key, int codHash, TH* h, TF afiel, TFCmp hasKey, FILE* f){
    TLDG p;
    TLDG el;
    p = h->v[codHash];
    if(p == NULL) {
        fprintf(f, "NULL");
        return;
    }
        
    for(el = p; el != p->pre; el = el->urm){
        if(hasKey(key, el->info)){           
            afiel(el->info, f);
            return;
        }
    }
    if(hasKey(key, el->info)){           
        afiel(el->info, f);
        return;
    }
    fprintf(f, "NULL");
    return;     
}
//functia de inserare in tabela hash
int InsTH(TH*a, void* e, TFCmp f)
{      
    int cod = a->fh(e, a->M), rez;
    TLDG el;
    if(a->v[cod] == NULL){
        rez = InsLG(a->v+cod, e);
        return rez;
    }
    for(el = a->v[cod]; el != a->v[cod]->pre; el = el->urm) {
        if (f(el->info, e) == 1)
            return 0;
        if(f(el->info, e) == 2){
            rez = InsBeforeLG(a->v+cod, e, el);
            return rez;
        }
    }
    if (f(el->info, e) == 1)
            return 0;
    if(f(el->info, e) == 2){
            rez = InsBeforeLG(a->v+cod, e, el);
            return rez;
    }
    rez = InsLG(a->v+cod, e);
    return rez;
}
//functia de stergere a unei structuri (cheie, valoare) din tabela hash, in functie de cheia primita ca parametru
int DelVal(char* key, int codHash, TH*h, TE freeEl, TFCmp hasKey){
    TLDG* p;
    TLDG el;
    p = &(h->v[codHash]);
    if(*p == NULL){
        return 0;
    }
    for(el = *p; el != (*p)->pre; el = el->urm){
        if(hasKey(key, el->info)){
            if(el == *p){
                *p = el->urm;
                if(el->urm == el){
                  *p = NULL;
                }else{
                    el->urm->pre = el->pre;   
                    el->pre->urm = el->urm;
                }
            }else{
                el->urm->pre = el->pre;   
                el->pre->urm = el->urm;            
            }
            freeEl(el->info);
            free(el);
            return 1;
        }
    }
    if(hasKey(key, el->info)){
    if(el == *p){
        *p = el->urm;
        if(el->urm == *p){
            *p = NULL;
        }else{
            el->urm->pre = el->pre;   
            el->pre->urm = el->urm;
        }
    }else{
        (*p)->pre = el->pre;
        el->pre->urm = *p;                  
    }
    freeEl(el->info);
    free(el);
    return 1;
    }
}
//functia de cautare a unei chei date ca argument in tabela hash, intoarce true respectiv false
void FindKey(char* key, int codHash, TH* h, TFCmp hasKey, FILE* f){
    TLDG p;
    TLDG el;
    p = h->v[codHash];
    if(p == NULL) {
        fprintf(f, "False");
        return;
    }
        
    for(el = p; el != p->pre; el = el->urm){
        if(hasKey(key, el->info)){           
            fprintf(f, "True");
            return;
        }
    }
    if(hasKey(key, el->info)){           
        fprintf(f, "True");
        return;
    }
    fprintf(f, "False");
    return;     
}   
//functia de distrugere/eliberare a tabelei hash
void DistrugeTH(TH** h)
{
    TLDG * p;
    TLDG el, aux, ultim;
    int i = 0;
    for (; i < (*h)->M; i++) {
        if((*h)->v[i] != NULL){
            ultim = (*h)->v[i]->pre;
            for(el = (*h)->v[i]; el != ultim;) {
                aux = el;
                el = el->urm;
                free(aux->info);
                free(aux);
            }
            free(el->info);
            free(el);
        }
    }
    free((*h)->v);
    free(*h);
    *h = NULL;
}