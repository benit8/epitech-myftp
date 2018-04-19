/*
** EPITECH PROJECT, 2018
** libmy
** File description:
** str_trim.c
*/

#include "my/string.h"

char *str_trim(char *str)
{
	char *dest = str;
	char *end = str + strlen(str);

	for (; *str && isspace(*str); str++);
	while (end > str) {
		if (!isspace(*(end - 1)))
			break;
		end--;
	}
	*end = '\0';
	memmove(dest, str, end - str + 1);
	return (dest);
}