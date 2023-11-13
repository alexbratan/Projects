#ifndef _REQUESTS_
#define _REQUESTS_
#include "parson.h"
// computes and returns a GET request string (query_params
// and cookies can be set to NULL if not needed)
char *compute_get_request(char *host, char *url, char *query_params, char* jwt_auth, 
							char **cookies, int cookies_count);

// computes and returns a POST request string (cookies can be NULL if not needed)
char *compute_post_request(char *host, char *url, char* content_type, char* jwt_auth, char **body_data,
							int body_data_fields_count, char** cookies, int cookies_count);

// computes delete request
char *compute_delete_request(char *host, char *url, char *jwt_auth);

//converts credentials to json format
char *parse_credentials_json(char *username, char *password);

//converts book to json format
char *parse_book_json(char *title, char *author, char *genre, char* page_count, char *publisher);
#endif
