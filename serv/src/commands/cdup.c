/*
** EPITECH PROJECT, 2018
** ftp / server
** File description:
** commands / cdup.c
*/

#include "server.h"

void cdup(client_t *client, size_t argc UNUSED, char **argv UNUSED)
{
	if (!client_is_logged_in(client))
		return;
	if (chdir("../") == 0) {
		send_response(client, FILE_ACTION_OK,
			"Directory successfully changed");
	}
	else {
		send_response(client, FILE_UNAVAILABLE, NULL);
	}
}