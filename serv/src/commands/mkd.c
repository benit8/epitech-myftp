/*
** EPITECH PROJECT, 2018
** ftp / server
** File description:
** commands / mkd.c
*/

#include "server.h"

void mkd(client_t *client, size_t argc, char **argv)
{
	char buf[PATH_MAX];

	if (!client_is_logged_in(client))
		return;
	if (argc < 2) {
		send_response(client, PARAMETERS_UNKNOWN, "Usage: MKD file");
		return;
	}
	if (mkdir(argv[1], 755) == -1)
		send_response(client, FILE_UNAVAILABLE, "%s: %s",
			argv[1], strerror(errno));
	else {
		bzero(buf, PATH_MAX);
		realpath(argv[1], buf);
		send_response(client, DIRECTORY_OK, "\"%s\"", buf);
	}
}