/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands / quote.c
*/

#include "client.h"

int ftp_quote(data_t *data, size_t argc, char **argv)
{
	char *cmd = NULL;

	if (!connected(data))
		return (2);
	if (argc > 1)
		cmd = implode(argv + 1, " ");
	else {
		cmd = prompt("(command line to send)", false);
		if (!cmd)
			return (2);
		else if (str_empty(cmd)) {
			printf("\nusage: quote line-to-send\n");
			return (2);
		}
	}
	send_command(data, cmd);
	free(cmd);
	return (response_wait(data, true));
}