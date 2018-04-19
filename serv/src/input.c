/*
** EPITECH PROJECT, 2018
** ftp / server
** File description:
** input.c
*/

#include "server.h"

char *get_input(tcp_socket_t *socket)
{}

void parse_input(char *input, client_t *client)
{
	char **args;

	input = str_trim(input);
	args = explode(input, " ");
	if (!args)
		return;
	for (size_t i = 0; commands[i].name; ++i) {
		if (strcasecmp(commands[i].name, args[0]) == 0) {
			(commands[i].func)(client, args);
			return;
		}
	}
	unknown_command(client, args);
}