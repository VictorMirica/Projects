#include<mpi.h>
#include<stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

static int num_neigh;
static int *neigh;

// Coordonatorii clusterelor citesc fisierele de intrare
void read_neighbours(int rank, int error) {
    FILE *fp;
    char file_name[15];
    sprintf(file_name, "./cluster%d.txt", rank);

    // Citesc prima linie, care reprezinta numarul de workeri
    fp = fopen(file_name, "r");
	fscanf(fp, "%d", &num_neigh);
    // Pe langa acele procese, ca neighbours o sa avem
    // si coordonatorii vecini
    num_neigh += 2;

	neigh = malloc(sizeof(int) * num_neigh);

	for (size_t i = 0; i < num_neigh - 2; i++) {
		fscanf(fp, "%d", &neigh[i]);
        MPI_Send(&rank, 1, MPI_INT, neigh[i], 0, MPI_COMM_WORLD);
        printf("M(%d,%d)\n", rank, neigh[i]);
    }

    // In vectorul neigh, trebuie adaugati si coordonatorii vecini.
    if (rank != 0) {
        // In cazul in care avem un defect pe canalul de comunicatii,
        // procesul 1 nu va fi vecin cu 0
        if (rank == 1 && error) {
            neigh[num_neigh - 1] = -1;
        } else {
            neigh[num_neigh - 1] = rank - 1;
        }
    } else {
        neigh[num_neigh - 1] = 3;
    }

    if (rank != 3) {
        // In cazul in care avem un defect pe canalul de comunicatii,
        // procesul 0 nu va fi vecin cu 1
        if (rank == 0 && error) {
            neigh[num_neigh - 2] = -1; 
        } else {
            neigh[num_neigh - 2] = rank + 1;
        }
    } else {
        neigh[num_neigh - 2] = 0;
    }
}

