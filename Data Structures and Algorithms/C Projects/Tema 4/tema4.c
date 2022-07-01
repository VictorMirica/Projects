#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void* (* Abilities[4])(void* x) = {RotateMatrix, DecodeString, InvertArray, KillPlayer};

char *fromEnumtoString(PlayerRoles playerRole)
{
	char *str = calloc(MAX_LEN_STR_ATR, sizeof(char));
	switch(playerRole)
	{
		case Rotator:
			str = strcpy(str, "Rotator");
			break;
		case Decoder:
			str = strcpy(str, "Decoder");
			break;
		case Invertor:
			str = strcpy(str, "Invertor");
			break;
		case Impostor:
			str = strcpy(str, "Impostor");
			break;
	}
	return str;
}

// Task 1
void *RotateMatrix(void *input)
{	
	int n = *(int*)input;
	int mat[n][n];
	for(int i = 0; i<n; i++){
		int nr_zero = 1;
		int copy_i = (i+1)/10;
		while(copy_i != 0){
			nr_zero++;
			copy_i/=10;
		}
		int m = n;
		for(int j = 0; j<n; j++){
			mat[i][j] = ((m * pow(10, nr_zero)) + i + 1);
			m--;
		}
	}

	char* output = malloc(MAX_LEN_STR_OUT);
	int k = 0;
	char num[10];
	for (int i = 0; i<n; i++){
		for (int j = 0; j<n; j++){
			sprintf(num, "%d", mat[i][j]);
			int p = 0;
			int number = mat[i][j];
			while(number != 0){
				output[k] = num[p];
				k++;
				p++;
				number/=10;
			}
			if(j != n-1){
				output[k] = ' ';
				k++;
			}
		}
		if(i != n-1){
			output[k] = '\n';
			k++;
		}
	}

	return (void*)output;
}

// Task 2
void *DecodeString(void *input)
{
	char* sir = (char*)input;
	int sum = 0;
	int param = 0;
	for(int i = 0; i <= (int)strlen(sir); i++){
		if(sir[i] == '_'){
			sum += atoi(sir + param);
			param = i + 1;
		}
		if(sir[i] == '\0'){
			sum += atoi(sir + param);
		}
	}
	char* output = malloc(sizeof(int));
	sprintf(output, "%d", sum);

	return (void*)output;
}

//Task 3
void *InvertArray(void *input)
{
	int* vect = (int*)input;
	int* sorted = malloc(MAX_LEN_STR_OUT);
	char* output = malloc(MAX_LEN_STR_OUT);
	char* outputReal = malloc(MAX_LEN_STR_OUT);
	if (*vect % 2 == 0){
		int i = 1;
		int j = 2;
		int k = 0;
		while(j <= vect[0]){
			sorted[k] = vect[j];
			sorted[k+1] = vect[i];
			k+=2;
			i+=2;
			j+=2;
		}
	}

	if (*vect % 2 != 0){
		int i = vect[0];
		int j = 0;
		while(i > 0){
			sorted[j] = vect[i];
			j++;
			i--;
		}
	}

	for (int i = 0; i < vect[0]; i++){
		sprintf(output, "%d", sorted[i]);
		strncat(outputReal, output, 6);
		strncat(outputReal, " " , 2);
	}

	
	
	return (void*)outputReal;
}

//Task 4
Player *allocPlayer()
{
	Player* player = malloc(sizeof(Player));
	player->alive = 1;
	player->name = (char*)malloc(MAX_LEN_STR_ATR);
	player->color = (char*)malloc(MAX_LEN_STR_ATR);
	player->hat = (char*)malloc(MAX_LEN_STR_ATR);
	return player;

}

//Task 4
Game *allocGame()
{
	Game* game = malloc(sizeof(Game));
	game->name = (char*)malloc(MAX_LEN_STR_ATR);
	return game;
}

