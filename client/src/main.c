/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** main.c
*/

#include "client.h"

static void sighandler(int signum UNUSED)
{
	printf("\n%s ", DEFAULT_PROMPT);
}

static int loop(data_t *data)
{
	char *input = NULL;
	int ret = 0;

	while (1) {
		input = prompt(NULL);
		if (!input)
			break;
		if (str_empty(input))
			continue;
		ret = exec_command(data, input);
		if (ret < 0)
			break;
		free(input);
	}
	printf("Bye\n");
	return (ret >= 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}

static int launch(data_t *data, int argc, char **argv)
{
	char **parts = NULL;

	if (argc > 1) {
		parts = calloc(4, sizeof(char *));
		parts[0] = "open";
		parts[1] = argv[1];
		parts[2] = argc > 2 ? argv[2] : "21";
		ftp_open(data, 3, parts);
		free(parts);
	}
	return (loop(data));
}

int main(int argc, char **argv)
{
	data_t data;

	signal(SIGINT, &sighandler);
	bzero(&data, sizeof(data));
	data.control_socket = tcp_socket_create();
	data.control_ip = IP_NONE;
	data.control_port = 0;
	data.data_listener = tcp_listener_bare();
	data.data_socket = tcp_socket_bare();
	data.data_ip = IP_NONE;
	data.data_port = 0;
	return (launch(&data, argc, argv));
}