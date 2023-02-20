#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <math.h>
#include <string>
#include <climits>

#include "pthread_barrier_mac.h"

#define MAX_LIST_SIZE 500000

using namespace std;

// Structura care va fi folosita ca argument la functiile pentru thread.
struct arg_struct {
    pthread_barrier_t* barrier;
    pthread_mutex_t* mut;
    string* fileNames;
    int*** mat;
    int** indexes;
    int id;
    int M;
    int R;
    int nrFisiere;
    int* next;
};

// functia thread-urilor reducer
void *reduce_function(void *arg) {
    struct arg_struct *args = (struct arg_struct *)arg;
    pthread_barrier_t* barrier = args->barrier;
    int*** mat = args->mat;
    int** indexes = args->indexes;
    int id = args->id;
    int M = args->M; 

    // pornim reduce doar cand se termina map
    pthread_barrier_wait(barrier);
    if(id < M) {
        return NULL;
    }

    // Creez noua lista mare 
    int listSize = 0;
    for (int i = 0; i < M; i++) {
        listSize += indexes[i][id - M];
    }
    int list[listSize];

    int index = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < indexes[i][id - M]; j++) {
            list[index] = mat[i][id - M][j];
            index++;
        }
    }

    // Verific cate valori unice sunt in lista
    int count = 1;
    for (int i = 1; i < listSize; i++){
        int j;
        for (j = 0; j < i; j++){
            if (list[i] == list[j]){
            break;
            }
        }
        if (i == j){
            count++;
        }
    }

    // Scriu variabila in fisierul de iesire
    string fName = "out";
    fName += to_string(id - M + 2);
    fName += ".txt";
    ofstream  file(fName);
    file << count;
    file.close();
    
    return NULL;
}

// Functie care intoarce urmatorul fisier valabil pentru mapperi.
string getNextFile(string* fileNames, int* next, int nrFisiere) {
    if ((*next) < nrFisiere) { 
        string ret = fileNames[*next];
        (*next)++;
        return ret;
    } else {
        return string(); // Empty string
    }
}

// Functie care introduce in matricea valorilor numerele date in 
// lista exponentilor din care face parte.
int getExponent(int number, int R, int*** mat, int id, int** indexes) {
 
    int exp = 2; // exponentul minim
    while (true) {
        // Limita exponentilor pana la care cautam
        if (exp > R + 1) {
            return 0;
        }

        // Daca numarul este 1, acesta va fi adaugat in taote
        // listele
        if (number == 1) {
            mat[id][exp - 2][indexes[id][exp - 2]] = number;
            indexes[id][exp - 2]++;

            exp += 1;
            continue;
        }

        // Daca 2 la exponentul curent este prea mare, 
        // nu mai avem ce cauta
        if (pow(2, exp) > number) {
            return 0;
        }

        // Pentru a gasi urmatorul exponent
        // facem o cautare binara
        int left = 2;
        int right = 2;
        // Daca indexul din dreapta ^ exp este mai mic ca numarul
        // Acesta poate fi dublat
        while (pow (right, exp) <= number) {
            right *= 2;
        }
        while (right - left > 1) {
            // Calculam mijlocul
            int middle = (left + right) / 2;
            if (pow(middle, exp) <= number) {
                left = middle;
            } else {
                right = middle;
            }
        }
        // Daca indexul din stanga ^ exp este egal cu numarul, am gasit un exp
        if (pow(left, exp) == number) {

            mat[id][exp - 2][indexes[id][exp - 2]] = number;
            indexes[id][exp - 2]++;
        }
        exp += 1;
    }
    return 0;
}

// functia de mapare
void *map_function(void *arg) {
    struct arg_struct *args = (struct arg_struct *)arg;
    pthread_mutex_t* mut = args->mut;
    string* fileNames = args->fileNames;
    int*** mat = args->mat;
    int** indexes = args->indexes;
    int id = args->id;
    int R = args->R;
    int nrFisiere = args->nrFisiere;
    int* next = args->next;

    // Preiau primul fisier pentru fiecare thread
    if (id < nrFisiere) {
        string fName = fileNames[id];
        while (!fName.empty()) {
            // Trec prin fisier linie cu linie
            ifstream file (fName);
            
            string line;
            getline(file, line); // Citesc prima linie
            int number;
            while (getline(file, line)) {
                number = atoi(line.c_str());
                // Gasesc exponentii numarului citit
                getExponent(number, R, mat, id, indexes);
            }

            file.close();
            // folosind un mutex, preiau urmatorul fisier, incrementez
            // variabila next pana cand ajung la ultimul fisier.
            pthread_mutex_lock(mut);
            fName = getNextFile(fileNames, next, nrFisiere);
            pthread_mutex_unlock(mut);
        }
    }
    reduce_function(arg);
    return NULL;
}

