/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** data_channel / active.c
*/

#include "client.h"

int init_data_channel_active(data_t *data)
{
	socket_status_t s;
	char *param = NULL;

	s = tcp_listener_listen(data->data_listener, 0, IP_ANY);
	if (s != SOCKET_DONE)
		return (2);
	data->data_ip = tcp_socket_get_remote_address(data->control_socket);
	data->data_port = tcp_listener_get_local_port(data->data_listener);
	asprintf(&param, "%s,%hu,%hu",
		ip_address_to_string(data->data_ip),
		data->data_port / 256, data->data_port % 256);
	if (!param) {
		close_data_channel(data);
		return (-1);
	}
	for (size_t i = 0; param[i]; ++i)
		param[i] = (param[i] == '.') ? ',' : param[i];
	send_command(data, "PORT %s", param);
	free(param);
	return (response_wait(data, true));
}