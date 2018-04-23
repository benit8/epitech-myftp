/*
** EPITECH PROJECT, 2018
** myftp / server
** File description:
** commands / pass.c
*/

#include "server.h"

void pass(client_t *client, size_t argc, char **argv)
{
	char *pass = (argc > 1) ? argv[1] : "";

	if (!client->trylogin)
		send_response(client, BAD_COMMAND_SEQUENCE, NULL);
	client->trylogin = false;
	if (client->anon) {
		send_response(client, LOGGED_IN, NULL);
		client->logged_in = true;
		chdir(get_server_ressources()->anon_home);
		return;
	}
	client->user = getpwnam(client->username);
	if (client->user && strcmp(pass, client->user->pw_passwd) == 0) {
		chdir(client->user->pw_dir);
		client->logged_in = true;
		send_response(client, LOGGED_IN, NULL);
		return;
	}
	send_response(client, NOT_LOGGED_IN, NULL);
}