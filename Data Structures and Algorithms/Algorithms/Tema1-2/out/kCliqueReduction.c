#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
     FILE* f = fopen(argv[1], "r");
    int k,m,n;

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

    int** graf = malloc((n+1) * sizeof(int*));
    for (int i = 0; i < n+1; i++){

        graf[i] = malloc((n+1) * sizeof(int));
    }

    // Initializam matricea ce va reprezenta graful
    // Aceasta va avea 1 in cazul in care intre nodurile
    // care reprezinta linia si coloana se afla o muchie, 0 in caz contrar
    for (int i = 0; i < m; i++) {

        graf[edges[i][0]][edges[i][1]] = 1;
        graf[edges[i][1]][edges[i][0]] = 1;
    }

    printf("(");

    // Primul set de clauze
    // Pentru fiecare i, este un nod cu indexul i in clică
    for(int i = 1; i <= k; i++){
        for(int v = 1; v <= n; v++){

            if(v != n){

                printf("x%d%d V ", i,v);
            }else{

                printf( "x%d%d", i,v);
            }
        }
        if(i != k){
            
            printf(") ^ (");
        }else{

            printf(")");
        }
    }

    // Al doilea set de clauze
    // Pentru feicare i si j, i != j, nodul cu indexul i este diferit de cel cu indexul j
    for(int v = 1; v <= n; v++){
        for(int i = 1; i <= k; i++){
            for(int j = i+1 ; j <= k; j++){

                printf(" ^ (~x%d%d V ~x%d%d)", i,v,j,v);
            }
        }
    }

    // Al treilea set de clauze
    // Pentru fiecare nod u si v, daca acestia nu au o muchie intre ei
    // (graf[u][v] == 0), nu pot sa apartina aceleiasi clici.
    for(int u = 1; u <= n; u++){
        for(int v = 1; v <= n; v++){
            if(graf[u][v] == 0){
                for(int i = 1; i <= k; i++){
                    for(int j = i+1 ; j <= k; j++){

                        printf(" ^ (~x%d%d V ~x%d%d)", i,u,j,v);
                    }
                }
            }
        }
    }

    for (int i = 0; i < m; i++)
        free(edges[i]);
    free(edges);

    for (int i = 0; i < n+1; i++)
        free(graf[i]);
    free(graf);

    return 0;
}