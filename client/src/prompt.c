/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** prompt.c
*/

#include "client.h"

char *prompt(char *prompt)
{
	char *line = NULL;
	size_t s = 0;
	ssize_t r = 0;

	if (!prompt)
		prompt = DEFAULT_PROMPT;
	printf("%s ", prompt);
	r = getline(&line, &s, stdin);
	if (r < 0)
		return (NULL);
	line[strlen(line) - 1] = '\0';
	return (line);
}