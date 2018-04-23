/*
** EPITECH PROJECT, 2018
** myftp / server
** File description:
** transfer.c
*/

#include "server.h"

bool init_data_connection(client_t *client)
{
	socket_status_t s;

	if (client->data_socket->handle != -1)
		return (true);
	s = tcp_socket_connect(client->data_socket, client->data_channel_ip,
		client->data_channel_port);
	if (s != SOCKET_DONE) {
		send_response(client, DATA_CONNECTION_UNAVAILABLE, NULL);
		return (false);
	}
	return (true);
}