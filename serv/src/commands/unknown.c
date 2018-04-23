/*
** EPITECH PROJECT, 2018
** ftp / serv
** File description:
** commands / unknown.c
*/

#include "server.h"

void unknown_command(client_t *client, size_t argc UNUSED, char **argv UNUSED)
{
	send_response(client, COMMAND_UNKNOWN, NULL);
}

void not_implemented(client_t *client, size_t argc UNUSED, char **argv UNUSED)
{
	send_response(client, COMMAND_NOT_IMPLEMENTED, NULL);
}