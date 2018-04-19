/*
** EPITECH PROJECT, 2018
** myftp / server
** File description:
** main.c
*/

#include "server.h"

static server_ressources_t *get_server_ressources(void)
{
	static server_ressources_t res;

	return (&res);
}

static void sig_handler(int signum UNUSED)
{
	server_ressources_t *res = get_server_ressources();

	printf("\nBye\n");
	tcp_socket_destroy(res->client);
	tcp_listener_destroy(res->listener);
	exit(EXIT_SUCCESS);
}

static void init(server_ressources_t *res, unsigned short port,
	const char *anonHome)
{
	res->listener = tcp_listener_create();
	if (!res->listener) {
		fprintf(stderr, "Failed to initialize server\n");
		exit(84);
	}
	res->client = tcp_socket_bare();
	if (!res->client) {
		fprintf(stderr, "Failed to initialize server\n");
		tcp_listener_destroy(res->listener);
		exit(84);
	}
	if (tcp_listener_listen(res->listener, port, IP_ANY) != SOCKET_DONE) {
		fprintf(stderr, "Could not listen to port %hu\n", port);
		tcp_listener_destroy(res->listener);
		tcp_socket_destroy(res->client);
		exit(84);
	}
	printf("Listening to port %hu...\n", port);
}

static void loop(server_ressources_t *res)
{
	socket_status_t s;
	pid_t child;

	while (1) {
		s = tcp_listener_accept(res->listener, &res->client);
		if (s != SOCKET_DONE) {
			fprintf(stderr, "Failed to accept connection\n");
			continue;
		}
		child = fork();
		if (child < 0) {
			fprintf(stderr, "Fork failed\n");
			tcp_socket_disconnect(res->client);
			continue;
		}
		if (child == 0)
			client(res->client);
		else
			tcp_socket_disconnect(res->client);
	}
}

int main(int argc, char *argv[])
{
	server_ressources_t *res = get_server_ressources();

	if (argc == 2 && regex_match("[-]{1,2}h(elp)?", argv[1]) > 0) {
		printf("USAGE: ./server port path\n\tport\tis the port number");
		printf(" on which the server socket listens\n\tpath\tis the ");
		printf("path to the home directory for the Anonymous user\n");
		return (EXIT_SUCCESS);
	}
	else if (argc < 3) {
		fprintf(stderr, "./server port anonPath\n");
		return (84);
	}
	signal(SIGINT, sig_handler);
	signal(SIGPIPE, sig_handler);
	init(res, atoi(argv[1]), argv[2]);
	loop(res);
	return (EXIT_SUCCESS);
}