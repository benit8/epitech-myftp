/*
** EPITECH PROJECT, 2018
** ftp / server
** File description:
** commands / port.c
*/

#include "server.h"

static void convert(client_t *client, char *data)
{
	size_t i = 0;
	size_t n = 0;
	char *h;

	for (i = 0; data[i] != '\0'; ++i) {
		if (data[i] == ',') {
			data[i] = '.';
			n++;
		}
		if (n == 4) {
			data[i++] = '\0';
			break;
		}
	}
	client->data_channel_ip = ip_address_from_string(data);
	h = &data[i];
	client->data_channel_port = strtol(h, &h, 10) * 256;
	client->data_channel_port += strtol(h + 1, NULL, 10);
}

void port(client_t *client, size_t argc, char **argv)
{
	if (!client_is_logged_in(client))
		return;
	if (argc < 2) {
		send_response(client, PARAMETERS_UNKNOWN,
			"Usage: PORT h1,h2,h3,h4,p1,p2");
		return;
	}
	convert(client, argv[1]);
	send_response(client, OK, "PORT command successful");
}