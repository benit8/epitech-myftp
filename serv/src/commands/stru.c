/*
** EPITECH PROJECT, 2018
** ftp / server
** File description:
** commands / stru.c
*/

#include "server.h"

void stru(client_t *client, size_t argc, char **argv)
{
	if (!client_is_logged_in(client))
		return;
	if (argc < 2) {
		send_response(client, PARAMETERS_UNKNOWN, "Usage: STRU type");
		return;
	}
	if (strcasecmp(argv[1], "F") == 0)
		send_response(client, OK, NULL);
	else
		send_response(client, PARAMETER_NOT_IMPLEMENTED, NULL);
}