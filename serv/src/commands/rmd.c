/*
** EPITECH PROJECT, 2018
** ftp / server
** File description:
** commands / rmd.c
*/

#include "server.h"

void rmd(client_t *client, size_t argc, char **argv)
{
	if (!client_is_logged_in(client))
		return;
	if (argc < 2) {
		send_response(client, PARAMETERS_UNKNOWN, "Usage: RMD file");
		return;
	}
	if (access(argv[1], F_OK) == -1) {
		send_response(client, FILE_UNAVAILABLE, "%s: %s",
			argv[1], strerror(errno));
		return;
	}
	if (rmdir(argv[1]) == 0)
		send_response(client, DIRECTORY_OK, NULL);
	else {
		send_response(client, FILE_ACTION_ABORTED, "%s: %s",
			argv[1], strerror(errno));
	}
}