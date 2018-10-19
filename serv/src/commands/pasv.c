/*
** EPITECH PROJECT, 2018
** ftp / server
** File description:
** commands / pasv.c
*/

#include "server.h"

static char *make_infos(client_t *client)
{
	char *infos = NULL;
	char *ip = NULL;
	unsigned short port = 0;

	ip = ip_address_to_string(tcp_socket_get_remote_address(
		client->control_socket));
	port = tcp_listener_get_local_port(client->data_listener);
	asprintf(&infos, "%s,%hu,%hu", ip, port / 256, port % 256);
	for (size_t i = 0; infos[i]; ++i) {
		if (infos[i] == '.')
			infos[i] = ',';
	}
	return (infos);
}

void pasv(client_t *client, size_t argc UNUSED, char **argv UNUSED)
{
	socket_status_t s;
	char *infos = NULL;

	if (!client_is_logged_in(client))
		return;
	s = tcp_listener_listen(client->data_listener, 0, 0);
	if (s != SOCKET_DONE) {
		send_response(client, DATA_CONNECTION_UNAVAILABLE, NULL);
		return;
	}
	infos = make_infos(client);
	send_response(client, ENTERING_PASSIVE_MODE,
		"Entering passive mode (%s)", infos);
	free(infos);
	s = tcp_listener_accept(client->data_listener, &client->data_socket);
	if (s != SOCKET_DONE)
		send_response(client, DATA_CONNECTION_UNAVAILABLE, NULL);
	tcp_listener_close(client->data_listener);
}