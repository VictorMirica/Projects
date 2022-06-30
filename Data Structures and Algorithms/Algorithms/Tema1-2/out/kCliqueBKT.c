#include <stdlib.h>
#include <stdio.h>

#define MAX 300

// Vectorul noduri va pastra nodurile clicii pe care trebuie sa o aflam
int noduri[MAX];
int n;

// Tabloul bi-dimensional al grafului va avea valoarea 1 in cazul in care
// exista o muchie intre nodurile rand-coloana si 0 in caz contrar
int graf[MAX][MAX];

// Vectorul grad va tine gradul nodului de pe indexul respectiv
int grad[MAX];

void findClique(int nod, int len, int k, int* flag){
    
    // Inseram nodurile pentru clică
    for (int i = nod; i <= n; i++){
        
        // Testăm daca nodul are suficiente muchii a.i sa faca
        // parte din k-clique
        if (grad[i] >= k - 1){
 
            noduri[len] = i;
 
            // Testam daca ce avem pana acum in vectorul de noduri
            // formeaza o clique
            int clique = 1;
            for (int i = 1; i < len + 1; i++)
                for (int j = i + 1; j < len + 1; j++)
                    if (graf[noduri[i]][noduri[j]] == 0)
                        clique = 0;
            
            // In cazul in care avem o clică testăm dacă lungimea
            // la care ne aflăm este cea dorită (k)
            if (clique){
                if (len < k){

                    findClique(i, len + 1, k, flag);
                }else{

                   *flag = 1;
                   return;
                }
            }
        }
    }
}

int main(int argc, char *argv[]){

    FILE* f = fopen(argv[1], "r");
    int k,m;

    // Citim din fisier
    fscanf(f,"%d\n %d\n %d\n",&k,&n,&m);

    // Alocam si citim tabloul bi-dimensional care reprezinta
    // muchiile dintre noduri
    int** edges = malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++){

        edges[i] = malloc(2 * sizeof(int));
    }

    for (int i = 0; !feof(f); i++){

        fscanf(f,"%d ",&edges[i][0]);
        fscanf(f,"%d\n",&edges[i][1]);
    }

    // Scriem in vectorul de grade si in tabloul grafului
    for (int i = 0; i < m; i++) {

        graf[edges[i][0]][edges[i][1]] = 1;
        graf[edges[i][1]][edges[i][0]] = 1;

        grad[edges[i][0]]++;
        grad[edges[i][1]]++;
    }

    int flag = 0;

    // Apelam functia, incepem prin a cauta un k-Clique de lungimea 1. Vom incrementa 
    // lungimea apeland functia recursiv pana cand ajungem la lungimea k
    findClique(1, 1, k, &flag);
    if(flag){

        printf("True");
    }else{

        printf("False");
    }

    for (int i = 0; i < m; i++)
        free(edges[i]);
    free(edges);
    return 0;
}