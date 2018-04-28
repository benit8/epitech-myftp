/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands / disconnect.c
*/

#include "client.h"

int ftp_disconnect(data_t *data, size_t argc UNUSED, char **argv UNUSED)
{
	if (!connected(data))
		return (0);
	send_command(data, "QUIT");
	response_wait(data, true);
	tcp_socket_disconnect(data->control_socket);
	data->control_ip = IP_NONE;
	data->control_port = 0;
	tcp_listener_close(data->data_listener);
	tcp_socket_disconnect(data->data_socket);
	data->data_ip = IP_NONE;
	data->data_port = 0;
	return (1);
}