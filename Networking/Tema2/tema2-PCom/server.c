#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <math.h>
#include "helpers.h"

#define MAX_CLIENTS_NO 1000

// Functiile listei
int insList(TList* l, void* e) {
	TList aux = malloc(sizeof(TCelula));
	aux->info = e;

	if(*l == NULL) {
		aux->urm = *l;
		*l = aux;
		return 1;
	}
	
	aux->urm = NULL;
	TList p = *l;
	for(;p->urm != NULL; p = p->urm){}
	p->urm = aux;
	return 1;
}

int removeList(TList* l, int index){
	int i = 0;
	TList last = NULL;
	TList p = *l;

	if (index == 0) {
		*l = p->urm;
		return 1;
	}

	for(;p->urm != NULL; p = p->urm){
		if (index == i) {
			last->urm = p->urm;
		}
	}

	return 1;
}

void usage(char *file)
{
	fprintf(stderr, "Usage: %s server_port\n", file);
	exit(0);
}

void setClient(struct clientTcp* client, char* buffer, int sock) {
	strcpy(client->id, buffer);
	client->sock = sock;
	client->online = 1;
}


int main(int argc, char *argv[])
{
	char buffer[BUFSIZE];
	
	socklen_t sockLen = sizeof(struct sockaddr);
	struct clientTcp* clients = malloc(MAX_CLIENTS_NO * sizeof(struct clientTcp));

	
	if (argc < 2) {
		usage(argv[0]);
	}

	setvbuf(stdout, NULL, _IONBF, BUFSIZ);
	
	fd_set read_fds; // multimea de citire folosita in select()
	fd_set tmp_fds;	// multime folosita temporar

	// se goleste multimea de descriptori de citire (read_fds) si multimea temporara (tmp_fds)
	FD_ZERO(&read_fds);
	FD_ZERO(&tmp_fds);

	// Deschid socket tcp
	int tcpSock = socket(AF_INET, SOCK_STREAM, 0);
	DIE(tcpSock < 0, "tcp socket");

	int port = atoi(argv[1]);
	DIE(port == 0, "proto atoi");

	struct sockaddr_in tcpAddr;
	tcpAddr.sin_family = AF_INET;
	tcpAddr.sin_port = htons(port);
	tcpAddr.sin_addr.s_addr = INADDR_ANY;

	// Incerc sa refolosesc un port ocupat
	int occupied = 1;
	int ret = setsockopt(tcpSock, SOL_SOCKET, SO_REUSEADDR, &occupied, sizeof(int));
	DIE(ret < 0, "Reusing port");

	// Dezactivam algoritmul Nagle
	int nagle = 1; 
	ret = setsockopt(tcpSock, IPPROTO_TCP, TCP_NODELAY, &nagle, sizeof(int));
	DIE(ret < 0, "Nagle algorithm");

	// bind socket tcp
	ret = bind(tcpSock, (struct sockaddr *) &tcpAddr, sizeof(struct sockaddr));
	DIE(ret < 0, "bind tcp");

	// Deschid socket udp
	int udpSock = socket(AF_INET, SOCK_DGRAM, 0);
	DIE(udpSock < 0, "udp socket");

	struct sockaddr_in udpAddr;
	udpAddr.sin_family = AF_INET;
	udpAddr.sin_port = htons(port);
	udpAddr.sin_addr.s_addr = INADDR_ANY;

	// bind socket udp
	ret = bind(udpSock, (struct sockaddr *) &udpAddr, sizeof(struct sockaddr));
	DIE(ret < 0, "bind udp");

	// Socket tcp asculta dupa conexiunile clientilor
	ret = listen(tcpSock, INT32_MAX);
	DIE(ret < 0, "listen tcp");

	
	// se adauga socket UDP, socket TCP si stdin in multimea read_fds
	FD_SET(udpSock, &read_fds);
	FD_SET(tcpSock, &read_fds);
	FD_SET(STDIN_FILENO, &read_fds);

	// Se decide fdmax dintre udp si tcp
	int fdmax = udpSock > tcpSock ? udpSock : tcpSock;

	while (1) {
		tmp_fds = read_fds; 
		
		ret = select(fdmax + 1, &tmp_fds, NULL, NULL, NULL);
		DIE(ret < 0, "select");

		// reset buff
		memset(buffer, 0, BUFSIZE);

		for (int i = 0; i <= fdmax; i++) {
			if (FD_ISSET(i, &tmp_fds)) {
				if (i == STDIN_FILENO) {
					// Citim de la stdin
					fgets(buffer, BUFSIZE-1, stdin);

					if(strncmp(buffer, "exit", 4) == 0) {

						// Inchidem socket-urile tuturor clientilor conectati
						for (int i = 0; i < fdmax; i++) { 
							if (FD_ISSET(i, &read_fds)) {
								close(i);
								FD_CLR(i, &read_fds);
							}
						}
						close(udpSock);
						close(tcpSock);
						return 0;
						// Iesim din loop
					}

					DIE(strncmp(buffer, "exit", 4) != 0, "stdin exit"); 
				} else if (i == tcpSock) { 
					// S-a primit o conexiune de la un client TCP 
					// a venit o cerere de conexiune pe socketul inactiv (TCP),
					// pe care serverul o accepta

					int newsockfd = accept(tcpSock, (struct sockaddr *) &tcpAddr, &sockLen);
					DIE(newsockfd < 0, "accept tcp");

					ret = recv(newsockfd, buffer, 10, 0);
					DIE(ret < 0, "recv tcp");

					// Cautam clientul 
					int found = -1;
					int online;
	
					for (int j = 0; j <= fdmax; j++) {
								
						if (strcmp(clients[j].id, buffer) == 0) {
							found = j;
							online = clients[j].online;
							break;
						}
					}		
		
					if (found == -1) {
						
						// client nou
						// se adauga noul socket intors de accept() la multimea descriptorilor de citire
						FD_SET(newsockfd, &read_fds);
						if (newsockfd > fdmax) { 
							fdmax = newsockfd;
						}

						setClient(&clients[fdmax], buffer, newsockfd);

						printf("New client %s connected from %s:%d\n",
								clients[fdmax].id, inet_ntoa(tcpAddr.sin_addr), ntohs(tcpAddr.sin_port));

					} else if (found && !online) {
						// S-a reconectat un client mai vechi, trebuie trimise toate mesajele (sf).
						FD_SET(newsockfd, &read_fds);
						setClient(&clients[found], clients[found].id, newsockfd);

						printf("New client %s connected from %s:%d\n",
								clients[found].id, inet_ntoa(tcpAddr.sin_addr), ntohs(tcpAddr.sin_port));

						// Trimit toate mesajele din store											
						TList p = clients[found].sfList;
						
						for(; p != NULL; p = p->urm){
							ret = send(clients[found].sock, p->info, sizeof(struct toSend), 0);
							DIE(ret < 0, "send tcp sf");
						}

						// Am trimis toate mesajele din store	
						clients[found].sfList = NULL;
						clients[found].online = 1;
						
					
					} else {
						// A incercat sa se conecteze un client cu un ID care este deja online
						printf("Client %s already connected.\n", clients[found].id);
						close(newsockfd);
						FD_CLR(newsockfd, &read_fds);
					
					}

				} else if (i == udpSock) {
					// Am primit o conexiune de la un client UDP
					// Va trebui sa trimit mesaje subscriberilor TCP
					ret = recvfrom(udpSock, buffer, sizeof(buffer), 0, (struct sockaddr *)&udpAddr, &sockLen);
					DIE(ret < 0, "recvfrom udp");

					struct toSend* toSend = malloc(sizeof (struct toSend));
					toSend->port = htons(udpAddr.sin_port);
					toSend->ip = udpAddr.sin_addr;
					
					struct msg* msg = (struct msg *)buffer;

					strcpy(toSend->msg.topic, msg->topic); 
					
					// Vedem ce tip de date trebuie sa trimitem. 
					if (msg->tip_date == 0) { // INT
						char semn; // Pentru octetul de semn
						memcpy(&semn, msg->continut, sizeof(char));
						uint32_t continut;
						memcpy(&continut, msg->continut + 1, sizeof(uint32_t));

						continut = ntohl(continut);
						if (semn == 1) {
							continut = -continut;
						}

						sprintf(toSend->msg.continut, "%d", continut);
						toSend->msg.tip_date = 0;
					}

					if (msg->tip_date == 1) { // SHORT_REAL
						uint16_t continut;
						memcpy(&continut, msg->continut, sizeof(uint16_t));

						continut = abs(ntohs(continut));
						double continutDouble = (double) continut;
						continutDouble /= (double)100;

						sprintf(toSend->msg.continut, "%.2f", continutDouble);
						toSend->msg.tip_date = 1;
					}

					if (msg->tip_date == 2) { // FLOAT
						char semn;
						memcpy(&semn, msg->continut, sizeof(char));
						uint32_t continut;
						memcpy(&continut, msg->continut + 1, sizeof(uint32_t));
						continut = ntohl(continut);
						uint8_t putere;
						memcpy(&putere, msg->continut + 1 + sizeof(uint32_t), sizeof(uint8_t));

						double continutDouble = (double) continut;

						while(putere != 0) {
							continutDouble /= 10;
							putere--;
						}

						if (semn == 1) {
							continutDouble = -continutDouble;
						}

						sprintf(toSend->msg.continut, "%f", continutDouble);
						toSend->msg.tip_date = 2;
					}

					if (msg->tip_date == 3) { // STRING	
						strcpy(toSend->msg.continut, msg->continut);
						toSend->msg.tip_date = 3;
					}

					// Am format mesajul ce trebuie trimis
					// Acum trimitem mesajul clientilor TCP
					// Pentru fiecare client, iteram prin topicele lui
					for (int j = 0; j <= fdmax; j++) {
						
						TList p = clients[j].topicList;
						
						for(; p != NULL; p = p->urm){
							if (strcmp(((struct topic*)p->info)->topic, toSend->msg.topic) == 0) {
								// Am gasit un topic comun, verificam daca clientul este online	
								if(clients[j].online) {
									ret = send(clients[j].sock, toSend, sizeof(struct toSend), 0);
									DIE(ret < 0, "send tcp online");
								} else {
									if (((struct topic*)p->info)->sf == 1) {
										insList(&(clients[j].sfList), toSend);
									}
								}
								break;
							}
						}
						
					}
				} else {
					// Primim un datastream de la un client TCP
					ret = recv(i, buffer, BUFSIZE, 0);
					DIE(ret < 0, "recv datastream tcp");

					struct flux* flux = (struct flux*) buffer;

					// Identificam clientul care a trimis comanda
					int index;
					for (int j = 0; j <= fdmax; j ++) {
						if (i == clients[j].sock) {
							index = j;
							break;
						}
					}

					if (flux->type == 0) { // Disconnect

						printf("Client %s disconnected.\n", clients[index].id);
						clients[index].online = 0;
						close(i); 
						FD_CLR(i, &read_fds);
					} else if (flux->type == 1) { // Subscribe

						// Verificam daca userul este deja abonat
						int flag = 1;
						TList p = clients[index].topicList;
						
						for(; p != NULL; p = p->urm){
							if (strcmp(((struct topic*)p->info)->topic, flux->topic.topic) == 0) {

								flag = 0;
								break;
							}
						}
					
						if(flag) {
							struct topic* topic = malloc(sizeof(struct topic));
							topic->sf = flux->topic.sf;
							strcpy(topic->topic, flux->topic.topic);
							insList(&(clients[index].topicList), topic);
						}

					} else if (flux->type == 2) { // Unsubscribe

						// Verificam ca userul sa fie abonat
						int flag = -1;
						int ind = -1;
						TList p = clients[index].topicList;
						
						for(; p != NULL; p = p->urm){
							ind++;
							if (strcmp(((struct topic*)p->info)->topic, flux->topic.topic) == 0) {
								flag = ind;
								break;
							}
						}

						if(flag >=0) {
							removeList(&(clients[index].topicList), flag);
						}
						
					}
				}
			}
		}
	}

	close(udpSock);
	close(tcpSock);
	return 0;
}
