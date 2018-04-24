/*
** EPITECH PROJECT, 2018
** ftp / server
** File description:
** commands / mode.c
*/

#include "server.h"

void mode(client_t *client, size_t argc, char **argv)
{
	if (!client_is_logged_in(client))
		return;
	if (argc < 2) {
		send_response(client, PARAMETERS_UNKNOWN, "Usage: MODE mode");
		return;
	}
	if (strcasecmp(argv[1], "S") == 0)
		send_response(client, OK, NULL);
	else
		send_response(client, PARAMETER_NOT_IMPLEMENTED, NULL);
}