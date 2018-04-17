/*
** EPITECH PROJECT, 2018
** myftp / server
** File description:
** main.c
*/

#include "server.h"

#define UNUSED __attribute__((unused))
#define SOCKSTRADDR(s) ip_address_to_string(tcp_socket_get_remote_address(s))

tcp_listener_t *listener = NULL;

static server_ressources_t *sresctl(void)
{
	static server_ressources_t res;

	return (&res);
}

void sig_handler(int signum UNUSED)
{
	printf("\nBye\n");
	tcp_socket_destroy((sresctl())->client);
	tcp_listener_destroy((sresctl())->listener);
	exit(EXIT_SUCCESS);
}

void client_process(tcp_socket_t *socket)
{
	printf("Connection from %s:%hu\n", SOCKSTRADDR(socket), tcp_socket_get_remote_port(socket));
	sleep(3);
	printf("Disconnection %s:%hu\n", SOCKSTRADDR(socket), tcp_socket_get_remote_port(socket));
	tcp_socket_disconnect(socket);
	exit(EXIT_SUCCESS);
}

int main(int argc, char const **argv)
{
	if (argc < 2) {
		fprintf(stderr, "./server port\n");
		return (1);
	}

	signal(SIGINT, sig_handler);
	signal(SIGPIPE, sig_handler);

	unsigned short port = atoi(argv[1]);
	(sresctl())->listener = tcp_listener_create();
	if (tcp_listener_listen((sresctl())->listener, port, IP_ANY) != SOCKET_DONE) {
		fprintf(stderr, "Could not listen to port %hu\n", port);
		return (EXIT_FAILURE);
	}
	printf("Listening to port %hu...\n", port);

	(sresctl())->client = tcp_socket_bare();
	while (1) {
		if (tcp_listener_accept((sresctl())->listener, &(sresctl())->client) != SOCKET_DONE) {
			fprintf(stderr, "Failed to accept connection\n");
			continue;
		}

		pid_t child = fork();
		if (child == 0)
			client_process((sresctl())->client);

		tcp_socket_disconnect((sresctl())->client);
	}

	return (EXIT_SUCCESS);
}