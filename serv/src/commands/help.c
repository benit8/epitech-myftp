/*
** EPITECH PROJECT, 2018
** ftp / server
** File description:
** commands / help.c
*/

#include "server.h"

static void all_commands(client_t *client)
{
	char buf[command_count * 6];

	bzero(buf, sizeof(buf));
	for (size_t i = 0; commands[i].name; ++i) {
		if (i > 0)
			strcat(buf, " ");
		strcat(buf, commands[i].name);
	}
	send_response(client, HELP_MESSAGE, "Available commands: %s", buf);
}

static void one_command(client_t *client, char *cmd)
{
	size_t i = 0;

	for (; commands[i].name && strcasecmp(commands[i].name, cmd) != 0; ++i);
	if (!commands[i].name)
		send_response(client, HELP_MESSAGE, "%s: Invalid command", cmd);
	else {
		send_response(client, HELP_MESSAGE, "%s\r\n%s",
			commands[i].usage, commands[i].help);
	}
}

void help(client_t *client, size_t argc, char **argv)
{
	if (argc > 1)
		one_command(client, argv[1]);
	else
		all_commands(client);
}