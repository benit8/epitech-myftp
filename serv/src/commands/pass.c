/*
** EPITECH PROJECT, 2018
** myftp / server
** File description:
** commands / pass.c
*/

#include "server.h"

void pass(client_t *client, char **args)
{
	char *pass = args[1] ? args[1] : "";

	if (!client->name)
		send_response(client, BAD_COMMAND_SEQUENCE, NULL);
	for (size_t i = 0; users[i].name; ++i) {
		if (strcasecmp(users[i].name, client->name) != 0)
			continue;
		if (strcmp(users[i].pass, pass) == 0) {
			send_response(client, LOGGED_IN, NULL);
			return;
		}
		break;
	}
	send_response(client, NOT_LOGGED_IN, NULL);
}