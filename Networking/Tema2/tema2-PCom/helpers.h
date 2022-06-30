#ifndef _HELPERS_H
#define _HELPERS_H 1

#include <stdio.h>
#include <stdlib.h>

/*
 * Macro de verificare a erorilor
 * Exemplu:
 *     int fd = open(file_name, O_RDONLY);
 *     DIE(fd == -1, "open failed");
 */

#define DIE(assertion, call_description)	\
	do {									\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ",	\
					__FILE__, __LINE__);	\
			perror(call_description);		\
			exit(EXIT_FAILURE);				\
		}									\
	} while(0)

#define BUFSIZE 1600


struct topic { // Un topic, folosit in structura client
	char topic[50];
	int sf;
};

struct msg { // Un tip de mesaj primit de la UDP, header ca in enunt
	char topic[50]; 
	uint8_t tip_date;
	char continut[1500];
};

struct toSend { // Un mesaj ce trebuie trimis unui TCP
	struct in_addr ip; 
	uint16_t port;
	struct msg msg;
};

// 3 tipuri :
// disconnect - 0
// subscribe - 1
// unsubscribe  - 2
struct flux { // O comanda, trimisa de un client TCP
	int type;
	struct topic topic;
};

typedef struct cell{
	void* info;
	struct cell* urm;
} TCelula, *TList;

struct clientTcp { // Un client 
	int online; // bool
	char id[11];
	int sock;
	TList topicList;
	TList sfList;
};

#endif
