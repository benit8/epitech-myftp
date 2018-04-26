/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands / help.c
*/

#include "client.h"

static int print_all_commands(void)
{
	size_t i = 0;
	size_t j = 0;

	printf("Commands are:\n");
	while (!(commands[i].name == NULL && aliases[j].first == NULL)) {
		if (!commands[i].name)
			printf("%s\n", aliases[j++].first);
		else if (!aliases[j].first)
			printf("%s\n", commands[i++].name);
		if (!aliases[j].first ||
			strcmp(commands[i].name, aliases[j].first) < 0) {
			printf("%s\n", commands[i++].name);
		}
	}
	return (1);
}

static int print_one_command(char *cmd)
{
	for (size_t i = 0; aliases[i].first; ++i) {
		if (strcmp(cmd, aliases[i].first) == 0) {
			cmd = aliases[i].second;
			break;
		}
	}
	for (size_t i = 0; commands[i].name; ++i) {
		if (strcmp(cmd, commands[i].name) == 0) {
			printf("%s: %s\n", commands[i].name, commands[i].help);
			return (1);
		}
	}
	printf("Invalid help command %s\n", cmd);
	return (2);
}

int ftp_help(data_t *data UNUSED, size_t argc, char **argv)
{
	if (argc < 2)
		return (print_all_commands());
	else
		return (print_one_command(argv[1]));
}