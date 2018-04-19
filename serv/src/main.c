/*
** EPITECH PROJECT, 2018
** myftp / server
** File description:
** main.c
*/

#include "server.h"

static void sig_handler(int signum UNUSED)
{
	server_ressources_t *res = sresctl();

	printf("\nBye\n");
	tcp_socket_destroy(res->client);
	tcp_listener_destroy(res->listener);
	exit(EXIT_SUCCESS);
}

static server_ressources_t *sresctl(void)
{
	static server_ressources_t res;

	return (&res);
}

int main(int argc, char const **argv)
{
	if (argc < 2) {
		fprintf(stderr, "./server port\n");
		return (1);
	}

	signal(SIGINT, sig_handler);
	signal(SIGPIPE, sig_handler);

	server_ressources_t *res = sresctl();
	unsigned short port = atoi(argv[1]);
	res->listener = tcp_listener_create();
	if (tcp_listener_listen(res->listener, port, IP_ANY) != SOCKET_DONE) {
		fprintf(stderr, "Could not listen to port %hu\n", port);
		return (EXIT_FAILURE);
	}
	printf("Listening to port %hu...\n", port);

	res->client = tcp_socket_bare();
	while (1) {
		if (tcp_listener_accept(res->listener, &res->client) != SOCKET_DONE) {
			fprintf(stderr, "Failed to accept connection\n");
			continue;
		}

		pid_t child = fork();
		if (child == 0)
			client(res->client);
		tcp_socket_disconnect(res->client);
	}

	return (EXIT_SUCCESS);
}