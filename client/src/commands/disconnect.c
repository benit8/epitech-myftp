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
	tcp_listener_close(data->data_listener);
	tcp_socket_disconnect(data->data_socket);
	return (1);
}