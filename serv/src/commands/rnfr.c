/*
** EPITECH PROJECT, 2018
** ftp / server
** File description:
** commands / rnfr.c
*/

#include "server.h"

void rnfr(client_t *client, size_t argc, char **argv)
{
	if (!client_is_logged_in(client))
		return;
	if (argc < 2) {
		send_response(client, PARAMETERS_UNKNOWN, "Usage: RNFR file");
		return;
	}
	if (access(argv[1], F_OK) == -1) {
		send_response(client, FILE_UNAVAILABLE, "%s: %s",
			argv[1], strerror(errno));
		return;
	}
	strcpy(client->to_rename, argv[1]);
	send_response(client, NEED_INFORMATION, NULL);
}