//Task 5
Player *ReadPlayer(FILE *inputFile)
{	
	char* trash = malloc(50 * sizeof(char));
	int trashInt;
	Player* player = allocPlayer();
	fgets(player->name, MAX_LEN_STR_ATR, inputFile);
	player->name[strlen(player->name)-1] = '\0';
	fgets(player->color, MAX_LEN_STR_ATR, inputFile);
	player->color[strlen(player->color)-1] = '\0';
	fgets(player->hat, MAX_LEN_STR_ATR, inputFile);
	player->hat[strlen(player->hat)-1] = '\0';

	fscanf(inputFile, "%d", &(player->numberOfLocations));
	fscanf(inputFile, "%d", &(player->numberOfLocations));
	player->locations = malloc(player->numberOfLocations * sizeof(Location));
	for(int i = 0; i < (player->numberOfLocations); i++){
		fscanf(inputFile, "%c%d%c%d%c%c", trash, &(player->locations[i].x) , trash, &(player->locations[i].y), trash, trash);
	}
	fscanf(inputFile, "%d", &trashInt);
	char *str = malloc(MAX_LEN_STR_ATR);
	fgets(str, MAX_LEN_STR_ATR, inputFile);

	if(str[1] == 'e'){
		player->playerRole = 1;
	}
	if(str[1] == 'o'){
		player->playerRole = 0;
	}
	if(str[1] == 'n'){
		player->playerRole = 2;
	}
	if(str[1] == 'm'){
		player->playerRole = 3;
	}

	switch(player->playerRole)
	{
		case Rotator:
			player->ability = Abilities[0];
			break;
		case Decoder:
			player->ability = Abilities[1];
			break;
		case Invertor:
			player->ability = Abilities[2];
			break;
		case Impostor:
			player->ability = Abilities[3];
			break;
	}

	
	return player;
}

// Task 5
Game *ReadGame(FILE *inputFile)
{	
	Game* game = allocGame();
	fgets(game->name, MAX_LEN_STR_ATR, inputFile);
	game->name[strlen(game->name)-1] = '\0';
	fscanf(inputFile, "%d", &(game->killRange));
	fscanf(inputFile, "%d", &(game->numberOfCrewmates));
	fscanf(inputFile, "%d", &(game->numberOfCrewmates));

	game->crewmates = malloc(game->numberOfCrewmates * sizeof(Player));
	for(int i = 0; i < game->numberOfCrewmates; i++){
		Player* player = ReadPlayer(inputFile);
		*((game->crewmates) + i) = player;	
	}

	Player* player = ReadPlayer(inputFile);
	game->impostor = player;


	return game;
}

// Task 6
void WritePlayer(Player *player, FILE *outputFile)
{	
	char* str = malloc(MAX_LEN_STR_ATR);
	str = strcpy(str, "Player ");
	if(((player->name)[strlen(player->name) - 1] > 122) | ((player->name)[strlen(player->name) - 1] < 97)){
		(player->name)[strlen(player->name) - 1] = '\0';
	}
	str = strcat(str, player->name);
	str = strcat(str, " with color ");
	if(((player->color)[strlen(player->color) - 1] > 122) | ((player->color)[strlen(player->color) - 1] < 97)){
		(player->color)[strlen(player->color) - 1] = '\0';
	}
	str = strcat(str, player->color);
	str = strcat(str, ", hat ");
	if(((player->hat)[strlen(player->hat) - 1] > 122) | ((player->hat)[strlen(player->hat) - 1] < 97)){
		(player->hat)[strlen(player->hat) - 1] = '\0';
	}
	str = strcat(str, player->hat);
	str = strcat(str, " and role ");
	str = strcat(str, fromEnumtoString(player->playerRole));
	str = strcat(str, " has entered the game.\n");
	fputs(str, outputFile);
	str = strcpy(str, "Player's locations:");
	for(int i = 0; i < player->numberOfLocations; i++){
		char* x = malloc(20 * sizeof(char));
		sprintf(x, "%d", player->locations[i].x);
		char* y = malloc(20 * sizeof(char));
		sprintf(y, "%d", player->locations[i].y);
		str = strcat(str, " ");
		str = strcat(str, "(");
		str = strcat(str, x);
		str = strcat(str, ",");
		str = strcat(str, y);
		str = strcat(str, ")");


	}
	fputs(str, outputFile);


	return;
}

