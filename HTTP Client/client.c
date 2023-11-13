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
#define CMD_LENGTH 15
int main(int argc, char *argv[])
{
    char *message = NULL;
    char *response = NULL;
    int sockfd = 0;
    char *command;
    char *username;
    char *password;
    int is_logged_in = 0;
    char *token_jwt = NULL;
    char *cookies = NULL;
    int cookies_count;
    while(1){
      sockfd = open_connection("34.254.242.81", 8080, AF_INET, SOCK_STREAM, 0);
      command = malloc(CMD_LENGTH);
      printf("COMANDA: ");
      //citire comanda
      fgets(command, CMD_LENGTH, stdin);
      command[strlen(command) - 1] = '\0';

      //REGISTER:
      if(strcmp(command, "register") == 0) {
        //verificam daca userul e logat si comunicam eroarea daca este cazul
        if(is_logged_in == 1){
          printf("ERROR: you are already logged in! You need to log out in order to create another account.\n\n");
          close(sockfd);
          continue;
        }
        //citim username
        username = malloc(40);
        printf("USER: ");
        fgets(username, 40, stdin);
        username[strlen(username) - 1] = '\0';

        //citim parola
        password = malloc(40);
        printf("PASSWORD: ");
        fgets(password, 40, stdin);
        password[strlen(password) - 1] = '\0';


        //formam sirul JSON cu username si parola si trimited request catre server
        char *json_credentials = parse_credentials_json(username, password);
        char **payload = &json_credentials;
        message = malloc(sizeof(char*));
        message = compute_post_request("34.252.242.81", "/api/v1/tema/auth/register", "application/json", NULL, payload, 1, NULL, 0);
        send_to_server(sockfd, message);
        response = malloc(sizeof(char*));
        response = receive_from_server(sockfd);
        
        if(response[9] == '2')
          printf("User registered successfully!\n\n");
          else printf("ERROR: User already exists!\n\n");
        close(sockfd);
      }
      else
      //LOGIN:
      if(strcmp(command, "login") == 0){
        if(is_logged_in == 1){
          //verificam daca userul este deja logat si trimitem mesaj de eroare daca este cazul
          printf("ERROR: you are already logged in! You need to log out in order to log into another account.\n\n");
          close(sockfd);
          continue;
        }
        
        //citim username
        username = malloc(40);
        printf("USER: ");
        fgets(username, 40, stdin);
        username[strlen(username) - 1] = '\0';

        //citim parola
        password = malloc(40);
        printf("PASSWORD: ");
        fgets(password, 40, stdin);
        password[strlen(password) - 1] = '\0';


        //formam sirul JSON cu userul si parola si trimitem mesaj catre server
        char *json_credentials = parse_credentials_json(username, password);
        char **payload = &json_credentials;
        message = malloc(sizeof(char*));
        message = compute_post_request("34.252.242.81", "/api/v1/tema/auth/login", "application/json", NULL, payload, 1, NULL, 0);
        send_to_server(sockfd, message);
        response = malloc(sizeof(char*));
        response = receive_from_server(sockfd);
        
        //daca totul este in regula, salvam cookie-ul de login si afisam mesajul de login
        if(response[9] == '2'){
          char *cookies_parser = strstr(response, "connect.sid=");
          cookies = strtok(cookies_parser," ;");
          is_logged_in = 1;
          printf("Successfully logged in!\n\n");
        }//tratam cele 2 cazuri de eroare
          else if(strstr(response,"No account"))
               printf("ERROR: User does not exist! Please create an account before logging in.\n\n");
                    else printf("ERROR: Password is incorrect!\n\n");
          
        close(sockfd);
        
      }
      else
      //LOGOUT:
      if(strcmp(command, "logout") == 0){
        if(is_logged_in == 0){
          //trimitem mesaj de eroare daca userul nu este logat
          printf("ERROR: Please log in first!\n\n");
          continue;
        }

        //trimitem request catre server
        message = malloc(sizeof(char*));
        cookies_count = cookies == NULL ? 0 : 1;
        char **cookies_aux = &cookies;
        message = compute_get_request("34.252.242.81", "/api/v1/tema/auth/logout", NULL, token_jwt, cookies_aux, cookies_count);
        send_to_server(sockfd, message);
        response = malloc(sizeof(char*));
        response = receive_from_server(sockfd);
        is_logged_in = 0;
        printf("Successfully logged out! See you later!\n\n");
        close(sockfd);
      }
      else
      //REQUEST ACCESS:
      if(strcmp(command, "enter_library") == 0){
        if(is_logged_in == 0){
          //verificam daca este logat si afisam mesajul de eroare daca este nevoie
          printf("ERROR: Please log in first!\n\n");
          close(sockfd);
          continue; 
        }

        //trimitem requestul
        message = malloc(sizeof(char*));
        cookies_count = cookies == NULL ? 0 : 1;
        char **cookies_aux = &cookies;
        message = compute_get_request("34.252.242.81", "/api/v1/tema/library/access", NULL, token_jwt, cookies_aux, 1);
        send_to_server(sockfd, message);
        response = malloc(sizeof(char*));
        response = receive_from_server(sockfd);

        //salvam tokenul JWT pentru a putea demonstra accesul la biblioteca
        token_jwt = malloc(sizeof(char*));
        char *response_aux = strstr(response, "{");
                if (response_aux) {
                    token_jwt = strtok(response_aux, "{\"}:");
                    token_jwt = strtok(NULL, "{\"}:");
                }
        if(token_jwt != NULL)
          printf("Congratulations! Access granted!\n\n");
          close(sockfd);
      }
      //GET BOOKS:
      if(strcmp(command, "get_books") == 0){
        if(is_logged_in == 0){
          printf("ERROR: Please log in first!\n\n");
          close(sockfd);
          continue;
        }

        //verificam daca utilizatorul are acces la biblioteca
        if(token_jwt != NULL){
        //compunem requestul si trimitem mesajul la server
        message = malloc(sizeof(char*));
        cookies_count = cookies == NULL ? 0 : 1;
        char **cookies_aux = &cookies;
        message = compute_get_request("34.252.242.81", "/api/v1/tema/library/books", NULL, token_jwt, cookies_aux, 1);
        send_to_server(sockfd, message);
        response = malloc(sizeof(char*));
        response = receive_from_server(sockfd);
        //afisam cartile in format JSON
        char *books = strchr(response,'[');
        printf(books);
        printf("\n\n");
        }
        else printf("ERROR: You don't have access to the library!\n\n");
        close(sockfd);
      }
      else
      //ADD BOOK:
      if(strcmp(command, "add_book") == 0){
        if(is_logged_in == 0){
          //verificam daca e logat si afisam mesaj de eroare daca e cazul
          printf("ERROR: Please log in first!\n\n");
          close(sockfd);
          continue;
        }

        //verificam daca utilizatorul are acces la biblioteca
          if(token_jwt != NULL){
            message = malloc(sizeof(char*));

            cookies_count = cookies == NULL ? 0 : 1;
            char **cookies_aux = &cookies;

            //citim datele cartii pe care vrem sa o adaugam in biblioteca
            char *title = malloc(100);
            char *author = malloc(100);
            char *genre = malloc(100);
            char *page_count = malloc(100);
            char *publisher = malloc(100);

            printf("TITLE: ");
            fgets(title, 100, stdin);
            title[strlen(title) - 1] = '\0';

            printf("AUTHOR: ");
            fgets(author, 100, stdin);
            author[strlen(author) - 1] = '\0';

            printf("GENRE: ");
            fgets(genre, 100, stdin);
            genre[strlen(genre) - 1] = '\0';

            printf("NUMBER OF PAGES: ");
            fgets(page_count, 100, stdin);
            page_count[strlen(page_count) - 1] = '\0';

            printf("PUBLISHER: ");
            fgets(publisher, 100, stdin);
            publisher[strlen(publisher) - 1] = '\0';

            //formam jirul JSON cu datele cartii
            char *book_json = parse_book_json(title, author, genre, page_count, publisher);
            char **book = &book_json;

            //trimitem mesaj carte server si afisam mesajul
            message = compute_post_request("34.252.242.81", "/api/v1/tema/library/books", "application/json", token_jwt, book, 1, cookies_aux, cookies_count);
            send_to_server(sockfd, message);
            response = malloc(sizeof(char*));
            response = receive_from_server(sockfd);
            if(strstr(response, "Something Bad Happened"))
              printf("ERROR: Could not add book! Please review the book data!\n\n");
                else
                  printf("Book added successfully!\n\n");
          }
          else printf("ERROR: Authorization needed!\n\n");
        close(sockfd);
      }
      else
      //GET BOOK BY ID:
      if(strcmp(command, "get_book") == 0) {
        if(is_logged_in == 0){
          //verificam daca e logat si afisam mesajul de eroare daca e cazul
          printf("ERROR: Please log in!\n\n");
          close(sockfd);
          continue;
        }

        //verificam daca utilizatorul are autorizatie
        if(token_jwt != NULL){
          //citim id-ul cartii
          char* id = malloc(100);
          printf("ID: ");
          fgets(id, 100, stdin);
          id[strlen(id) - 1] = '\0';
          message = malloc(sizeof(char*));
          char *url = malloc(150);
          strcpy(url,"/api/v1/tema/library/books/");
          strcat(url, id);
          //compunem mesajul trimis catre server
          char **cookies_aux = &cookies;
          cookies_count = cookies == NULL ? 0 : 1;
          message = compute_get_request("34.252.242.81", url, NULL, token_jwt, cookies_aux, cookies_count);
          send_to_server(sockfd, message);
          response = receive_from_server(sockfd);
          //afisam mesajul de eroare sau de succes
          if(strstr(response, "No book was found!"))
            printf("ERROR: We couldn't find the book you were looking for! Please double check the ID!\n\n");
              else{
                printf(strstr(response,"{\"id"));
                printf("\n\n");
                }
        }
        else printf("ERROR: Authorization needed!\n\n");
        close(sockfd);
      }
      else
      //DELETE:
      if(strcmp(command, "delete") == 0) {
        if(is_logged_in == 0){
          printf("ERROR: Please log in!\n\n");
          close(sockfd);
          continue;
        }
        if(token_jwt != NULL){
          char* id = malloc(100);
          printf("ID: ");
          fgets(id, 100, stdin);
          id[strlen(id) - 1] = '\0';
          message = malloc(sizeof(char*));
          char *url = malloc(150);
          strcpy(url,"/api/v1/tema/library/books/");
          strcat(url, id);
          message = compute_delete_request("34.252.242.81", url, token_jwt);
          send_to_server(sockfd, message);
          response = receive_from_server(sockfd);
          if(strstr(response, "No book was deleted!"))
            printf("ERROR: We couldn't find the book you were looking for! Please double check the ID!\n\n");
            else printf("Bokk successfully deleted!\n\n");
      } 
        else printf("ERROR: Authorization needed!\n\n");
        close(sockfd);
      }
      else
      //EXIT:
      if(strcmp(command, "exit") == 0){
        free(command);
        command = NULL;
        close(sockfd);
        break;
      }
      else {
        printf("ERROR: Please enter a valid command!\n\n");
      }
    }
    

    return 0;
}
