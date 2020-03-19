#ifndef CHERRY_H
#define CHERRY_H

#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#define MAX_CHAR_BUFF 4096
#define MIME_APPLICATION_JSON "application/json"
#define MIME_TEXT_PLAIN       "text/plain"
#define MIME_TEXT_HTML        "text/html"
#define METHOD_GET            "GET"
#define METHOD_POST           "POST"
#define METHOD_PUT            "PUT"



/*-----------------------------------------------------------------------------
 *                                  Globals
 *----------------------------------------------------------------------------*/
char *(*ERROR404HANDLER)(void);
char *(*ERROR500HANDLER)(void);
int   NUM_MATCHING_ROUTE;
char *MIMETYPE_CANDIDATE;
char *(*REQUEST_HANDLER_CANDIDATE)(void);
char *ERROR404MSG;
char *ERROR500MSG;


/*-----------------------------------------------------------------------------
 *                              Default handlers
 *----------------------------------------------------------------------------*/
char *def_error404handler();
char *def_error500handler();


/*-----------------------------------------------------------------------------
 *                                  Primary
 *----------------------------------------------------------------------------*/

/*
 * Function: CH_get_request_method()
 * ---------------------------------
 * Get current performed request
 *
 * returns: char* of either "GET", "POST", "PUT", etc.
 */
char *CH_get_request_method();

char *CH_get_route();

/*
 * Function: CH_get_query_string(char* key)
 * ----------------------------------------
 * Get query string value based on the key.
 *
 * returns: char* containing the value.
 */
char *CH_get_query_string(char *key);

/*
 * Function: CH_handle_request(char *method,
 *                             char *route,
 *                             char *(*handler)(void),
 *                             char *mimetype);
 * ---------------------------------------------------
 * Handles route according to the determined request method.
 */
void CH_handle_request(char *method,
                       char *route,
                       char *(*handler)(void),
                       char *mimetype);

/*
 * Function: CH_init();
 * --------------------
 * Initialize cherry with defaults
 */
void CH_init();

/*
 * Function: CH_route_from_uri(char *uri)
 * --------------------------------------
 * Get query string value based on the key.
 *
 * returns: char* containing the value.
 */
char *CH_route_from_uri(char *uri);

void CH_run();

/*
 * Function: CH_print_message_body_info(char *content_type,
 *                                      char *content_encoding)
 * ------------------------------------------------------------
 * Print the message body info.
 */
void CH_print_message_body_info(char *content_type, char *content_encoding);


/*-----------------------------------------------------------------------------
 *                                  Auxiliary
 *----------------------------------------------------------------------------*/
/*
 * Function: CH_strcat(char *s1, char *s2)
 * ---------------------------------------
 * A slightly more flexible string concatenation function.
 *
 * returns: char* as the result of the concatenation of s1 and s2
 */ 
char *CH_strcat(char *s1, char *s2);

/*
 * Function: CH_strcat_multiple(int numstr, ...)
 * ---------------------------------------------
 * Concatenate a series of string. The number of string is determied by
 * `numstr`.
 *
 * returns: char* containing concatenation of `numstr` strings
 */ 
char *CH_strcat_multiple(int, ...);

/*
 * Function: *substr(char *s1, char *s2)
 * -------------------------------------
 * A slightly more flexible string concatenation function.
 *
 * returns: char* as the result of the concatenation of s1 and s2
 */ 
char *CH_substr(char *str, int offset, int amount);


/*-----------------------------------------------------------------------------
 *                                 Utilities
 *----------------------------------------------------------------------------*/
int  regex_match(const char *string, char *pattern);
char *route_to_regex(char *route);
char *str_replace(char *str, char *orig, char *rep);

#endif
