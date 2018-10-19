/*
** EPITECH PROJECT, 2018
** ftp / server
** File description:
** commands / stor.c
*/

#include "server.h"

static bool sync_file(client_t *client, int fd, bool ok)
{
	if (!ok)
		return (false);
	if (fsync(fd) < 0) {
		send_response(client, INSUFFICIENT_STORAGE_SPACE, NULL);
		return (false);
	}
	return (true);
}

static bool receive_file(client_t *client, int fd)
{
	socket_status_t s;
	size_t r = 0;
	char buf[1];
	bool ok = true;

	while (ok) {
		s = tcp_socket_receive(client->data_socket, buf, 1, &r);
		if (r == 0)
			break;
		else if (s == SOCKET_ERROR) {
			send_response(client, TRANSFER_ABORTED, NULL);
			ok = false;
		}
		if (write(fd, buf, 1) < 0) {
			send_response(client, LOCAL_ERROR, NULL);
			ok = false;
		}
	}
	return (sync_file(client, fd, ok));
}

void stor(client_t *client, size_t argc, char **argv)
{
	if (!client_is_logged_in(client))
		return;
	if (argc < 2) {
		send_response(client, PARAMETERS_UNKNOWN, "Usage: STOR file");
		return;
	}
	if (!init_data_channel(client))
		return;
	int fd = open(argv[1], O_WRONLY | O_CREAT, 0644);
	if (fd < 0) {
		send_response(client, FILE_UNAVAILABLE, "%s: %s", argv[1],
			strerror(errno));
		return;
	}
	close_data_channel(client, receive_file(client, fd));
	close(fd);
}