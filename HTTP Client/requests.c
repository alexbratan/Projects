#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <stdio.h>
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"



char *compute_get_request(char *host, char *url, char *query_params,char* jwt_auth,
                            char **cookies, int cookies_count)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));

    // Step 1: write the method name, URL, request params (if any) and protocol type
    if (query_params != NULL) {
        sprintf(line, "GET %s?%s HTTP/1.1", url, query_params);
    } else {
        sprintf(line, "GET %s HTTP/1.1", url);
    }

    compute_message(message, line);

    // Step 2: add the host

    sprintf(line,"Host: %s", host);
    compute_message(message, line);
    // Step 3 (optional): add headers and/or cookies, according to the protocol format
    sprintf(line, "Authorization: Bearer %s", jwt_auth);
    compute_message(message, line);
    if (cookies != NULL) {
       for(int i = 0; i < cookies_count; i++){
       sprintf(line, "Cookie: %s", cookies[i]);
       compute_message(message, line);
       }
    }
    // Step 4: add final new line
    compute_message(message, "");
    return message;
}

char *compute_post_request(char *host, char *url, char *content_type, char* jwt_auth, char **body_data,
                            int body_data_fields_count, char **cookies, int cookies_count)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));
    char *body_data_buffer = calloc(LINELEN, sizeof(char));

    // Step 1: write the method name, URL and protocol type
    sprintf(line, "POST %s HTTP/1.1", url);
    compute_message(message, line);
    
    // Step 2: add the host
    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    /* Step 3: add necessary headers (Content-Type and Content-Length are mandatory)
            in order to write Content-Length you must first compute the message size
    */

    for (int i = 0; i < body_data_fields_count; i++) {
        if (i < body_data_fields_count - 1) {
            strcat(body_data_buffer, body_data[i]);
            strcat(body_data_buffer, "&");
        }
        else {
            strcat(body_data_buffer, body_data[i]);
        }
    }

    sprintf(line, "Content-Type: %s", content_type);
    compute_message(message, line);
    sprintf(line, "Content-Length: %ld", strlen(body_data_buffer));
    compute_message(message, line);
    sprintf(line, "Authorization: Bearer %s", jwt_auth);
    compute_message(message, line);
    // Step 4 (optional): add cookies
    if (cookies != NULL) {
       sprintf(line, "Cookie:");
       for (int i = 0; i < cookies_count; i++) {
           sprintf(line, " %s;", cookies[i]);
           compute_message(message, line);
       }
    }
    // Step 5: add new line at end of header
    compute_message(message, "");

    // Step 6: add the actual payload data
    memset(line, 0, LINELEN);
    compute_message(message, body_data_buffer);

    free(line);
    return message;
}
char *compute_delete_request(char *host, char *url, char *jwt_auth){
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));

    // Step 1: write the method name, URL and protocol type
    sprintf(line, "DELETE %s HTTP/1.1", url);
    compute_message(message, line);
    
    // Step 2: add the host
    sprintf(line, "Host: %s", host);
    compute_message(message, line);
    
    sprintf(line, "Authorization: Bearer %s", jwt_auth);
    compute_message(message, line);
    // Step 5: add new line at end of header
    compute_message(message, "");
    free(line);
    return message;
}
char *parse_credentials_json(char *username, char *password){
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *credentials_json = json_value_get_object(root_value);

    json_object_set_string(credentials_json, "username", username);
    json_object_set_string(credentials_json, "password", password);

    
    char *json_credentials_converted = json_serialize_to_string_pretty(root_value);

    json_value_free(root_value);

    return json_credentials_converted;
}

char *parse_book_json(char *title, char *author, char *genre, char* page_count, char *publisher){
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *book = json_value_get_object(root_value);

    json_object_set_string(book, "title", title);
    json_object_set_string(book, "author", author);
    json_object_set_string(book, "genre", genre);
    json_object_set_string(book, "page_count", page_count);
    json_object_set_string(book, "publisher", publisher);

    char *book_converted = json_serialize_to_string_pretty(root_value);
    json_value_free(root_value);

    return book_converted;
}