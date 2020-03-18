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

/*-----------------------------------------------------------------------------
 *                                  Primary
 *----------------------------------------------------------------------------*/

/*
 * Function: CH_handle_get(char* route, char *(*handler)(void), char*)
 * -------------------------------------------------------------------
 * Handles route with get request method.
 */
void CH_handle_get(char* route, char *(*handler)(void), char* mimetype);

/*
 * Function: CH_get_request_method()
 * ---------------------------------
 * Get current performed request
 *
 * returns: char* of either "GET", "POST", "PUT", etc.
 */
char *CH_get_request_method();

/*
 * Function: CH_get_query_string(char* key)
 * ----------------------------------------
 * Get query string value based on the key.
 *
 * returns: char* containing the value.
 */
char *CH_get_query_string(char *key);

/*
 * Function: CH_route_from_uri(char *uri)
 * --------------------------------------
 * Get query string value based on the key.
 *
 * returns: char* containing the value.
 */
char *CH_route_from_uri(char *uri);

/*
 * Function: CH_print_message_body_info(char *content_type,
                                        char *content_encoding)
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
char *str_replace(char *str, char *orig, char *rep);

#endif
