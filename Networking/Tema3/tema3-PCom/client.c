#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"
#include "parson.h"

void inputUserPass(char** serialized_string) {
    char* user = malloc(100);
    char* pass = malloc(100);

    // Citim userul si parola
    printf("username=");
    scanf("%s", user);
    printf("password=");
    scanf("%s", pass);

    // Parse json
    JSON_Value* root_value = json_value_init_object();
    JSON_Object* root_object = json_value_get_object(root_value);
    json_object_set_string(root_object, "username", user);
    json_object_set_string(root_object, "password", pass);

    *serialized_string = json_serialize_to_string_pretty(root_value);
    return;
}

int main(int argc, char *argv[])
{
    char *message;
    char *response;
    char* error;
    int sockfd;
    char* command = malloc(LINELEN);

    int loggedIn = 0; // 1 daca suntem logati/ 0 altfel
    int hasAccess = 0; // Are acces in librarie?
    char* cookie = malloc(LINELEN);
    char* tokenJWT = malloc(LINELEN);
    

    while(1){
        
        // Open socket
        sockfd = open_connection("34.241.4.235", 8080, AF_INET, SOCK_STREAM, 0);

        scanf("%s", command);

        if (strcmp(command, "register") == 0) { // Inregistram un cont NOU

            // Functie care citeste un user de la tastatura,
            // intoarce format json
            char* serialized_string;
            inputUserPass(&serialized_string);

            // Post request
            message = compute_post_request("34.241.4.235", "/api/v1/tema/auth/register", "application/json",
                                        &serialized_string, 1, NULL, 0, NULL);
            send_to_server(sockfd, message);

            response = receive_from_server(sockfd);
            error = basic_extract_json_response(response);


            if(error != NULL) { // Am primit o eroare, in acest caz, same user
                puts(error);
            } else {
                printf("Utilizator inregistrat cu succes!\n");
            }
        }

        if (strcmp(command, "login") == 0) { // Un user incearca sa se logheze
            if (loggedIn == 0) { // Verificam daca suntem deja logati
                // Citim user-ul de la tastatura
                char* serialized_string;
                inputUserPass(&serialized_string);

                // Post request
                message = compute_post_request("34.241.4.235", "/api/v1/tema/auth/login", "application/json",
                                            &serialized_string, 1, NULL, 0, NULL);
                send_to_server(sockfd, message);

                response = receive_from_server(sockfd);
                error = basic_extract_json_response(response);

                if(error != NULL) {
                    puts(error);
                } else {

                    // Suntem logati, preluam cookies.
                    loggedIn = 1;
                    char* responseCookies = strstr(response, "Set-Cookie: ");
                    char* token = strtok(responseCookies + 12,";");
                    strcpy(cookie, token);
                    printf("Logare efectuata cu succes!\n");
                }
            } else {
                printf("Este un utilizator deja logat\n");
            }
        }

        if (strcmp(command, "enter_library") == 0) { // Cerem acces in biblioteca
            if (loggedIn) { // Trebuie sa fim logati

                // Get request
                message = compute_get_request("34.241.4.235", "/api/v1/tema/library/access", NULL,
                                            &cookie, 1, NULL);
                send_to_server(sockfd, message);

                response = receive_from_server(sockfd);
                char* token = basic_extract_json_response(response);
        
                // Trebuie preluat tokenul JWT
                if(token != NULL) {
                    hasAccess = 1;
                    strcpy(tokenJWT, token + 10); // Formatez stringul ce contine tokenul.
                    tokenJWT[strlen(tokenJWT) - 2] = '\0';
                    
                    printf("Acces permis cu token-ul: %s\n", tokenJWT);
                } 
            } else {
                printf("Trebuie sa fiti logat!\n");
            }
        }

        if (strcmp(command, "get_books") == 0) { // Afisez toate cartile
            if(loggedIn) {
                if (hasAccess) { // Trebuie sa avem acces la biblioteca

                    // Get request
                    message = compute_get_request("34.241.4.235", "/api/v1/tema/library/books", NULL,
                                                &cookie, 1, tokenJWT);
                    send_to_server(sockfd, message);

                    response = receive_from_server(sockfd);
                    
                    printf("Books: %s\n", strstr(response, "["));
                } else {
                    printf("Nu aveti acces la biblioteca!\n");
                }
            } else {
                printf("Trebuie sa fiti logat!\n");
            }
        }

        if (strcmp(command, "get_book") == 0) { // Afisez o carte specifica
            if (loggedIn) {
                if (hasAccess) { // Trebuie sa avem acces la biblioteca
                    char* id = malloc(100);

                    // Citim id-ul
                    printf("id=");
                    scanf("%s", id);

                    // Creez url-ul pentru id-ul dat
                    char* url = malloc(100);
                    sprintf(url, "/api/v1/tema/library/books/%s", id);

                    // Get request
                    message = compute_get_request("34.241.4.235", url, NULL, &cookie, 1, tokenJWT);
                    send_to_server(sockfd, message);

                    response = receive_from_server(sockfd);
                    error = basic_extract_json_response(response);

                    puts(error); // Va afisa fie cartea, fie eroarea de id invalid.
                } else {
                    printf("Nu aveti acces la biblioteca!\n");
                }
            } else {
                printf("Trebuie sa fiti logat!\n");
            }
        }

        if (strcmp(command, "add_book") == 0) { // Adaug o carte
            if (loggedIn) {
                if (hasAccess) {

                    char* title = malloc(100);
                    char* author = malloc(100);
                    char* genre = malloc(100);
                    char* publisher = malloc(100);
                    int page_count;

                    // Campurile pentru payload-ul necesar
                    fgets(title, LINELEN, stdin);
                    printf("title=");
                    fgets(title, LINELEN, stdin);
                    title[strlen(title) - 1] = '\0';
                    printf("author=");
                    fgets(author, LINELEN, stdin);
                    author[strlen(author) - 1] = '\0';                    
                    printf("genre=");
                    fgets(genre, LINELEN, stdin);
                    genre[strlen(genre) - 1] = '\0';
                    printf("publisher=");
                    fgets(publisher, LINELEN, stdin);
                    publisher[strlen(publisher) - 1] = '\0';
                    printf("page_count=");
                    if(!scanf("%d", &page_count)) {
                        printf("Eroare de formatare.\n"); // Eroare de formatare
                        continue;
                    } 
                    

                    // Parse json
                    JSON_Value* root_value = json_value_init_object();
                    JSON_Object* root_object = json_value_get_object(root_value);
                    json_object_set_string(root_object, "title", title);
                    json_object_set_string(root_object, "author", author);
                    json_object_set_string(root_object, "genre", genre);
                    json_object_set_number(root_object, "page_count", page_count);
                    json_object_set_string(root_object, "publisher", publisher);

                    char* serialized_string = json_serialize_to_string_pretty(root_value);        

                    // Post request
                    message = compute_post_request("34.241.4.235", "/api/v1/tema/library/books", "application/json",
                                                &serialized_string, 1, &cookie, 1, tokenJWT);
                    send_to_server(sockfd, message);

                    response = receive_from_server(sockfd);
                    error = basic_extract_json_response(response);


                    if(error != NULL) { // Am primit o eroare de formatare
                        puts(error);
                    } else {
                        printf("Carte adaugata cu succes!\n");
                    }

                } else {
                    printf("Nu aveti acces la biblioteca!\n");
                }
            } else {
                printf("Trebuie sa fiti logat!\n");
            }
        }

        if (strcmp (command, "delete_book") == 0) { // Elimin o carte
            if (loggedIn) {
                if (hasAccess) {
                    char* id = malloc(100);

                    // Citim id-ul
                    printf("id=");
                    scanf("%s", id);

                    // Creez url-ul pentru id-ul dat
                    char* url = malloc(100);
                    sprintf(url, "/api/v1/tema/library/books/%s", id);

                    // Delete request
                    message = compute_delete_request("34.241.4.235", url, NULL, &cookie, 1, tokenJWT);
                    send_to_server(sockfd, message);

                    response = receive_from_server(sockfd);
                    error = basic_extract_json_response(response);

                if(error != NULL) { // Am primit o eroare de id invalid.
                        puts(error);
                    } else {
                        printf("Carte stearsa cu succes!\n");
                    } 
                } else {
                    printf("Nu aveti acces la biblioteca!\n");
                }
            } else {
                printf("Trebuie sa fiti logat!\n");
            }
        }

        if (strcmp (command, "logout") == 0) { // Userul de delogheaza
            if (loggedIn) {

                loggedIn = 0;
                hasAccess = 0;

                // Get request
                message = compute_get_request("34.241.4.235", "/api/v1/tema/auth/logout", NULL,
                                            &cookie, 1, NULL);
                send_to_server(sockfd, message);

                response = receive_from_server(sockfd);
                printf("Delogat cu succes.\n");
            } else {
                printf("Nu sunteti logat.\n");
            }
        }
       
        // Close socket
        close(sockfd);

        if (strcmp (command, "exit") == 0) { // Ies din program
            break;
        } 
    }


    return 0;
}
