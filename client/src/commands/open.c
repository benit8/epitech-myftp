/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands / open.c
*/

#include "client.h"

static int send_pass_command(data_t *data, response_t *res)
{
	char *pass = NULL;

	if (res->code >= 400) {
		response_destroy(res);
		return (printf("Login failed\n") ? 2 : 2);
	}
	response_destroy(res);
	pass = prompt("Password:", true);
	send_command(data, "PASS %s", pass ? pass : "");
	if (pass)
		free(pass);
	res = response_get(data);
	response_display(res);
	if (res->code >= 400) {
		response_destroy(res);
		return (printf("Login failed\n") ? 2 : 2);
	}
	response_destroy(res);
	return (1);
}

static int send_user_command(data_t *data, char *to, response_t *res)
{
	char login[32];
	char *prmpt = NULL;
	char *name = NULL;

	getlogin_r(login, 32);
	asprintf(&prmpt, "Name (%s:%s):", to, login);
	name = prompt(prmpt, false);
	free(prmpt);
	free(to);
	if (!name) {
		printf("Login failed\n");
		return (2);
	}
	if (strlen(name) == 0)
		strcpy(name, login);
	send_command(data, "USER %s", name);
	free(name);
	res = response_get(data);
	response_display(res);
	return (send_pass_command(data, res));
}

static int wait_for_response(data_t *data, char *to)
{
	response_t *res = response_get(data);

	if (!res)
		return (-1);
	if (res->code < 400)
		printf("Connected to %s\n", to);
	else
		printf("Could not connect to %s\n", to);
	response_display(res);
	response_destroy(res);
	return (send_user_command(data, to, res));
}

static int try_connecting(data_t *data, size_t argc, char **argv, char *to)
{
	data->control_ip = ip_address_from_string(to);
	if (data->control_ip == IP_NONE)
		return (printf("%s: Name or service unknown\n", to) ? 2 : 2);
	data->control_port = (argc > 2) ? atoi(argv[2]) : 21;
	if (tcp_socket_connect(data->control_socket, data->control_ip,
		data->control_port) != SOCKET_DONE) {
		data->control_ip = IP_NONE;
		data->control_port = 0;
		return (printf("connect: Connection refused\n") ? 2 : 2);
	}
	return (wait_for_response(data, to));
}

int ftp_open(data_t *data, size_t argc, char **argv)
{
	char *to = NULL;

	if (connected(data)) {
		printf("Already connected to %s, use close first\n",
			ip_address_to_string(tcp_socket_get_remote_address(
				data->control_socket)));
		return (2);
	}
	if (argc > 1)
		to = strdup(argv[1]);
	else {
		to = prompt("(to)", false);
		if (!to)
			return (2);
		else if (str_empty(to)) {
			printf("usage: %s host-name [port]\n", argv[0]);
			return (2);
		}
	}
	return (try_connecting(data, argc, argv, to));
}