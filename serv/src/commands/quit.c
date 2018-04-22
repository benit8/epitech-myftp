/*
** EPITECH PROJECT, 2018
** myftp / server
** File description:
** commands / quit.c
*/

#include "server.h"

void quit(client_t *client, char **args UNUSED)
{
	if (args[1])
		send_response(client, PARAMETERS_UNKNOWN, NULL);
	else {
		send_response(client, CLOSING_CONNECTION, "Bye");
		client_disconnected(client);
	}
}