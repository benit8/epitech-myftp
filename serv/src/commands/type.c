/*
** EPITECH PROJECT, 2018
** ftp / server
** File description:
** commands / type.c
*/

#include "server.h"

static const transfer_type_t transfer_types[] = {
	{"A", false},
	{"I", true},
	{NULL, false}
};

void type(client_t *client, size_t argc, char **argv)
{
	if (argc < 2) {
		send_response(client, PARAMETERS_UNKNOWN, "Usage: TYPE type");
		return;
	}
	for (size_t i = 0; transfer_types[i].flag; ++i) {
		if (strcasecmp(argv[1], transfer_types[i].flag) == 0) {
			client->binary = transfer_types[i].binary;
			send_response(client, OK, NULL);
			return;
		}
	}
	send_response(client, PARAMETERS_UNKNOWN, "%s: Unknown mode", argv[1]);
}