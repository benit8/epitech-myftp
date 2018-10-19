/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands / send.c
*/

#include "client.h"

static int send_file(data_t *data, int fd)
{
	socket_status_t s;
	ssize_t r;
	char buf[1];

	while (1) {
		r = read(fd, buf, 1);
		if (r <= 0)
			break;
		s = tcp_socket_send(data->data_socket, buf, 1);
		if (s == SOCKET_DISCONNECTED)
			break;
	}
	close(fd);
	close_data_channel(data);
	return (response_wait(data, true));
}

static int init_connection(data_t *data, char *action,
	char *local_file, char *remote_file)
{
	int r;
	int fd = open(local_file, O_RDONLY);

	if (fd < 0) {
		fprintf(stderr, "%s: %s\n", local_file, strerror(errno));
		free(local_file);
		free(remote_file);
		return (2);
	}
	r = init_data_channel(data);
	if (r != 1)
		return (r);
	send_command(data, "%s %s", action, remote_file);
	free(remote_file);
	r = connect_data_channel(data);
	if (r != 1)
		return (r);
	free(local_file);
	return (send_file(data, fd));
}

static char *get_arg(size_t argc, char **argv, char *prmpt, size_t pos)
{
	char *arg = NULL;

	if (argc > pos)
		arg = strdup(argv[pos]);
	else {
		arg = prompt(prmpt, false);
		if (!arg)
			return (NULL);
		else if (str_empty(arg)) {
			printf("usage: %s local-file remote-file\n", argv[0]);
			free(arg);
			return (NULL);
		}
	}
	return (arg);
}

int ftp_send(data_t *data, size_t argc, char **argv)
{
	char *remote_file = NULL;
	char *local_file = NULL;

	if (!connected(data))
		return (2);
	local_file = get_arg(argc, argv, "(local-file)", 1);
	if (!local_file)
		return (2);
	remote_file = get_arg(argc, argv, "(remote-file)", 2);
	if (!remote_file)
		return (2);
	return (init_connection(data, "STOR", local_file, remote_file));
}

int ftp_append(data_t *data, size_t argc, char **argv)
{
	char *remote_file = NULL;
	char *local_file = NULL;

	if (!connected(data))
		return (2);
	local_file = get_arg(argc, argv, "(local-file)", 1);
	if (!local_file)
		return (2);
	remote_file = get_arg(argc, argv, "(remote-file)", 2);
	if (!remote_file)
		return (2);
	return (init_connection(data, "APPE", local_file, remote_file));
}