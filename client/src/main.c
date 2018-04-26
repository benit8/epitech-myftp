/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** main.c
*/

#include "client.h"

static void sighandler(int signum UNUSED)
{
	char *prmpt = prompt_ctl(0, NULL);

	write(1, "\n", 1);
	write(1, prmpt, strlen(prmpt));
	write(1, " ", 1);
}

static void destroy(data_t *data)
{
	tcp_socket_destroy(data->control_socket);
	tcp_listener_destroy(data->data_listener);
	tcp_socket_destroy(data->data_socket);
}

static int loop(data_t *data)
{
	char *input = NULL;
	int ret = 0;

	while (1) {
		input = prompt(NULL, false);
		if (!input)
			break;
		if (str_empty(input)) {
			free(input);
			continue;
		}
		ret = exec_command(data, input);
		free(input);
		if (ret <= 0)
			break;
	}
	destroy(data);
	return (ret >= 0 ? EXIT_SUCCESS : 84);
}

static int launch(data_t *data, int argc, char **argv)
{
	char **parts = NULL;

	if (argc > 1) {
		parts = alloca(3 * sizeof(char *));
		parts[0] = "open";
		parts[1] = argv[1];
		parts[2] = argc > 2 ? argv[2] : "21";
		if (ftp_open(data, 3, parts) < 0)
			return (84);
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
	data.passive = false;
	data.debug = 0;
	data.transfer_mode = BINARY;
	return (launch(&data, argc, argv));
}