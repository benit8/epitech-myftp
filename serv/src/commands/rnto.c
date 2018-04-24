/*
** EPITECH PROJECT, 2018
** ftp / server
** File description:
** commands / rnto.c
*/

#include "server.h"

void rnto(client_t *client, size_t argc, char **argv)
{
	if (!client_is_logged_in(client))
		return;
	if (argc < 2) {
		send_response(client, PARAMETERS_UNKNOWN, "Usage: RNTO file");
		return;
	}
	if (strcasecmp(client->last_command, "rnfr") != 0) {
		send_response(client, BAD_COMMAND_SEQUENCE, NULL);
		return;
	}
	if (access(client->to_rename, F_OK) == -1) {
		send_response(client, FILE_UNAVAILABLE, "%s: %s",
			client->to_rename, strerror(errno));
		return;
	}
	if (rename(client->to_rename, argv[1]) == -1) {
		send_response(client, FILENAME_NOT_ALLOWED, "%s: %s",
			client->to_rename, strerror(errno));
		return;
	}
	send_response(client, FILE_ACTION_OK, NULL);
	bzero(client->to_rename, PATH_MAX);
}