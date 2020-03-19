#include "cherry.h"

/*-----------------------------------------------------------------------------
 *                              Default handlers
 *----------------------------------------------------------------------------*/
char *def_error404handler() {
	return "404: The page you requested does not exist";
}

char *def_error500handler() {
	char *s = malloc(strlen(ERROR500MSG));
	sprintf(s, "500: %s", ERROR500MSG);
	return s;
}


/*-----------------------------------------------------------------------------
 *                                  Primary
 *----------------------------------------------------------------------------*/
char *CH_get_request_method() {
	return getenv("REQUEST_METHOD");
}

char *CH_get_route() {
	return CH_route_from_uri(getenv("REQUEST_URI"));

}

char *CH_get_query_string(char *key) {
	char *qs = getenv("QUERY_STRING");
	if (strlen(key) == 0) return qs;

	/* the default result when key is not found */
	char *res = ""; 

	char *token = strtok(qs, "&");
	while (token != NULL) {
		/* get current current key */
		int eqpos = strstr(token, "=") - token;
		char *curr_key = CH_substr(token, 0, eqpos);

		if (strcmp(key, curr_key) == 0) {
			int amount = strlen(token) - eqpos + 1;
			res = CH_substr(token, eqpos + 1, amount);
			break;
		}
		token = strtok(NULL, "&");
	}
	return res;
}

void CH_handle_request(char *method, char *route, char *(*handler)(void),
                       char *mimetype) {
	char *env_route   = CH_get_route();
	char *regex_route = route_to_regex(route);

	if (strlen(env_route) == 0) env_route = "/"; 

	if ((strcmp(CH_get_request_method(), method) == 0) &&
	    (regex_match(env_route, regex_route))) {
		MIMETYPE_CANDIDATE        = mimetype;
		REQUEST_HANDLER_CANDIDATE = handler;
		NUM_MATCHING_ROUTE++;
	}
	free(regex_route);
}

void CH_init() {
	NUM_MATCHING_ROUTE = 0;
	ERROR404HANDLER    = def_error404handler;
	ERROR500HANDLER    = def_error500handler;
	ERROR500MSG        = "";
}

void CH_print_message_body_info(char *content_type,
                                char *content_encoding) {
	printf("Content-Type: %s\n", content_type);
	printf("Content-Encoding: %s\n", content_encoding);
	printf("\n");
}

char *CH_route_from_uri(char *uri) {
	char *script_name = getenv("SCRIPT_NAME");
	char *route = CH_substr(uri, strlen(script_name), strlen(uri));
	return route;
}

void CH_run() {
	if (NUM_MATCHING_ROUTE == 0) {
		/*
		 * 404: route not found
		 */
		REQUEST_HANDLER_CANDIDATE = ERROR404HANDLER;
	} else if (NUM_MATCHING_ROUTE > 1) {
		/*
		 * 500: duplicate routes
		 */
		char *s1  = "Duplicate or ambiguous route: ";
		char *route = CH_get_route();
		char *msg = malloc(MAX_CHAR_BUFF);
		if (strlen(route) == 0) route = "/";
		strcpy(msg, "");
		strcat(msg, s1);
		strcat(msg, route);
		ERROR500MSG = msg;

		REQUEST_HANDLER_CANDIDATE = ERROR500HANDLER;
		MIMETYPE_CANDIDATE        = MIME_TEXT_PLAIN;
	} 
	CH_print_message_body_info(MIMETYPE_CANDIDATE, "utf-8");
	printf("%s", REQUEST_HANDLER_CANDIDATE());
	printf("\n");
}

char *CH_strcat(char *s1, char *s2) {
	int len;
	char *s;
	if (s1 != NULL) 
		len = strlen(s1);
	len += strlen(s2) + 1 * sizeof(*s2);
	s = realloc(s1, len);
	strcat(s, s2);

	return s;
}

char *CH_strcat_multiple(int numstr, ...) {
	/* TODO: implement this, lol */
	return "";
}

char *CH_substr(char *str, int offset, int amount) {
	char *res = 0;
	res = (char*)malloc(amount + 1);
	memcpy(res, str + offset, amount);
	res[amount] = 0;
	return res;
}

int regex_match(const char *string, char *pattern) {
	int status;
	regex_t re;

	if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
		return(0);
	}
	status = regexec(&re, string, (size_t) 0, NULL, 0);
	regfree(&re);
	if (status != 0) {
		return(0);
	}
	return(1);
}

char *route_to_regex(char *route) {
	/*
	 * TODO: Convert special route format to POSIX-compatible regex.
	 */
	char *regex_route = malloc(MAX_CHAR_BUFF);
	strcpy(regex_route, "^(");
	strcat(regex_route, route);
	strcat(regex_route, ")(\\?([[:alnum:]=]+)?)?$");

	return regex_route;
}

char *str_replace(char *str, char *orig, char *rep) {
	static char buffer[MAX_CHAR_BUFF];
	char *p;
	int i = 0;

	if (!(p = strstr(str + i, orig))) {
		return str;
	}

	while (str[i]) {
		if (!(p = strstr(str + i, orig))) {
			strcat(buffer, str + i);
			break; //return str;
		}
		strncpy(buffer + strlen(buffer), str + i, (p - str) - i);
		buffer[p - str] = '\0';
		strcat(buffer, rep);
		i = (p - str) + strlen(orig);
	}

	return buffer;
}
