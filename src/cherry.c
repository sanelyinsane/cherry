#include "cherry.h"

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

void CH_handle_get(char *route, char *(*handler)(void), char *mimetype) {
	char *env_route = CH_route_from_uri(getenv("REQUEST_URI"));
	if (strlen(env_route) == 0) env_route = "/";

	char *regex_route = route_to_regex(route);

	if ((strcmp(CH_get_request_method(), "GET") == 0) &&
	    (regex_match(env_route, regex_route))) {
		CH_print_message_body_info(mimetype, "utf-8");
		printf("%s", handler());
	}

	free(env_route);
	free(regex_route);
}

char *CH_get_request_method() {
	return getenv("REQUEST_METHOD");
}

char *CH_get_query_string(char *key) {
	char *qs = getenv("QUERY_STRING");
	if (strlen(key) == 0)
		return qs;

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
