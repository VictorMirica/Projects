//Mirică Victor-Nicolae 324CB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LINE_SIZE 300

struct Dir;
struct File;

typedef struct Dir{
	char *name;
	struct Dir* parent;
	struct File* head_children_files;
	struct Dir* head_children_dirs;
	struct Dir* next;
} Dir;

typedef struct File {
	char *name;
	struct Dir* parent;
	struct File* next;
} File;
//Crearea unui fisier
void touch (Dir* parent, char* name) {
	File* lastFile = NULL;
	//Iteram prin fisierele directorului parinte pentru a ajunge la finalul listei
	//De asemenea testam daca exista deja acest fisier.
	for(File* file = parent->head_children_files; file != NULL; file=file->next){
		lastFile = file;
		if(strcmp(file->name, name) == 0){
			printf("File already exists\n");
			return;
		}
	}
	//Alocam memorie si initializam campurile fisierului
	File* file = (File*)malloc(sizeof(File));
	file->name = (char*)malloc(sizeof(name));
	strcpy(file->name, name);
	file->parent = parent;
	file->next = NULL;
	if(lastFile == NULL){
		parent->head_children_files = file;
	}else
		lastFile->next = file;
	return;
}

//Crearea unui director
void mkdir (Dir* parent, char* name) {
	Dir* lastDir = NULL;
	//In mod similar cu comanda touch, iteram prin lista de directoare
	for(Dir* dir = parent->head_children_dirs; dir != NULL; dir = dir->next){
		lastDir = dir;
		if(strcmp(dir->name, name) == 0){
			printf("Directory already exists\n");
			return;
		}
	}
	//Alocare + initializare
	Dir* dir = (Dir*)malloc(sizeof(Dir));
	dir->name = (char*)malloc(sizeof(name));
	strcpy(dir->name,name);
	dir->parent = parent;
	dir->next = NULL;
	dir->head_children_dirs = NULL;
	dir->head_children_files = NULL;
	if(lastDir == NULL){
		parent->head_children_dirs = dir;	
	}else
		lastDir->next = dir;
	return;
}

//Afisare
void ls (Dir* parent) {
	//Iteram prin ambele liste si afisam numele directoarelor, respectiv ale fisierelor
	for(Dir* dir = parent->head_children_dirs; dir != NULL; dir=dir->next){
		printf("%s\n", dir->name);
	}
	for(File* file = parent->head_children_files; file != NULL; file=file->next){
		printf("%s\n", file->name);
	}
}

//Stergerea unui fisier
void rm (Dir* parent, char* name) {
	File* lastFile = NULL;
	//Cautam fisierul, actualizam capetele listei si eliberam memoria
	for(File* file = parent->head_children_files; file != NULL; file=file->next){	
		if(strcmp(file->name, name) == 0){
			if(lastFile == NULL)
				parent->head_children_files = file->next;
			else
				lastFile->next = file->next;
			
			free(file->name);
			free(file);
			return;
		}
		lastFile = file;
	}
	printf("Could not find the file\n");
}

//Stergerea unui director
void rmdir (Dir* parent, char* name) {
	Dir* lastDir = NULL;
	//Similar cu stergerea fisierului, cu cativa pasi in plus la eliberarea memoriei
	for(Dir* dir = parent->head_children_dirs; dir != NULL; dir = dir->next){
		if(strcmp(dir->name, name) == 0){
			if(lastDir == NULL)
				parent->head_children_dirs = dir->next;
			else
				lastDir->next = dir->next;
			
			for(File* file = dir->head_children_files; file != NULL;){
				File* next = file->next;
				rm(dir,file->name);
				file = next;
			}
			for(Dir* dirChild = dir->head_children_dirs; dirChild != NULL;){
				Dir* next = dirChild->next;
				rmdir(dir,dirChild->name);
				dirChild = next;
			}

			free(dir->name);
			free(dir);
			return;
		}
		lastDir = dir;
	}
	printf("Could not find the dir\n");
}

//Schimbarea directorului de lucru
void cd(Dir** target, char *name) {
	//In cazul ".." trebuie sa ajungem in parintele directorului target
	if(strcmp(name, "..") == 0){
		if((*target)->parent != NULL)
			(*target) = (*target)->parent;
		return;
	}
	//Iteram lista de directoare si il alegem pe cel corespunzator
	for(Dir* dir = (*target)->head_children_dirs; dir!= NULL; dir=dir->next){
		if(strcmp(dir->name, name) == 0){
			(*target) = dir;
			return;
		}
	}
	printf("No directories found!\n");
	return;
}

//Afisarea path-ului pana la directorul curent
char *pwd (Dir* target) {
	char* path = malloc(MAX_INPUT_LINE_SIZE);
	char* tmp = malloc(MAX_INPUT_LINE_SIZE);
	strcpy(path,"");
	//Iteram prin parintii directoarelor pana ajungem la root 
	//Comanda sprintf ne va pune noul director (parintele), inaintea path-ului curent.
	for(Dir* dir = target; dir != NULL; dir = dir->parent){
		sprintf(tmp,"/%s%s",dir->name,path);
		strcpy(path,tmp);
	}
	free(tmp);
	return path;
}

