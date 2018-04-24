/*
** EPITECH PROJECT, 2018
** ftp / server
** File description:
** commands / retr.c
*/

#include "server.h"

static bool send_file(client_t *client, int fd)
{
	socket_status_t s;
	char buf[1];

	while (read(fd, buf, 1) > 0) {
		s = tcp_socket_send(client->data_socket, buf, 1);
		if (s == SOCKET_DISCONNECTED)
			client_disconnected(client);
		else if (s != SOCKET_DONE) {
			send_response(client, FILE_ACTION_ABORTED, NULL);
			return (false);
		}
	}
	return (true);
}

void retr(client_t *client, size_t argc, char **argv)
{
	int fd;
	struct stat buf;

	if (!client_is_logged_in(client))
		return;
	if (argc < 2) {
		send_response(client, PARAMETERS_UNKNOWN, "Usage: RETR file");
		return;
	}
	if (!init_data_channel(client))
		return;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || (fstat(fd, &buf) == -1 || !S_ISREG(buf.st_mode))) {
		send_response(client, FILE_UNAVAILABLE, "%s: %s", argv[1],
			strerror(errno));
		return;
	}
	close_data_channel(client, send_file(client, fd));
}