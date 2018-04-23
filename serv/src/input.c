/*
** EPITECH PROJECT, 2018
** ftp / server
** File description:
** input.c
*/

#include "server.h"

static bool append(char **line_p, size_t *line_len_p, char *s, size_t n)
{
	char *line = NULL;
	size_t line_len = *line_len_p;

	if (n == 0) {
		if (*line_p == NULL)
			*line_p = calloc(1, sizeof(char));
		return (true);
	}
	line = realloc(*line_p, (line_len + n + 1) * sizeof(char));
	if (!line)
		return (false);
	bzero(line + line_len, n + 1);
	line_len += n;
	strncat(line, s, n);
	*line_p = line;
	*line_len_p = line_len;
	return (true);
}

static bool refill(client_t *client, char *buff, size_t *size, size_t *off)
{
	socket_status_t s;

	s = tcp_socket_receive(client->control_socket, buff, 1024, size);
	if (s == SOCKET_DISCONNECTED)
		client_disconnected(client);
	else if (s == SOCKET_ERROR)
		return (false);
	*off = 0;
	return (true);
}

char *get_input(client_t *client)
{
	static char buff[1024];
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
	for (size_t i = 0; argv[i] != NULL; ++i)
		free(argv[i]);
	free(argv);
}