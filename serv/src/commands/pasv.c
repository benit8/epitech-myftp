/*
** EPITECH PROJECT, 2018
** ftp / server
** File description:
** commands / pasv.c
*/

#include "server.h"

void pasv(client_t *client, char **args UNUSED)
{
	client->passive = !client->passive;
	printf("Passive mode %s\n", client->passive ? "On" : "Off");
}