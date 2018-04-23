/*
** EPITECH PROJECT, 2018
** myftp / server
** File description:
** commands / quit.c
*/

#include "server.h"

void quit(client_t *client, size_t argc UNUSED, char **argv UNUSED)
{
	send_response(client, CLOSING_CONNECTION, "Bye");
	client_disconnected(client);
}