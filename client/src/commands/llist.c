/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands / llist.c
*/

#include "client.h"

static char *make_command(size_t argc, char **argv)
{
	char *cmd = NULL;
	size_t length = strlen("ls -l");

	for (size_t i = 1; i < argc; ++i)
		length += strlen(argv[i]) + 1;
	cmd = calloc(length + 1, sizeof(char));
	if (!cmd)
		return (NULL);
	strcpy(cmd, "ls -l");
	for (size_t i = 1; i < argc; ++i) {
		strcat(cmd, " ");
		strcat(cmd, argv[i]);
	}
	return (cmd);
}

int ftp_llist(data_t *data UNUSED, size_t argc, char **argv)
{
	char *cmd = make_command(argc, argv);
	int r;

	if (!cmd)
		return (-1);
	r = system(cmd);
	free(cmd);
	return ((r < 0) ? 2 : 1);
}