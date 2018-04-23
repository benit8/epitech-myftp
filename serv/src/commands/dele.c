/*
** EPITECH PROJECT, 2018
** ftp / server
** File description:
** commands / dele.c
*/

#include "server.h"

void dele(client_t *client, size_t argc, char **argv)
{
	struct stat buf;

	if (!client_is_logged_in(client))
		return;
	if (argc < 2) {
		send_response(client, PARAMETERS_UNKNOWN, "Usage: DELE file");
		return;
	}
	if (stat(argv[1], &buf) == -1 || !S_ISREG(buf.st_mode)) {
		send_response(client, FILE_UNAVAILABLE, "%s: %s", argv[1],
			strerror(errno));
		return;
	}
	if (unlink(argv[1]) == -1) {
		send_response(client, FILE_ACTION_ABORTED, "%s: %s", argv[1],
			strerror(errno));
		return;
	}
	send_response(client, FILE_ACTION_OK, NULL);
}