// Task 6
void WriteGame(Game *game, FILE *outputFile)
{
	char* str = malloc(MAX_LEN_STR_ATR);
	str = strcpy(str, "Game ");
	if(((game->name)[strlen(game->name) - 1] > 122) | ((game->name)[strlen(game->name) - 1] < 97)){
		(game->name)[strlen(game->name) - 1] = '\0';
	}
	str = strcat(str, game->name);
	str = strcat(str, " has just started!\n");
	fputs(str, outputFile);
	fputs("\tGame options:\n", outputFile);
	str = strcpy(str, "Kill Range: ");
	char* killR = malloc(20 * sizeof(char));
	sprintf(killR, "%d", game->killRange);
	str = strcat(str, killR);
	str = strcat(str, "\n");
	fputs(str, outputFile);
	str = strcpy(str, "Number of crewmates: ");
	char* nrMates = malloc(20 * sizeof(char));
	sprintf(nrMates, "%d", game->numberOfCrewmates);
	str = strcat(str, nrMates);
	str = strcat(str, "\n");
	fputs(str, outputFile);
	fputs("\n", outputFile);
	fputs("\tCrewmates:\n", outputFile);
	for(int i = 0; i < game->numberOfCrewmates; i++){
		WritePlayer(*((game->crewmates) + i), outputFile);
		fputs("\n", outputFile);
	}
	fputs("\n", outputFile);
	fputs("\tImpostor:\n", outputFile);
	WritePlayer(game->impostor, outputFile);

	return;
}

//Task 7
void *KillPlayer(void *input)
{
	Game* game = (Game*)input;
	char* str = malloc(MAX_LEN_STR_ATR);
	str = strcpy(str, "Impostor ");
	if(((game->impostor->name)[strlen(game->impostor->name) - 1] > 122) | ((game->impostor->name)[strlen(game->impostor->name) - 1] < 97)){
		(game->impostor->name)[strlen(game->impostor->name) - 1] = '\0';
	}
	str = strcat(str, game->impostor->name);

	int killIndex = -1;	
	int minDist = game->killRange;
	int impX = game->impostor->locations[game->impostor->indexOfLocation].x;
	int impY = game->impostor->locations[game->impostor->indexOfLocation].y;
	for(int i = 0; i < game->numberOfCrewmates; i++){
		int crewX = game->crewmates[i]->locations[game->crewmates[i]->indexOfLocation].x;
		int crewY = game->crewmates[i]->locations[game->crewmates[i]->indexOfLocation].y;
		int distanta = abs(impX - crewX) + abs(impY - crewY);
		if((distanta <= minDist) & (game->crewmates[i]->alive == 1)){
			killIndex = i;
			minDist = distanta;
		}
	}

	if(killIndex == -1){
		str = strcat(str, " couldn't kill anybody.");
	}else{
		game->crewmates[killIndex]->alive = 0;
		str = strcat(str, " has just killed crewmate ");
		if(((game->crewmates[killIndex]->name)[strlen(game->crewmates[killIndex]->name) - 1] > 122) | ((game->crewmates[killIndex]->name)[strlen(game->crewmates[killIndex]->name) - 1] < 65)){
			(game->crewmates[killIndex]->name)[strlen(game->crewmates[killIndex]->name) - 1] = '\0';
		}
		str = strcat(str, game->crewmates[killIndex]->name);
		str = strcat(str, " from distance ");
		char* distance = malloc(MAX_LEN_STR_ATR);
		sprintf(distance, "%d", minDist);
		str = strcat(str, distance);
		str = strcat(str, ".");
	}
	
	return (void*)str;
}

