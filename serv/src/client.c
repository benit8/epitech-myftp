/*
** EPITECH PROJECT, 2018
** myFTP / server
** File description:
** client.c
*/

#include "server.h"

static char *full_address_to_string(tcp_socket_t *socket)
{
	ip_address_t ip = tcp_socket_get_remote_address(socket);
	unsigned short port = tcp_socket_get_remote_port(socket);
	char *ipstr = ip_address_to_string(ip);
	static char buffer[22];

	bzero(buffer, sizeof(buffer));
	snprintf(buffer, sizeof(buffer), "%s:%hu", ipstr, port);
	return (buffer);
}

void client_init(client_t *client, tcp_socket_t *socket)
{
	bzero(client, sizeof(client_t));
	client->control_socket = socket;
	client->data_socket = tcp_socket_bare();
	client->passive = false;
}

void client_loop(client_t *client)
{
	char *input = NULL;

	while (1) {
		input = get_input(client->control_socket);
		if (!input)
			continue;
	}
}

void client(tcp_socket_t *socket)
{
	client_t client;

	printf("Connection from %s\n", full_address_to_string(socket));
	client_init(&client, socket);
	client_loop(&client);
	printf("Disconnection %s\n", full_address_to_string(socket));
	tcp_socket_disconnect(socket);
	exit(EXIT_SUCCESS);
}