//Oprim programul, eliberand toata memoria
void stop (Dir* target) {
	for(File* file = target->head_children_files; file != NULL;){
		File* next = file->next;
		rm(target,file->name);
		file = next;
	}
	for(Dir* dirChild = target->head_children_dirs; dirChild != NULL;){
		Dir* next = dirChild->next;
		rmdir(target,dirChild->name);
		dirChild = next;
	}

	free(target->name);
	free(target);
	return;
}

//Afisam fisierele si directoarele din target, ca pe un arbore
void tree (Dir* target, int level) {
	//In directoare, vom folosi recursiv functia tree()
	//De fiecare data cand apelam functia, incrementam argumentul level
	//pentru fecare "level", vom printa 4 caractere de indentare " "
	for(Dir* dir = target->head_children_dirs; dir != NULL; dir=dir->next){
		for(int i = 0; i < 4*level; i++){
			printf(" ");
		}
		printf("%s\n", dir->name);
		tree(dir,level+1);
	}
	for(File* file = target->head_children_files; file != NULL; file=file->next){
		for(int i = 0; i < 4*level; i++){
			printf(" ");
		}
		printf("%s\n", file->name);
	}
	return;
}

//Functie care schimba numele unui fisier/director
void mv(Dir* parent, char *oldname, char *newname) {
	File* lastFile = NULL;
	Dir* lastDir = NULL;

	//La inceput, testam daca numele nostru nou exista deja
	for(File* file = parent->head_children_files; file != NULL; file=file->next){	
		if(strcmp(file->name, newname) == 0){
			printf("File/Director already exists\n");
			return;
		}
	}
	for(Dir* dir = parent->head_children_dirs; dir != NULL; dir = dir->next){
		if(strcmp(dir->name, newname) == 0){
			printf("File/Director already exists\n");
			return;
		}
	}

	//Cautam, la inceput prin fisiere si apoi prin directoare, numele vechi
	//Dupa ce acesta a fost gasit, ii schimbam numele si il trecem la finalul listei respective
	for(File* file = parent->head_children_files; file != NULL; file=file->next){	
		if(strcmp(file->name, oldname) == 0){
			if(lastFile == NULL)
				parent->head_children_files = file->next;
			else
				lastFile->next = file->next;
			
			strcpy(file->name, newname);
			file->next = NULL;
			if(parent->head_children_files == NULL){
				parent->head_children_files = file;
				return;
			}
			for(File* file = parent->head_children_files; file != NULL; file=file->next){
				lastFile = file;
			}
			lastFile->next = file;
			return;
		}
		lastFile = file;
	}

	//Procedura dintre fisiere si directoare este foarte similara
	for(Dir* dir = parent->head_children_dirs; dir != NULL; dir = dir->next){
		if(strcmp(dir->name, oldname) == 0){
			if(lastDir == NULL)
				parent->head_children_dirs = dir->next;
			else
				lastDir->next = dir->next;
			
			strcpy(dir->name, newname);
			dir->next = NULL;
			if(parent->head_children_dirs == NULL){
				parent->head_children_dirs = dir;
				return;
			}
			for(Dir*  dir = parent->head_children_dirs; dir != NULL; dir=dir->next){
				lastDir = dir;
			}
			lastDir->next = dir;
			return;
		}
		lastDir = dir;
	}

	printf("File/Director not found\n");
	return;
}

int main () {
	int stops = 0;
	Dir* home = (Dir*)malloc(sizeof(Dir));
	home->name = malloc(5);
	strcpy(home->name, "home");
	home->parent = NULL;
	home->head_children_dirs = NULL;
	home->head_children_files = NULL;

	Dir* curr_dir = home;

	char* comanda = malloc(MAX_INPUT_LINE_SIZE);
	char* arg1 = malloc(MAX_INPUT_LINE_SIZE);
	char* arg2 = malloc(MAX_INPUT_LINE_SIZE);

	//flag-ul "stops" indica rularea programului
	//Initializam directorul root, numit si "home"
	//Alocam memorie pentru comanda si argumentele ce vor fi preluate din stdin.
	do
	{	
		scanf("%s",comanda);

		if(strcmp(comanda, "touch") == 0){ 
			scanf(" %s",arg1);
			touch(curr_dir, arg1);
		}

		if(strcmp(comanda, "mkdir") == 0){ 
			scanf(" %s",arg1);
			mkdir(curr_dir, arg1);
		}

		if(strcmp(comanda, "ls") == 0){
			ls(curr_dir);
		}

		if(strcmp(comanda, "rm") == 0){
			scanf(" %s",arg1);
			rm(curr_dir, arg1);
		}

		if(strcmp(comanda, "rmdir") == 0){
			scanf(" %s",arg1);
			rmdir(curr_dir, arg1);
		}

		if(strcmp(comanda, "cd") == 0){
			scanf(" %s",arg1);
			cd(&curr_dir,arg1);
		}

		if(strcmp(comanda,"tree") == 0){
			tree(curr_dir, 0);
		}

		if(strcmp(comanda,"pwd") == 0){
			char* a = pwd(curr_dir);
			printf("%s\n",a);
			free(a);
		}

		
		if(strcmp(comanda,"mv") == 0){
			scanf(" %s",arg1);
			scanf(" %s",arg2);
			mv(curr_dir,arg1,arg2);
		}

		if(strcmp(comanda, "stop") == 0){ 
			stops = 1;
			free(comanda);
			free(arg1);
			free(arg2);
			stop(home);
		}

	} while (stops != 1);
	
	return 0;
}
