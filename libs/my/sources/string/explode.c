/*
** EPITECH PROJECT, 2018
** libmy
** File description:
** explode.c
*/

#include "my/string.h"

static bool explode_append(char ***tabp, size_t *sizep, char *token)
{
	char **ntab = realloc(*tabp, sizeof(char *) * ((*sizep) + 2));

	if (!ntab)
		return (false);
	ntab[(*sizep)] = strdup(token);
	if (!ntab[(*sizep)])
		return (false);
	ntab[++(*sizep)] = NULL;
	*tabp = ntab;
	return (true);
}

char **explode(char *original, const char *delim)
{
	size_t tokens = 0;
	char *copy = strdup(original);
	char *c = copy;
	char *token = strsep(&copy, delim);
	char **tab = calloc(1, sizeof(char *));

	if (!tab)
		return (NULL);
	for (; token != NULL; token = strsep(&c, delim)) {
		if (!explode_append(&tab, &tokens, token))
			break;
	}
	free(copy);
	return (tab);
}