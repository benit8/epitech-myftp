/*
** EPITECH PROJECT, 2018
** myftp / server
** File description:
** commands / pwd.c
*/

#include "server.h"

void pwd(client_t *client, size_t argc UNUSED, char **argv UNUSED)
{
	char buff[PATH_MAX];

	if (!client_is_logged_in(client))
		return;
	if (!getcwd(buff, sizeof(buff)))
		send_response(client, FILE_UNAVAILABLE, "Failed to get CWD");
	else {
		send_response(client, DIRECTORY_OK,
			"\"%s\" is current directory", buff);
	}
}