/*
** EPITECH PROJECT, 2018
** ftp / server
** File description:
** commands / stor.c
*/

#include "server.h"

void stor(client_t *client, size_t argc, char **argv)
{
	send_response(client, OK, NULL);
}