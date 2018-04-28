/*
** EPITECH PROJECT, 2018
** ftp / server
** File description:
** input.c
*/

#include "server.h"

static bool append(char **line_p, size_t *line_len_p, char *s, size_t n)
{
	if (n == 0) {
		if (*line_p)
			return (true);
		*line_p = calloc(1, sizeof(char));
		if (!(*line_p)) {
			fprintf(stderr, "out of memory\n");
			return (false);
		}
	}
	*line_p = realloc(*line_p, (*line_len_p + n + 1) * sizeof(char));
	if (!(*line_p)) {
		printf("out of memory\n");
		return (false);
	}
	bzero(*line_p + *line_len_p, n + 1);
	*line_len_p += n;
	strncat(*line_p, s, n);
	return (true);
}

static bool refill(client_t *client, char *buff, size_t *size, size_t *off)
{
	socket_status_t s;

	*off = 0;
	bzero(buff, 128);
	s = tcp_socket_receive(client->control_socket, buff, 128, size);
	if (s == SOCKET_DISCONNECTED)
		client_disconnected(client);
	else if (s == SOCKET_ERROR)
		return (false);
	return (true);
}

char *get_input(client_t *client)
{
	static char buff[128];
	static size_t size = 0;
	static size_t off = 0;
	char *input = NULL;
	char *end = NULL;
	size_t len = 0;

	if ((size == 0 || off == size) && !refill(client, buff, &size, &off))
		return (NULL);
	while (1) {
		end = strstr(buff + off, "\r\n");
		if (end) {
			append(&input, &len, buff + off, end - (buff + off));
			off += end - (buff + off) + 2;
			return (input);
		}
		append(&input, &len, buff + off, size - off);
		if (!refill(client, buff, &size, &off))
			return (input);
	}
}

void parse_input(char *input, client_t *client)
{
	bool done = false;
	char **argv;
	size_t argc = 0;

	input = str_trim(input);
	argv = explode(input, " ");
	if (!argv)
		return;
	for (argc = 0; argv[argc]; ++argc);
	for (size_t i = 0; commands[i].name != NULL && !done; ++i) {
		if (strcasecmp(commands[i].name, argv[0]) == 0) {
			(commands[i].func)(client, argc, argv);
			done = true;
		}
	}
	if (!done)
		unknown_command(client, argc, argv);
	strcpy(client->last_command, argv[0]);
	for (size_t i = 0; argv[i] != NULL; ++i)
		free(argv[i]);
	free(argv);
}