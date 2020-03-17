#ifndef CHERRY_H
#define CHERRY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#define MAX_CHAR_BUFF 4096

/*
 * Struct: CH
 * ----------
 * Provides a "namespace" for cherry's functions.
 */

typedef struct {
	/*---------------------------------------------------------------------
	 *                              Primary
	 *--------------------------------------------------------------------*/

	/*
	 * Function: echo(char *msg)
	 * -------------------------
	 * Outputs a string.
	 */
	void (*echo)(char*);

	/*
	 * Function: get(char *msg)
	 * -------------------------
	 * Outputs a string.
	 */
	void (*get)(char*, char *(*handler)(void));

	/*
	 * Function: get_query_string(char* key)
	 * -------------------------------------
	 * Get query string value based on the key.
	 *
	 * returns: char* containing the value.
	 */
	char *(*get_query_string)(char*);

	/*
	 * Function: get_request_method()
	 * ------------------------------
	 * Get current performed request
	 *
	 * returns: char* of either "GET", "POST", "PUT", etc.
	 */
	char *(*get_request_method)(void);


	/*---------------------------------------------------------------------
	 *                              Auxiliary
	 *--------------------------------------------------------------------*/

	/*
	 * Function: *strcat(char *s1, char *s2)
	 * -------------------------------------
	 * A slightly more flexible string concatenation function.
	 *
	 * returns: char* as the result of the concatenation of s1 and s2
	 */ 
	char *(*strcat)(char*, char*);

	/*
	 * Function: *strcat_multiple(int numstr, ...)
	 * -------------------------------------
	 * Concatenate a series of string. The number of string is determied by
	 * `numstr`.
	 *
	 * returns: char* containing concatenation of `numstr` strings
	 */ 
	char *(*strcat_multiple)(int, ...);

	/*
	 * Function: *substr(char *s1, char *s2)
	 * -------------------------------------
	 * A slightly more flexible string concatenation function.
	 *
	 * returns: char* as the result of the concatenation of s1 and s2
	 */ 
	char *(*substr)(char*, int, int);

} namespace_struct;
extern namespace_struct const CH;

typedef struct {
	void (*get_handler);
	void (*post_handler);
} RequestHandler;

/* 
 * Primary
 */
void CH_echo(char *msg);
void CH_get(char* route, char *(*handler)(void));
char *CH_get_request_method();
char *CH_get_query_string(char *key);

/* 
 * Auxillaries
 */
char *CH_strcat(char *s1, char *s2);
char *CH_substr(char *str, int offset, int amount);

int regex_match(const char *string, char *pattern) {
#endif
