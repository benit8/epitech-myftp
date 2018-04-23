/*
** EPITECH PROJECT, 2018
** ftp / server
** File description:
** response.c
*/

#include "server.h"

bool finish_response(client_t *client, char *buffer, char *fmt, char *msg)
{
	socket_status_t s;

	s = tcp_socket_send(client->control_socket, buffer, strlen(buffer));
	free(buffer);
	if (fmt)
		free(msg);
	if (s == SOCKET_DISCONNECTED)
		client_disconnected(client);
	return (s == SOCKET_DONE);
}

bool send_response(client_t *client, ftp_status_t status, char *fmt, ...)
{
	char *buffer = NULL;
	char *msg = NULL;
	va_list ap;

	if (!fmt)
		msg = ftp_status_as_strings(status);
	else {
		va_start(ap, fmt);
		vasprintf(&msg, fmt, ap);
		va_end(ap);
	}
	asprintf(&buffer, "%d %s\r\n", status, msg);
	if (!buffer) {
		fprintf(stderr, "out of memory\n");
		exit(84);
	}
#ifdef DEBUG
	printf("< %s", buffer);
#endif
	return (finish_response(client, buffer, fmt, msg));
}

bool client_is_logged_in(client_t *client)
{
	if (!client->logged_in)
		send_response(client, COMMAND_UNKNOWN, NULL);
	return (client->logged_in);
}