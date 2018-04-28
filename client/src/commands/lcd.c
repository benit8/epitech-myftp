/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands / lcd.c
*/

#include "client.h"

int ftp_lcd(data_t *data UNUSED, size_t argc, char **argv)
{
	char *dirname = NULL;

	if (argc > 1)
		dirname = strdup(argv[1]);
	else {
		dirname = prompt("(directory-name)", false);
		if (!dirname)
			return (2);
		else if (str_empty(dirname)) {
			printf("usage: %s directory-name\n", argv[0]);
			free(dirname);
			return (2);
		}
	}
	if (chdir(argv[1]) == -1) {
		printf("%s: %s\n", argv[1], strerror(errno));
		return (2);
	}
	free(dirname);
	return (1);
}