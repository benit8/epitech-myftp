/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands / delete.c
*/

#include "client.h"

int ftp_delete(data_t *data, size_t argc, char **argv)
{
	char *filename = NULL;

	if (!connected(data))
		return (2);
	if (argc > 1)
		filename = strdup(argv[1]);
	else {
		filename = prompt("(remote-file)", false);
		if (!filename)
			return (2);
		else if (str_empty(filename)) {
			printf("usage: %s remote-file\n", argv[0]);
			free(filename);
			return (2);
		}
	}
	send_command(data, "DELE %s", filename);
	free(filename);
	return (response_wait(data, true));
}