/*
** EPITECH PROJECT, 2018
** myftp / server
** File description:
** data_channel.c
*/

#include "server.h"

bool init_data_channel(client_t *client)
{
	socket_status_t s;

	if (client->data_socket->handle != -1) {
		send_response(client, OPENING_DATA_CONNECTION, NULL);
		return (true);
	}
	else if (client->data_channel_ip == IP_NONE ||
		client->data_channel_port == 0) {
		send_response(client, DATA_CONNECTION_UNAVAILABLE, NULL);
		return (false);
	}
	s = tcp_socket_connect(client->data_socket, client->data_channel_ip,
		client->data_channel_port);
	if (s != SOCKET_DONE) {
		send_response(client, DATA_CONNECTION_UNAVAILABLE, NULL);
		return (false);
	}
	send_response(client, OPENING_DATA_CONNECTION, NULL);
	return (true);
}

void close_data_channel(client_t *client, bool ok)
{
	if (ok)
		send_response(client, CLOSING_DATA_CONNECTION, NULL);
	tcp_socket_disconnect(client->data_socket);
	tcp_listener_close(client->data_listener);
	client->data_channel_ip = IP_NONE;
	client->data_channel_port = 0;
}