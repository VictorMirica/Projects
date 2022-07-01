/*MIRICA Victor - 315CB*/
#include "tarb.h"
//Structura carte
typedef struct carte
{	
	char titlu[50];
	char autor[40];
	int rating;
  int nrPg;
} TCarte;
//Functii  pentru eliberare: Carte, Arbore 
int freeCarte(void* a){
  if (!a){
    return 0;
  }
  TCarte* carte = (TCarte*)a;
  free(carte);
  return 1;
}
//functie pentru eliberarea arborelui T, folosita dupa ce a fost eliberat arborele T1
//(Nu mai avem nevoie sa eliberam "Cartea")
int freeT2(void* a){
  if (!a){
    return 0;
  }

  return 1;
}

int freeArb(void* a){
  if(!a){
    return 0;
  }
  TArb arb = (TArb)a;
  DistrArb(&arb, freeT2);
  return 1;
}
//Functia adauga o carte, citind fisierul in
TCarte* addBook(FILE* in){
  TCarte* carte = malloc(sizeof(TCarte)); 
  fscanf(in, " %[^:]:%[^:]:", carte->titlu, carte->autor);
  fscanf(in, "%d:%d", &(carte->rating), &(carte->nrPg));
  return carte;
}
//Functie de auto-complete. Foloseste functie autoComplete
//Specifica structurii carte, functia functioneaza pentru 3 carti
void autoCompleteCarte(char* titlu, TArb arb, FILE* out){
  int nuExista = 1;
  for(int i = 0; i < 3; i++){ //Scriem in fisier primele 3 carti
    TCarte* carte = autoComplete(arb, titlu, i); //Apelam functia de autocomplete
    if(carte){
      nuExista = 0;
      fprintf(out,"%s\n",carte->titlu);
    }
  }
  if(nuExista){ //In cazul in care nu am gasit nicio carte dupa cele 3 incercari, printam mesajul:
    fprintf(out,"Nicio carte gasita.\n");
  }
}
//Functie similara cu cea de auto-complete pentru carte
void autoCompleteAutor(char* autor, TArb arb, FILE* out){
  int nuExista = 1;
  int which = 0;
  for(int i = 0; i < 3; i++){ //Scriem in fisier 3 autori
    TArb T = autoComplete(arb, autor, i);
    if(T){
      nuExista = 0;
      which = 0;
      TCarte* carte = lexicografic(T, &which);//Nu pastram nicaieri intregul string care reprezinta numele autorului
      fprintf(out,"%s\n", carte->autor);  //Asadar Intoarcem prima valoare din arborele respectiv lui, din care extragem numele
    }
  }
  if(nuExista){ //In caz ca nu exista:
    fprintf(out,"Niciun autor gasit.\n");
  }
}
//Scriem titlul cartii primite (a), in fisier
int printCarte(void* a, FILE* out){
  if(!a){
    return 0;
  }
  TCarte* carte = (TCarte*)a;
  fprintf(out, "%s\n", carte->titlu);
  return 1;
}

