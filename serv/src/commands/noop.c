/*
** EPITECH PROJECT, 2018
** ftp / server
** File description:
** commands / noop.c
*/

#include "server.h"

void noop(client_t *client, size_t argc UNUSED, char **argv UNUSED)
{
	send_response(client, OK, NULL);
}