/*
** EPITECH PROJECT, 2018
** libmy
** File description:
** str_empty.c
*/

#include "my/string.h"

bool str_empty(const char *string)
{
	const char *s = string;

	if (!s)
		return (true);
	else if (*s == '\0')
		return (true);
	for (; *s != '\0'; ++s) {
		if (!isblank(*s))
			return (false);
	}
	return (true);
}