#include "cherry.h"

/* 
 * Primary
 */
void CH_echo(char *msg);
char *CH_get_query_string(char *key);

/* 
 * Auxillaries
 */
char *CH_strcat(char *s1, char *s2);
char *CH_substr(char *str, int offset, int amount);

void CH_echo(char *msg) {
	char *res = CH.strcat(NULL, "");
	res = CH_strcat(res, "Content-type: text/html\n\n");
	res = CH_strcat(res, msg);
	res = CH_strcat(res, "\n");
	printf("%s", res);
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

namespace_struct const CH = {
	CH_echo,
	CH_get_query_string,
	CH_strcat,
	CH_strcat_multiple,
	CH_substr
};
