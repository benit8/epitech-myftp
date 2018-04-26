/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** connection.c
*/

#include "client.h"

bool connected(data_t *data)
{
	return (tcp_socket_get_remote_address(data->control_socket) != IP_NONE);
}

bool not_connected(data_t *data)
{
	bool c = connected(data);

	if (!c)
		printf("Not connected.\n");
	return (!c);
}