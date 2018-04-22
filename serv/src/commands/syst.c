/*
** EPITECH PROJECT, 2018
** myftp / server
** File description:
** commands / syst.c
*/

#include "server.h"

void syst(client_t *client, char **args UNUSED)
{
	send_response(client, SYSTEM_TYPE, "UNIX Type: L8");
}