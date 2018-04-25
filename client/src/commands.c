/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands.c
*/

#include "client.h"

const command_t commands[] = {
	{"append", &ftp_append, "append to a file"},
	{"ascii", &ftp_ascii, "set ascii transfer type"},
	{"binary", &ftp_binary, "set binary transfer type"},
	{"cd", &ftp_cd, "change remote working directory"},
	{"cdup", &ftp_cdup,
		"change remote working directory to parent directory"},
	{"delete", &ftp_delete, "delete remote file"},
	{"debug", &ftp_debug, "toggle/set debugging mode"},
	{"disconnect", &ftp_disconnect, "terminate ftp session"},
	{"exit", &ftp_exit, "terminate ftp session and exit"},
	{"help", &ftp_help, "print local help information"},
	{"lcd", &ftp_lcd, "change local working directory"},
	{"list", &ftp_list, "list contents of remote directory"},
	{"mkdir", &ftp_mkdir, "make directory on the remote machine"},
	{"noop", &ftp_noop, "keeps the connection alive"},
	{"open", &ftp_open, "connect_to_remote_ftp"},
	{"passive", &ftp_passive, "toggle passive mode"},
	{"pwd", &ftp_pwd, "print working directory on remote machine"},
	{"quote", &ftp_quote, "send arbitrary ftp command"},
	{"recv", &ftp_recv, "receive file"},
	{"rename", &ftp_rename, "rename file"},
	{"rmdir", &ftp_rmdir, "remove directory on the remove machine"},
	{"send", &ftp_send, "send one file"},
	{NULL, NULL, NULL}
};

const size_t command_count = sizeof(commands) / sizeof(*commands);

const pair_t aliases[] = {
	{"?", "help"},
	{"bye", "exit"},
	{"close", "disconnect"},
	{"dir", "list"},
	{"get", "recv"},
	{"image", "binary"},
	{"ls", "list"},
	{"put", "send"},
	{"quit", "exit"},
	{NULL, NULL}
};

static size_t find_command(char *cmd)
{
	for (size_t i = 0; aliases[i].first; ++i) {
		if (strcmp(aliases[i].first, cmd) == 0) {
			cmd = aliases[i].second;
			break;
		}
	}
	for (size_t i = 0; commands[i].name != NULL; ++i) {
		if (strcmp(commands[i].name, cmd) == 0)
			return (i);
	}
	return ((size_t)-1);
}

int exec_command(data_t *data, char *input)
{
	bool done = false;
	char **argv = NULL;
	size_t argc = 0;
	size_t i = 0;

	input = str_trim(input);
	argv = explode(input, " ");
	if (!argv)
		return (-1);
	for (argc = 0; argv[argc]; ++argc);
	i = find_command(argv[0]);
	if (i == (size_t)-1)
		printf("%s: Invalid command\n", argv[0]);
	else
		done = (commands[i].func)(data, argc, argv);
	for (size_t i = 0; argv[i] != NULL; ++i)
		free(argv[i]);
	free(argv);
	return ((int)done);
}

void send_command(data_t *data, char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vdprintf(data->control_socket->handle, fmt, ap);
	dprintf(data->control_socket->handle, "\r\n");
	va_end(ap);
}