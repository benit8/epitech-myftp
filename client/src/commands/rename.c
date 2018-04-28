/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands / rename.c
*/

#include "client.h"

char *get_from_name(size_t argc, char **argv)
{
	char *filename = NULL;

	if (argc > 1)
		filename = strdup(argv[1]);
	else {
		filename = prompt("(from-name)", false);
		if (!filename)
			return (NULL);
		else if (str_empty(filename)) {
			printf("usage: %s from-name to-name\n", argv[0]);
			free(filename);
			return (NULL);
		}
	}
	return (filename);
}

char *get_to_name(size_t argc, char **argv)
{
	char *filename = NULL;

	if (argc > 2)
		filename = strdup(argv[2]);
	else {
		filename = prompt("(to-name)", false);
		if (!filename)
			return (NULL);
		else if (str_empty(filename)) {
			printf("usage: %s from-name to-name\n", argv[0]);
			free(filename);
			return (NULL);
		}
	}
	return (filename);
}

int ftp_rename(data_t *data, size_t argc, char **argv)
{
	char *from = NULL;
	char *to = NULL;

	if (!connected(data))
		return (2);
	from = get_from_name(argc, argv);
	if (!from)
		return (2);
	to = get_to_name(argc, argv);
	if (!to)
		return (2);
	send_command(data, "RNFR %s", from);
	free(from);
	if (response_wait(data, true) == 1) {
		send_command(data, "RNTO %s", to);
		free(to);
		return (response_wait(data, true));
	}
	return (2);
}