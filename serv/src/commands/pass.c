/*
** EPITECH PROJECT, 2018
** myftp / server
** File description:
** commands / pass.c
*/

#include "server.h"

void pass(client_t *client, size_t argc UNUSED, char **argv)
{
	char *pass = (argc > 1) ? argv[1] : "";

	if (!client->trylogin)
		send_response(client, BAD_COMMAND_SEQUENCE, NULL);
	client->trylogin = false;
	if (client->anon) {
		send_response(client, LOGGED_IN, NULL);
		chdir(get_server_ressources()->anon_home);
		return;
	}
	if (strcmp(pass, client->user->pw_passwd) == 0) {
		chdir(client->user->pw_dir);
		send_response(client, LOGGED_IN, NULL);
	}
	else {
		send_response(client, NOT_LOGGED_IN, NULL);
	}
}