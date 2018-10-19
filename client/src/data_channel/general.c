/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** data_channel / general.c
*/

#include "client.h"

int init_data_channel(data_t *data)
{
	int r;

	if (data->passive)
		r = init_data_channel_passive(data);
	else
		r = init_data_channel_active(data);
	if (r != 1)
		close_data_channel(data);
	return (r);
}

void close_data_channel(data_t *data)
{
	tcp_socket_disconnect(data->data_socket);
	tcp_listener_close(data->data_listener);
	data->data_ip = IP_NONE;
	data->data_port = 0;
}

int connect_data_channel(data_t *data)
{
	socket_status_t s;

	if (!data->passive) {
		s = tcp_listener_accept(data->data_listener,
			&data->data_socket);
		if (s != SOCKET_DONE)
			return (2);
	}
	return (response_wait(data, true));
}