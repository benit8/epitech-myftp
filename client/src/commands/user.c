/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands / user.c
*/

#include "client.h"

static int send_password(data_t *data, char *password)
{
	response_t *res = NULL;

	if (!password)
		password = prompt("Password:", true);
	send_command(data, "PASS %s", password);
	free(password);
	res = response_get(data);
	response_display(res);
	if (res->code >= 400) {
		response_destroy(res);
		printf("Login failed\n");
		return (2);
	}
	response_destroy(res);
	return (1);
}

static int send_username(data_t *data, char *username, char *password)
{
	response_t *res = NULL;

	send_command(data, "USER %s", username);
	free(username);
	res = response_get(data);
	response_display(res);
	if (res->code >= 400) {
		response_destroy(res);
		printf("Login failed\n");
		return (2);
	}
	response_destroy(res);
	return (send_password(data, password));
}

int ftp_user(data_t *data, size_t argc, char **argv)
{
	char *username = NULL;
	char *password = NULL;

	if (!connected(data))
		return (2);
	if (argc > 1)
		username = strdup(argv[1]);
	else {
		username = prompt("(username)", false);
		if (!username)
			return (2);
		else if (str_empty(username)) {
			printf("usage: user username [password]\n");
			return (2);
		}
	}
	password = (argc > 2) ? strdup(argv[2]) : NULL;
	return (send_username(data, username, password));
}