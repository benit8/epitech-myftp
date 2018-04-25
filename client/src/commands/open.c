/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands / open.c
*/

#include "client.h"

bool ftp_open(data_t *data, size_t argc, char **argv)
{
	char *to = NULL;

	if (data->control_socket->handle != -1) {
		printf("Already connected to %s, use close first\n",
			ip_address_to_string(tcp_socket_get_remote_address(
				data->control_socket)));
		return (false);
	}
	if (argc > 1)
		to = argv[1];
	else {
		to = prompt("(to)");
		if (!to)
			return (false);
	}
	data->control_ip = ip_address_from_string(to);
	if (data->control_ip == IP_NONE) {
		printf("%s: Name or service unknown\n", to);
		return (false);
	}
	data->control_port = (argc > 2) ? atoi(argv[2]) : 21;
	if (tcp_socket_connect(data->control_socket, data->control_ip,
		data->control_port) == -1) {
		printf("connect: Connection refused\n");
		data->control_ip = IP_NONE;
		data->control_port = 0;
		return (false);
	}
	return (false);
}