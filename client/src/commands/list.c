/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands / list.c
*/

#include "client.h"

static char *make_command(size_t argc, char **argv)
{
	char *cmd = NULL;
	size_t length = strlen("LIST");

	for (size_t i = 1; i < argc; ++i)
		length += strlen(argv[i]) + 1;
	cmd = calloc(length + 1, sizeof(char));
	if (!cmd)
		return (NULL);
	strcpy(cmd, "LIST");
	for (size_t i = 1; i < argc; ++i) {
		strcat(cmd, " ");
		strcat(cmd, argv[i]);
	}
	return (cmd);
}

static int read_data_channel(data_t *data)
{
	socket_status_t s;
	char buf[1];
	size_t rcv = 0;

	while (1) {
		s = tcp_socket_receive(data->data_socket, buf, 1, &rcv);
		if (s == SOCKET_DISCONNECTED || rcv == 0)
			break;
		write(1, buf, 1);
	}
	close_data_channel(data);
	return (response_wait(data, true));
}

int ftp_list(data_t *data, size_t argc, char **argv)
{
	char *cmd = NULL;
	int r;

	r = init_data_channel(data);
	if (r != 1)
		return (r);
	cmd = make_command(argc, argv);
	if (!cmd)
		return (-1);
	send_command(data, cmd);
	free(cmd);
	r = connect_data_channel(data);
	if (r != 1)
		return (r);
	return (read_data_channel(data));
}