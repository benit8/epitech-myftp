/*
** EPITECH PROJECT, 2018
** ftp / server
** File description:
** commands / list.c
*/

#include "server.h"

void list(client_t *client, size_t argc UNUSED, char **argv UNUSED)
{
	FILE *pp;
	char buf[1];

	if (!init_data_connection(client))
		return;
	pp = popen("ls -l", "r");
	while (fread(buf, sizeof(char), 1, pp) > 0) {
		if (*buf == '\n')
			tcp_socket_send(client->data_socket, "\r\n", 2);
		else
			tcp_socket_send(client->data_socket, buf, 1);
	}
	pclose(pp);
	close_data_connection(client);
}