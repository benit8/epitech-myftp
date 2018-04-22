/*
** EPITECH PROJECT, 2018
** myftp / server
** File description:
** commands / user.c
*/

#include "server.h"

const user_t users[] = {
	{"anonymous", ""},
	{"benito", "b"},
	{NULL, NULL}
};

void user(client_t *client, char **args)
{
	if (!args[1])
		send_response(client, NOT_LOGGED_IN, NULL);
	for (size_t i = 0; users[i].name != NULL; ++i) {
		if (strcasecmp(users[i].name, args[1]) == 0) {
			strcpy(client->name, args[1]);
			send_response(client, NEED_PASSWORD, NULL);
			return;
		}
	}
	send_response(client, NOT_LOGGED_IN, NULL);
}