// Task 8
void CalcuateNextCycleOfGame(Game *game, FILE *outputFile, void **inputMatrix)
{
	for(int i = 0; i < game->numberOfCrewmates; i++){
		char* str = malloc(MAX_LEN_STR_ATR);
		str = strcpy(str, "Crewmate ");
		if(((game->crewmates[i]->name)[strlen(game->crewmates[i]->name) - 1] > 122) | ((game->crewmates[i]->name)[strlen(game->crewmates[i]->name) - 1] < 65)){
			(game->crewmates[i]->name)[strlen(game->crewmates[i]->name) - 1] = '\0';
		}
		str = strcat(str, game->crewmates[i]->name);
		if(game->crewmates[i]->alive == 0){
			str = strcat(str, " is dead.\n");
			fputs(str, outputFile);
			continue;
		}

		int locX, locY;
		if(game->crewmates[i]->indexOfLocation == (game->crewmates[i]->numberOfLocations)-1){
			locX = game->crewmates[i]->locations[0].x;
			locY = game->crewmates[i]->locations[0].y;
			game->crewmates[i]->indexOfLocation = 0;
		}else{
			locX = game->crewmates[i]->locations[game->crewmates[i]->indexOfLocation + 1].x;
			locY = game->crewmates[i]->locations[game->crewmates[i]->indexOfLocation + 1].y;
			game->crewmates[i]->indexOfLocation++;
		}
		str = strcat(str, " went to location (");
		char* strX = malloc(MAX_LEN_STR_ATR);
		char* strY = malloc(MAX_LEN_STR_ATR);
		sprintf(strX, "%d", locX);
		sprintf(strY, "%d", locY);
		str = strcat(str, strX);
		str = strcat(str, ",");
		str = strcat(str, strY);
		str = strcat(str, ").\n");
		fputs(str, outputFile);

		str = strcpy(str, "Crewmate ");
		str = strcat(str, game->crewmates[i]->name);
		str = strcat(str, "'s output:\n");
		fputs(str, outputFile);

		fputs(game->crewmates[i]->ability(inputMatrix[i]) , outputFile);
		fputs("\n", outputFile);

	}

	char* str = malloc(MAX_LEN_STR_ATR);
	str = strcpy(str, "Impostor ");
	if(((game->impostor->name)[strlen(game->impostor->name) - 1] > 122) | ((game->impostor->name)[strlen(game->impostor->name) - 1] < 97)){
		(game->impostor->name)[strlen(game->impostor->name) - 1] = '\0';
	}
	str = strcat(str, game->impostor->name);

	int locX, locY;
	if(game->impostor->indexOfLocation == (game->impostor->numberOfLocations)-1){
		locX = game->impostor->locations[0].x;
		locY = game->impostor->locations[0].y;
		game->impostor->indexOfLocation = 0;
	}else{
		locX = game->impostor->locations[game->impostor->indexOfLocation + 1].x;
		locY = game->impostor->locations[game->impostor->indexOfLocation + 1].y;
		game->impostor->indexOfLocation++;
	}
	str = strcat(str, " went to location (");
	char* strX = malloc(MAX_LEN_STR_ATR);
	char* strY = malloc(MAX_LEN_STR_ATR);
	sprintf(strX, "%d", locX);
	sprintf(strY, "%d", locY);
	str = strcat(str, strX);
	str = strcat(str, ",");
	str = strcat(str, strY);
	str = strcat(str, ").\n");
	fputs(str, outputFile);

	str = strcpy(str, "Impostor ");
	str = strcat(str, game->impostor->name);
	str = strcat(str, "'s output:\n");
	fputs(str, outputFile);

	fputs(game->impostor->ability(inputMatrix[game->numberOfCrewmates]), outputFile);
	fputs("\n", outputFile);


	return;
}

// Task 9
void FreePlayer(Player *player)
{	

	free(player->name);
	free(player->color);
	free(player->hat);
	free(player->locations);
	free(player);
	return;
}

// Task 9
void FreeGame(Game *game)
{	
	free(game->name);
	FreePlayer(game->impostor);
	for(int i = 0; i < game->numberOfCrewmates; i++){
		FreePlayer(game->crewmates[i]);
	}
	free(game->crewmates);
	free(game);
	return;
}