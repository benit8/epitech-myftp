/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands / recv.c
*/

#include "client.h"

static int get_file(data_t *data, int fd)
{
	socket_status_t s;
	size_t rcv;
	char buf[1];

	while (1) {
		s = tcp_socket_receive(data->data_socket, buf, 1, &rcv);
		if (s == SOCKET_DISCONNECTED || rcv == 0)
			break;
		write(fd, buf, 1);
	}
	close(fd);
	close_data_channel(data);
	return (response_wait(data, true));
}

static int init_connection(data_t *data, char *remote_file, char *local_file)
{
	int r;
	int fd;

	r = init_data_channel(data);
	if (r != 1)
		return (r);
	send_command(data, "RETR %s", remote_file);
	free(remote_file);
	r = connect_data_channel(data);
	if (r != 1)
		return (r);
	fd = open(local_file, O_WRONLY | O_CREAT, 0644);
	if (fd < 0) {
		fprintf(stderr, "%s: %s\n", local_file, strerror(errno));
		close_data_channel(data);
		free(local_file);
		return (2);
	}
	free(local_file);
	return (get_file(data, fd));
}

int ftp_recv(data_t *data, size_t argc, char **argv)
{
	char *remote_file = NULL;
	char *local_file = NULL;

	if (!connected(data))
		return (2);
	if (argc > 1)
		remote_file = strdup(argv[1]);
	else {
		remote_file = prompt("(remote-file)", false);
		if (!remote_file)
			return (2);
		else if (str_empty(remote_file)) {
			printf("usage: %s remote-file [local-file]\n", argv[0]);
			free(remote_file);
			return (2);
		}
	}
	local_file = strdup(argc > 2 ? argv[2] : remote_file);
	return (init_connection(data, remote_file, local_file));
}