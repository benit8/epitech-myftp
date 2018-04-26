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
	client->data_listener = tcp_listener_bare();
	client->data_socket = tcp_socket_bare();
	client->data_channel_ip = IP_NONE;
}

void client_loop(client_t *client)
{
	char *input = NULL;

	send_response(client, SERVICE_READY, "myFTP server");
	while (1) {
		input = get_input(client);
		if (!input)
			break;
		if (str_empty(input)) {
			unknown_command(client, 0, NULL);
			free(input);
			continue;
		}
#ifdef DEBUG
		printf("%40s%s\n", " ", input);
#endif
		parse_input(input, client);
		free(input);
	}
}

void client(tcp_socket_t *socket)
{
	client_t client;

	printf("-- Connection from %s\n", full_address_to_string(socket));
	client_init(&client, socket);
	client_loop(&client);
	printf("-- Disconnection %s\n", full_address_to_string(socket));
	tcp_socket_destroy(client.control_socket);
	tcp_socket_destroy(client.data_socket);
	exit(EXIT_SUCCESS);
}

void client_disconnected(client_t *client)
{
	printf("-- Disconnection %s\n",
		full_address_to_string(client->control_socket));
	tcp_socket_destroy(client->control_socket);
	tcp_socket_destroy(client->data_socket);
	tcp_listener_destroy(client->data_listener);
	exit(EXIT_FAILURE);
}