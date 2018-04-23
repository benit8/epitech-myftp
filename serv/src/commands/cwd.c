/*
** EPITECH PROJECT, 2018
** ftp / server
** File description:
** commands / cwd.c
*/

#include "server.h"

void cwd(client_t *client, size_t argc, char **argv)
{
	if (!client_is_logged_in(client))
		return;
	if (argc < 2) {
		send_response(client, PARAMETERS_UNKNOWN,
			"Usage: CWD directory");
		return;
	}
	if (chdir(argv[1]) == 0) {
		send_response(client, FILE_ACTION_OK,
			"Directory successfully changed");
	}
	else {
		send_response(client, FILE_UNAVAILABLE,
			"%s: %s", argv[1], strerror(errno));
	}
}