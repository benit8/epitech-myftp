/*
** EPITECH PROJECT, 2018
** myftp / server
** File description:
** commands / user.c
*/

#include "server.h"

const user_t users[] = {
	{"anonymous", ""},
	{NULL, NULL}
};

void user(client_t *client, size_t argc, char **argv)
{
	if (argc < 2) {
		send_response(client, NOT_LOGGED_IN, NULL);
		return;
	}
	if (strcasecmp(argv[1], "anonymous") == 0) {
		client->anon = true;
		client->trylogin = true;
		send_response(client, NEED_PASSWORD, NULL);
		return;
	}
	client->user = getpwnam(argv[1]);
	if (!client->user) {
		send_response(client, NOT_LOGGED_IN, NULL);
		return;
	}
	send_response(client, NEED_PASSWORD, NULL);
	client->trylogin = true;
}