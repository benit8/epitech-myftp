/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands / cd.c
*/

#include "client.h"

int ftp_cd(data_t *data, size_t argc, char **argv)
{
	char *cmd = NULL;

	if (!connected(data))
		return (2);
	if (argc > 1)
		cmd = strdup(argv[1]);
	else {
		cmd = prompt("(remote-directory)", false);
		if (!cmd)
			return (2);
		else if (str_empty(cmd)) {
			printf("\nusage: cd remote-directory\n");
			return (2);
		}
	}
	send_command(data, "CWD %s" ,cmd);
	free(cmd);
	return (response_wait(data, true));
}