// functie care aloca matricea de valori (matrice 3d)
int ***allocMat(int M, int R, int n)
{
    int ***p;

    p = (int***)malloc(M * sizeof *p);

    for (int i=0; i < M; i++)
        p[i] = (int**)malloc(R * sizeof *p[i]);

    for (int i=0; i < M; i++)
        for (int j=0; j < R; j++)
            p[i][j] = (int*)malloc(n * sizeof *p[i][j]);

    return p;
}

void freeMat(int ***mat, int M, int R)
{
    for (int i=0; i < M; i++) {
        if (mat[i] != NULL) {
            for (int j=0; j < R; j++)
                free(mat[i][j]);
            free(mat[i]);
        }
    }
    free(mat);
}


int main(int argc, char *argv[]) {

    // Verificare si citire parametri
    if (argc < 4) {
        printf("Numar insuficient de parametri!");
        exit(1);
    }

	int M = atoi(argv[1]);
	int R = atoi(argv[2]);
    string fileName = argv[3];

    // Vector de threaduri si id-uri
    pthread_t tid[M + R];
	struct arg_struct structs[M + R];

    // Vectorul pentru cele doua functii (map si reduce)
	void* (*p[2]) (void *arg);
	p[0] = map_function;
	p[1] = reduce_function;

    pthread_barrier_t barrier;
    pthread_barrier_init(&barrier, NULL, M + R);
    pthread_mutex_t mut;
    pthread_mutex_init(&mut, NULL);
    int next = M;

    // fiecare thread M are o lista de 
    // R liste pe care le umple
    
    // dupa care, fiecare thread R
    // lucreaza pe cate M liste
    // (R1 lucreaza pe lista 1 de la fiecare M
    // R2 lucreaza pe lista 2 de la fiecare M etc
    
    // exemplu de matrice
    // M = 2
    // R = 3
    // [[1,2], [3,4], [1]]  <- M1
    // [[2],   [4],   [6,7,8]] <- M2
    //  ^R1     ^R2     ^R3
    
    // la M-uri lucrez pe mat[id][0, 1, 2, ..., R - 1]
    // la R-uri lucrez pe mat[0, 1, 2, ..., M -1 ][id - M]

    int n = MAX_LIST_SIZE; //Cate elemente poate avea fiecare lista
    // Marimea lui n nu va afecta viteza Reducerului deoarece
    // acesta se opreste cand ajunge la ultimul element introdus
    // in lista, deci nu o va parcurge niciodata pe toata, ci doar cat este nevoie.
    int*** mat = allocMat(M, R, n);

    // un vector 2d care reprezinta indecsii pentru cele R liste ale unui thread M (threadul i)
    // ex: indexes[3][0] = 5
    // prima lista (puterea a 2-a) a thread-ului mapper cu id = 3 are 5 elemente.
    int** indexes;
    indexes = (int**)malloc(M * sizeof(int*));
    for (int i=0; i < M; i++)
        indexes[i] = (int*)calloc(R, sizeof(int));



    // Citim fisierul principal, preluam prima linie
    ifstream mainFile (fileName);
    string line;
    getline(mainFile, line);
    int nrFisiere = atoi(line.c_str());

    string files[nrFisiere];

    // Citim numele celorlalte fisiere
    for (int i = 0; i < nrFisiere; i++) {
        getline(mainFile, files[i]);
            
    }

    mainFile.close();
    
    // Pornesc threadurile
    for (int i = 0; i < M + R; i++) {
        int f = 0;
        i < M ? f = 0 : f = 1; // in functie de ID, aleg functia

        structs[i].barrier = &barrier;
        structs[i].mut = &mut;
        structs[i].fileNames = files;
        structs[i].mat = mat;
        structs[i].indexes = indexes;
        structs[i].id = i;
        structs[i].M = M;
        structs[i].R = R;
        structs[i].nrFisiere = nrFisiere;
        structs[i].next = &next;

        if (pthread_create(&tid[i], NULL, p[f], &structs[i]) != 0) {
			printf("Eroare la crearea thread-ului %d\n", i);
			exit(-1);
		}
	}

    // Join threads
    for (int i = 0; i < M + R; i++) {
		if (pthread_join(tid[i], NULL) != 0) {
			printf("Eroare la asteptarea thread-ului %d\n", i);
			exit(-1);
		}
	}

    freeMat(mat, M, R);
    pthread_mutex_destroy(&mut);
    pthread_barrier_destroy(&barrier);

  	pthread_exit(NULL);
}