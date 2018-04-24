/*
** EPITECH PROJECT, 2018
** ftp / server
** File description:
** commands / list.c
*/

#include "server.h"

static char *make_command(size_t argc, char **argv)
{
	char *cmd = NULL;
	size_t length = strlen("ls -l");

	for (size_t i = 1; i < argc; ++i)
		length += strlen(argv[i]) + 1;
	cmd = calloc(length + 1, sizeof(char));
	if (!cmd)
		return (NULL);
	strcat(cmd, "ls -l");
	for (size_t i = 1; i < argc; ++i) {
		strcat(cmd, " ");
		strcat(cmd, argv[i]);
	}
	return (cmd);
}

static FILE *get_process(client_t *client, size_t argc, char **argv)
{
	FILE *pp = NULL;
	char *cmd = make_command(argc, argv);

	if (!cmd) {
		send_response(client, LOCAL_ERROR, "Out of memory");
		exit(84);
	}
	pp = popen(cmd, "r");
	free(cmd);
	if (!pp) {
		send_response(client, LOCAL_ERROR, "%s", strerror(errno));
		close_data_channel(client, false);
		return (NULL);
	}
	return (pp);
}

static void send_output(client_t *client, FILE *pp)
{
	socket_status_t s;
	char buf[1];

	while (fread(buf, sizeof(char), 1, pp) > 0) {
		if (buf[0] == '\n')
			s = tcp_socket_send(client->data_socket, "\r\n", 2);
		else
			s = tcp_socket_send(client->data_socket, buf, 1);
		if (s != SOCKET_DONE) {
			send_response(client, TRANSFER_ABORTED, NULL);
			break;
		}
	}
}

void list(client_t *client, size_t argc, char **argv)
{
	FILE *pp = NULL;

	if (!client_is_logged_in(client))
		return;
	if (!init_data_channel(client))
		return;
	pp = get_process(client, argc, argv);
	if (!pp)
		return;
	send_output(client, pp);
	pclose(pp);
	close_data_channel(client, true);
}