/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** response.c
*/

#include "client.h"

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

static bool refill(data_t *data, char *buff, size_t *size, size_t *off)
{
	socket_status_t s;

	s = tcp_socket_receive(data->control_socket, buff, 1024, size);
	if (s == SOCKET_DISCONNECTED)
		return (false);
	else if (s == SOCKET_ERROR)
		return (false);
	*off = 0;
	return (true);
}

static char *get_raw_response(data_t *data)
{
	static char buff[1024];
	static size_t size = 0;
	static size_t off = 0;
	char *input = NULL;
	char *end = NULL;
	size_t len = 0;

	if ((size == 0 || off == size) && !refill(data, buff, &size, &off))
		return (NULL);
	while (1) {
		end = strstr(buff + off, "\r\n");
		if (end) {
			append(&input, &len, buff + off, end - (buff + off));
			off += end - (buff + off) + 2;
			return (input);
		}
		append(&input, &len, buff + off, size - off);
		if (!refill(data, buff, &size, &off))
			return (input);
	}
}

response_t *get_response(data_t *data)
{
	response_t *res = NULL;
	char *raw = get_raw_response(data);
	char *r = raw;

	if (!raw)
		return (NULL);
	res = calloc(1, sizeof(response_t));
	if (!res) {
		free(raw);
		return (NULL);
	}
	res->code = strtol(raw, &r, 10);
	res->message = strdup(r);
	if (!res->message) {
		free(res);
		free(raw);
		return (NULL);
	}
	res->message = str_trim(res->message);
	return (res);
}

void response_destroy(response_t *res)
{
	free(res->message);
	free(res);
}