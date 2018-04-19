/*
** EPITECH PROJECT, 2018
** ftp / serv
** File description:
** commands / unknown.c
*/

#include "server.h"

void unknown_commands(client_t *client, char **args UNUSED)
{
	send_response(client->control_socket, COMMAND_UNKNOWN, NULL);
}