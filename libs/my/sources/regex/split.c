/*
** EPITECH PROJECT, 2018
** libmy
** File description:
** split.c
*/

#include "my/regex.h"

char **regex_split(char *pattern, char *subject)
{
	char **array = calloc(1, sizeof(char *));
	regmatch_t *matches = calloc(1, sizeof(regmatch_t));
	regex_t regex;
	size_t n = 0;
	int ok = regcomp(&regex, pattern, REG_EXTENDED);

	if (ok != 0 || (matches == NULL || array == NULL))
		return (NULL);
	for (; regexec(&regex, subject, 1, matches, 0) != REG_NOMATCH; ++n) {
		array = realloc(array, sizeof(char *) * (n + 3));
		if (array == NULL)
			return (NULL);
		array[n] = strndup(subject, matches[0].rm_so);
		subject += matches[0].rm_eo;
	}
	array[n++] = strdup(subject);
	regfree(&regex);
	free(matches);
	return (array);
}