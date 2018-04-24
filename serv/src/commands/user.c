/*
** EPITECH PROJECT, 2018
** myftp / server
** File description:
** commands / user.c
*/

#include "server.h"

void user(client_t *client, size_t argc, char **argv)
{
	if (argc < 2) {
		send_response(client, PARAMETERS_UNKNOWN, NULL);
		return;
	}
	if (strcasecmp(argv[1], "anonymous") == 0)
		client->anon = true;
	else
		strcpy(client->username, argv[1]);
	send_response(client, NEED_PASSWORD, NULL);
}