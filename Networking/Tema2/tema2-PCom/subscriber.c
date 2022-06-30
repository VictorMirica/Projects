#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/tcp.h>
#include "helpers.h"

void usage(char *file)
{
	fprintf(stderr, "Usage: %s server_address server_port\n", file);
	exit(0);
}

int main(int argc, char *argv[])
{
	char buffer[BUFSIZE];

	if (argc < 4) {
		usage(argv[0]);
	}

	setvbuf(stdout, NULL, _IONBF, BUFSIZ);

	fd_set read_fds; // multimea de citire folosita in select()
	fd_set tmp_fds;	// multime folosita temporar

	// se goleste multimea de descriptori de citire (read_fds) si multimea temporara (tmp_fds)
	FD_ZERO(&read_fds);
	FD_ZERO(&tmp_fds);

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	DIE(sockfd < 0, "socket");

	int port = atoi(argv[3]);
	DIE(port == 0, "proto atoi");

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	int ret = inet_aton(argv[2], &serv_addr.sin_addr);
	DIE(ret == 0, "inet_aton");

	// Dezactivam algoritmul Nagle
	int nagle = 1; 
	ret = setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &nagle, sizeof(int));
	DIE(ret < 0, "Nagle algorithm");

	ret = connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
	DIE(ret < 0, "connect");

	ret = send(sockfd, argv[1], 10, 0);
	DIE(ret < 0, "send");

	FD_SET(STDIN_FILENO, &read_fds);
	FD_SET(sockfd, &read_fds);

	struct flux* flux = malloc(sizeof(struct flux)); //Asta trimite un subscriber TCP
	while (1) {
		tmp_fds = read_fds; 
		
		ret = select(sockfd + 1, &tmp_fds, NULL, NULL, NULL);
		DIE(ret < 0, "select");

		memset(buffer, 0, BUFSIZE); // Reset buffer

		if (FD_ISSET(STDIN_FILENO, &tmp_fds)) {
			// se citeste de la tastatura
			fgets(buffer, BUFSIZE - 1, stdin);
			
			if (strncmp(buffer, "exit", 4) == 0) {
				flux->type = 0;
				// se trimite mesaj la server
				ret = send(sockfd, flux, sizeof(struct flux), 0);
				DIE(ret < 0, "send exit");
				break;
			}

			if (strncmp(buffer, "subscribe", 9) == 0) {
				flux->type = 1;

				sscanf(buffer+10, "%s %d",flux->topic.topic, &(flux->topic.sf));
				ret = send(sockfd, flux, sizeof(struct flux), 0);
				DIE(ret < 0, "send subscribe");
				printf("Subscribed to topic.\n");
			}

			if (strncmp(buffer, "unsubscribe", 11) == 0) {
				flux->type = 2;

				sscanf(buffer+12, "%s %n",flux->topic.topic, &(flux->topic.sf));
				ret = send(sockfd, flux, sizeof(struct flux), 0);
				DIE(ret < 0, "send unsubscribe");
				printf("Unsubscribed from topic.\n");
			}
		}

		if (FD_ISSET(sockfd, &tmp_fds)) {
			// Se primeste un mesaj de la server
			// Se va primi o structura de tip toSend
			ret = recv(sockfd, buffer, sizeof(struct toSend), 0);
			DIE(ret < 0, "recv");

			if (ret == 0) {
				break;
			}

			struct toSend* recieved = (struct toSend*)buffer;
			char* identificator = malloc(15);

			switch(recieved->msg.tip_date) {
				case 0:
					strcpy(identificator,"INT");
					break;
				case 1:
					strcpy(identificator,"SHORT_REAL");
					break;
				case 2:
					strcpy(identificator,"FLOAT");
					break;
				case 3:
					strcpy(identificator,"STRING");
					break;															
			}

			printf("%s:%u - %s - %s - %s\n", inet_ntoa(recieved->ip), recieved->port, recieved->msg.topic,
					identificator, recieved->msg.continut);
		}
	}

	close(sockfd);
	return 0;
}
