/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** response.c
*/

#include "client.h"

static bool append(char **line_p, size_t *line_len_p, char *s, size_t n)
{
	if (n == 0) {
		if (*line_p)
			return (true);
		*line_p = calloc(1, sizeof(char));
		if (!(*line_p)) {
			printf("out of memory\n");
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

response_t *response_get(data_t *data)
{
	response_t *res = calloc(1, sizeof(response_t));
	char *r = NULL;

	if (!res)
		return (NULL);
	res->raw = get_raw_response(data);
	if (!res->raw) {
		free(res);
		return (NULL);
	}
	res->code = strtol(res->raw, &r, 10);
	res->message = str_trim(r);
	return (res);
}

void response_destroy(response_t *res)
{
	free(res->raw);
	free(res);
}