int* get_dst(int rank, int numProcs, int leader) {
	MPI_Status status;

	int *v = malloc(sizeof(int) * numProcs);
	int *vRecv = malloc(sizeof(int) * numProcs);

	memset(v, -1, sizeof(int) * numProcs);
	memset(vRecv, -1, sizeof(int) * numProcs);
	
	if (rank == leader)
		v[rank] = -1;
	else {
		// Daca procesul curent este worker, inseamna ca va astepta un mesaj de la un coordonator 
		MPI_Recv(vRecv, numProcs, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
		v[rank] = status.MPI_SOURCE;
	}

	// Coordonatorii trimit vectorul de parinti propriu catre workeri
    if (rank == leader)
        for (int i = 0; i < num_neigh - 2; i++) {
            MPI_Send(v, numProcs, MPI_INT, neigh[i], 0, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, neigh[i]);
        }


	// Coordonatorii asteapta vectorul workerilor sai
    if (rank == leader)
        for (int i = 0; i < num_neigh - 2; i++) {
            MPI_Recv(vRecv, numProcs, MPI_INT, neigh[i], 0, MPI_COMM_WORLD, &status);
            for (int j = 0; j < numProcs; j++) {
                if (vRecv[j] != -1)
                    v[j] = vRecv[j];
            }
        }

	// Toti workerii propaga parintelui vectorul propriu
	if (rank != leader) {
		MPI_Send(v, numProcs, MPI_INT, v[rank], 0, MPI_COMM_WORLD);
        printf("M(%d,%d)\n", rank, v[rank]);
		MPI_Recv(v, numProcs, MPI_INT, v[rank], 0, MPI_COMM_WORLD, &status);
	}

    // Coordonatorii propaga intre ei topologia curenta
    if (rank == leader) {
        // Trimit in sens trigonometric topologia
        if (rank == 0) {
            MPI_Send(v, numProcs, MPI_INT, neigh[num_neigh - 1], 0, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, neigh[num_neigh - 1]);
        } else {
            MPI_Recv(vRecv, numProcs, MPI_INT, neigh[num_neigh - 2], 0, MPI_COMM_WORLD, &status);
        }
        
        // Introduc in topologie
        if (rank != 0) {
            for (int j = 0; j < numProcs; j++) {
                if (vRecv[j] != -1)
                    v[j] = vRecv[j];
            }
        }

        // Dau mai departe in sensul trigonometric
        if (rank != 0 && rank != 1) {
            MPI_Send(v, numProcs, MPI_INT, neigh[num_neigh - 1], 0, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, neigh[num_neigh - 1]);
        }

        // Odata ajuns la procesul 1, trimit in sens ceasornic
        if (rank == 1) {
            MPI_Send(v, numProcs, MPI_INT, neigh[num_neigh - 2], 0, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, neigh[num_neigh - 2]);
        } else {
            MPI_Recv(vRecv, numProcs, MPI_INT, neigh[num_neigh - 1], 0, MPI_COMM_WORLD, &status);
        }

        // Introduc iar elementele noi in topologie
        if (rank != 1) {
            for (int j = 0; j < numProcs; j++) {
                if (vRecv[j] != -1)
                    v[j] = vRecv[j];
            }
        }
        
        // Trimit mai departe in sens ceasornic
        if (rank != 0 && rank != 1) {
            MPI_Send(v, numProcs, MPI_INT, neigh[num_neigh - 2], 0, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, neigh[num_neigh - 2]);
        }
    }

	// Procesul trimite doar copiilor topologia curenta
    if (rank == leader)
        for (int i = 0; i < numProcs; i++) {
            if (v[i] == rank) {
                MPI_Send(v, numProcs, MPI_INT, i, 0, MPI_COMM_WORLD);
                printf("M(%d,%d)\n", rank, i);
            }
        }

	return v;
}

void getArray(int n, int rank, int numProcs, int leader) {

    int res[n];
    int auxRes[n];
    int finalRes[n];
    int startIndex = -1;
	
    MPI_Status status;

    int workLoad = n / (numProcs - 4);
    if (rank != leader) {
        // N / W, unde W este numarul de workeri
        // Indexul de inceput al fiecarul worker
        startIndex = (workLoad * (rank - 4));
    }

    if (rank == 0) {
        // Procesul 0 genereaza vectorul
        for (int i = 0; i < n; i++) {
            res[i] = n - i - 1;
        }
        // Trimit vectorul catre procesul coordonator din stanga mea
        // Si catre copii mei
        MPI_Send(res, n, MPI_INT, neigh[num_neigh - 1], 0, MPI_COMM_WORLD);
        printf("M(%d,%d)\n", rank, neigh[num_neigh - 1]);


        // Catre copii
        for (int i = 0; i < num_neigh - 2; i++) {
            MPI_Send(res, n, MPI_INT, neigh[i], 0, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, neigh[i]);
        }
        

    } else if (rank == leader) {
        // In cazul in care sunt un coordonator, preiau vectorul v de la procesul 0
        // si il trimit copiilor mei
        MPI_Recv(res, n, MPI_INT, neigh[num_neigh - 2], 0, MPI_COMM_WORLD, &status);

        for (int i = 0; i < num_neigh - 2; i++) {
            MPI_Send(res, n, MPI_INT, neigh[i], 0, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, neigh[i]);
        }

        // In cazul in care nu sunt procesul 1, trebuie sa trimit si la urm coordonator
        if (rank != 1) {
            MPI_Send(res, n, MPI_INT, neigh[num_neigh - 1], 0, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, neigh[num_neigh - 1]);
        }


    } else {
        // Sunt worker, astept vectorul v si aplic calculul
        MPI_Recv(res, n, MPI_INT, neigh[0], 0, MPI_COMM_WORLD, &status);

        for (int i = 0; i < workLoad; i++) {
            res[startIndex + i] = res[startIndex + i] * 5;
        }

        // Daca sunt ultimul proces worker, lucrez pana termin vectorul
        if (rank == (numProcs - 1) && (startIndex + workLoad != n)) {
            for(int i = startIndex + workLoad; i < n; i++) {
                res[i] = res[i] * 5;
            }
        }

        // Dupa ce am realizat operatia, o trimit parintelui
        MPI_Send(res, n, MPI_INT, neigh[0], 0, MPI_COMM_WORLD);
        printf("M(%d,%d)\n", rank, neigh[0]);
    }

    if (rank == leader) {
        for (int i = 0; i < n; i++) {
            auxRes[i] = res[i];
        }
        // Primesc vectorul completat partial de la diferitii workeri copii
        for (int i = 0; i < num_neigh - 2; i++) {
            MPI_Recv(res, n, MPI_INT, neigh[i], 0, MPI_COMM_WORLD, &status);
            startIndex = workLoad * (neigh[i] - 4);
            for (int i = 0; i < workLoad; i++) {
                auxRes[startIndex + i] = res[startIndex + i];
            }

            // In cazul in care sunt parintele ultimul worker, primesc vectorul pana la capat
            if (neigh[i] == (numProcs - 1) && (startIndex + workLoad != n)) {
                for(int i = startIndex + workLoad; i < n; i++) {
                    auxRes[i] = res[i];
                }
            }
        }

        // Trebuie sa trimit catre ceilalti coordonatori vectorul meu, incepand de la procesul 0
        // si sa primesc de la ei un vector pe care sa-l completez cu al meu
        // Trimit vectorul la coordonatorul din stanga mea, adica in sens trigonometric
        if (rank == 0) {
            MPI_Send(auxRes, n, MPI_INT, neigh[num_neigh - 1], 0, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, neigh[num_neigh - 1]);
            // din cauza erorilor de comunicare, procesul 0 va astepta raspuns de la 3, nu de la 1
            MPI_Recv(finalRes, n, MPI_INT, neigh[num_neigh - 1], 0, MPI_COMM_WORLD, &status);
        } else {
            MPI_Recv(finalRes, n, MPI_INT, neigh[num_neigh - 2], 0, MPI_COMM_WORLD, &status);
        }

        // Daca un element din vectorul primit este diferit de cel din vectorul meu curent
        // Dar nu este un element din vectorul original, atunci il inlocuiesc
        for (int i = 0; i < n; i++) {
            if (finalRes[i] != auxRes[i] && auxRes[i] != (n - i - 1)) {
                finalRes[i] = auxRes[i];
            }
        }

        if (rank != 0 && rank != 1) {
            MPI_Send(finalRes, n, MPI_INT, neigh[num_neigh - 1], 0, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, neigh[num_neigh - 1]);
        }

        // Dupa ce procesul 1 a terminat de introdus elemente in vector, acesta
        // trebuie sa trimita in sensul acelor de ceasornic prin topologie, ca vectorul
        // final sa ajunga inapoi la procesul 0
        if (rank == 1) {
            MPI_Send(finalRes, n, MPI_INT, neigh[num_neigh - 2], 0, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, neigh[num_neigh - 2]);
        } else if (rank != 0){
            MPI_Recv(finalRes, n, MPI_INT, neigh[num_neigh - 1], 0, MPI_COMM_WORLD, &status);
        }

        if (rank != 0 && rank != 1) {
            MPI_Send(finalRes, n, MPI_INT, neigh[num_neigh - 2], 0, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, neigh[num_neigh - 2]);
        }

        // In final, afisez tot vectorul, in procesul 0
        if (rank == 0) {
            
            printf("Rezultat: ");
            for (int i = 0; i < n; i++) {
                printf("%d ", finalRes[i]);
            }
            printf("\n");
        }
    }
}


int main(int argc, char * argv[]) {
	int rank, nProcesses, leader;
	int *parents, **topology;

    int n = atoi(argv[1]);
    int error = atoi(argv[2]);

	MPI_Init(&argc, &argv);
	MPI_Status status;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	
    if (rank < 4) {
	    read_neighbours(rank, error);
    } else {
        num_neigh = 1;
        neigh = malloc(sizeof(int) * num_neigh);
        MPI_Recv(&neigh[0], 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
    }

    if (rank < 4) {
        leader = rank;
    } else {
        leader = neigh[0];
    }

    MPI_Barrier(MPI_COMM_WORLD);

    parents = get_dst(rank, nProcesses, leader);

    // Afisaza topologia
    printf("%d -> ", rank);
    for (int i = 0; i < nProcesses; i++) {
        if (parents[i] == -1) {
            printf("%d:",i);
            char str[100];
            int len = 0;
            for (int j = 0; j < nProcesses; j++) {
                if (parents[j] == i) {
                    len += sprintf(str + len, "%d,", j);
                }
            }
            str[len - 1] = ' ';
            printf("%s", str);
        }
	}
    printf("\n");

	MPI_Barrier(MPI_COMM_WORLD);

    getArray(n, rank, nProcesses, leader);

    MPI_Finalize();
	return 0;
}