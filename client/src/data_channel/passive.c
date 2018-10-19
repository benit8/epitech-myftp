/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** data_channel / passive.c
*/

#include "client.h"

static void convert(data_t *data, char *raw)
{
	size_t i = 0;
	size_t n = 0;
	char *h;

	for (i = 0; raw[i] != '\0'; ++i) {
		if (raw[i] == ',') {
			raw[i] = '.';
			n++;
		}
		if (n == 4) {
			raw[i++] = '\0';
			break;
		}
	}
	data->data_ip = ip_address_from_string(raw);
	h = &raw[i];
	data->data_port = strtol(h, &h, 10) * 256;
	data->data_port += strtol(h + 1, NULL, 10);
}

static bool translate(data_t *data, char *message)
{
	char **matches = regex_capture(REGEX_IPPORT, message);

	if (!matches || matches[0] == NULL) {
		if (matches)
			free(matches);
		return (false);
	}
	convert(data, matches[0]);
	free(matches[0]);
	free(matches);
	return (true);
}

int init_data_channel_passive(data_t *data)
{
	socket_status_t s;
	response_t *res = NULL;

	send_command(data, "PASV");
	res = response_get(data);
	response_display(res);
	if (res->code >= 400) {
		response_destroy(res);
		return (2);
	}
	if (!translate(data, res->message))
		return (-1);
	response_destroy(res);
	s = tcp_socket_connect(data->data_socket, data->data_ip,
		data->data_port);
	return (s == SOCKET_DONE ? 1 : 2);
}