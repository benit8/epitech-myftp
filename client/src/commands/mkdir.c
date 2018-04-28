/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands / mkdir.c
*/

#include "client.h"

int ftp_mkdir(data_t *data, size_t argc, char **argv)
{
	char *dirname = NULL;

	if (!connected(data))
		return (2);
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
	send_command(data, "MKD %s", dirname);
	free(dirname);
	return (response_wait(data, true));
}