int main( int argc, char *argv[] ){
  //Testare pentru a rula functia corect din linia de comanda + deschidere fisiere
  if(argc != 3){
      printf("Programul a fost rulat incorect din linia de comanda\n");
      return 0;
  }
  FILE *in, *out;
  in = fopen(argv[1], "rt");
  out = fopen(argv[2], "wt");
  if (in == NULL)
  return 0;
  if (out == NULL)
  return 0;
  //Construim cei doi arbori trie
  TArb T1 = ConstrNod();
  TArb T2 = ConstrNod();
  //Citim fisierul pana la final
  while (!feof(in)){      
    char comanda[50]={};
    fscanf(in, "%s ", comanda);
    //Citim primul cuvant de pe linie, "comanda"
    if(strcmp(comanda,"add_book") == 0){
      //Adaugam o carte
      TCarte* carte = addBook(in);
      if(findString(T1, carte->titlu)){//Ne asiguram ca aceasta nu se afla deja in arb
        free(carte);
        continue;
      }
      Insert(T1,carte->titlu,carte);//Introducem cartea in T1

      TArb T = findString(T2, carte->autor);//Ne asiguram ca autorul cartii nu exista deja
      if(!T){
        T = ConstrNod(); //Creem un nou trie, in caz ca nu exista autorul
        Insert(T,carte->titlu,carte);
        Insert(T2,carte->autor,T);
      }else{
        Insert(T,carte->titlu,carte);//In cazul de existenta, introducem cartea in trie
      }
    }
    //Cautam o carte dupa titlu
    if(strcmp(comanda,"search_book") == 0){
      char titlu[50];
      fscanf(in, " %[^\n\r]\n\r", titlu);
      if(titlu[strlen(titlu)-1] == '~'){    //intru in autocomplete
        titlu[strlen(titlu)-1] = '\0';
        autoCompleteCarte(titlu, T1, out);
        continue;
      }
      //Cauta cartea in T1
      TCarte* carte = findString(T1, titlu);
      if(carte){
        fprintf(out,"Informatii recomandare: %s, %s, %d, %d\n", carte->titlu, carte->autor, carte->rating, carte->nrPg);
      }else{
        fprintf(out,"Cartea %s nu exista in recomandarile tale.\n", titlu);
      }
    }
    //Caut un autor dupa nume
    if(strcmp(comanda,"list_author") == 0){
      char autor[40];
      fscanf(in, " %[^\n\r]\n\r", autor);
      if(autor[strlen(autor)-1] == '~'){    //intru in autocomplete
        autor[strlen(autor)-1] = '\0';
        autoCompleteAutor(autor, T2, out);
        continue;
      }
      //Cauta autorul in T2
      TArb T = findString(T2, autor);
      if(!T){
        fprintf(out,"Autorul %s nu face parte din recomandarile tale.\n", autor);
        continue;
      }
      printArb(T,printCarte,out);
    }
    //Caut cartile unui autor
    if(strcmp(comanda,"search_by_author") == 0){
      char titlu[50];
      char autor[40];
      fscanf(in, " %[^:\n\r]:\n\r", autor);        
      if(autor[strlen(autor)-1] == '~'){    //intru in autocomplete autor
        autor[strlen(autor)-1] = '\0';
        autoCompleteAutor(autor, T2, out);
        continue;
      }
      //Caut autorul in T2
      TArb T = findString(T2, autor);
      if(!T){
        fprintf(out,"Autorul %s nu face parte din recomandarile tale.\n", autor);
        continue;
      }
      fscanf(in, "%[^\n\r]\n\r", titlu);
      if(titlu[strlen(titlu)-1] == '~'){    //intru in autocomplete titlu
        titlu[strlen(titlu)-1] = '\0';
        autoCompleteCarte(titlu, T, out);
        continue;
      }
      //Caut cartea in trie-ul respectiv al autorului
      TCarte* carte = findString(T, titlu);
      if(carte){
        fprintf(out,"Informatii recomandare: %s, %s, %d, %d\n", carte->titlu, carte->autor, carte->rating, carte->nrPg);
      }else{
        fprintf(out,"Cartea %s nu exista in recomandarile tale.\n", titlu);
      }
    }
    //Sterg o carte din memorie
    if(strcmp(comanda,"delete_book") == 0){
      char titlu[50];
      fscanf(in, " %[^\n\r]\n\r", titlu);
      //Caut cartea in T1
      TCarte* carte = findString(T1, titlu);
      if(!carte){
        fprintf(out,"Cartea %s nu exista in recomandarile tale.\n", titlu);
        continue;
      }
      //Pastrez numele autorul pentru a-l folosi la o ulterioara sterge, dupa ce Am eliberat deja cartea
      char* autor = malloc(sizeof(carte->autor));
      memcpy(autor,carte->autor,sizeof(carte->autor));
      //Caut autorul in T2
      TArb T = findString(T2, autor);
      //Sterg cartea din T1
      elimString(&T1,titlu,freeCarte);
      if(!T1){
        //Reconstruiesc T1, in caz ca este gol, pentru eventuale introduceri
        T1 = ConstrNod();
      }
      //Sterg Cartea din Trie-ul autorului
      elimString(&T,titlu,freeT2);
      if(!T){
        //Daca autorul nu mai are alte carti, il sterg din T2
        elimString(&T2,autor,freeT2);
        if(!T2){
          //Reconstruiesc T2, in caz ca este gol, pentru eventuale introduceri
          T2 = ConstrNod();
        }
      }
      //Eliberez numele autorului alocat mai sus (ln 199)
      free(autor);
    }
  }
  //Inchid fisierele si distrug arborii.
  fclose(in);
  fclose(out);
  DistrArb(&T1, freeCarte);
  DistrArb(&T2, freeArb);
}