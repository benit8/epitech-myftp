/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands / binary.c
*/

#include "client.h"

int ftp_binary(data_t *data, size_t argc UNUSED, char **argv UNUSED)
{
	response_t *res = NULL;
	bool ok = false;

	if (not_connected(data))
		return (2);
	send_command(data, "TYPE I");
	res = response_get(data);
	ok = (res->code < 400);
	response_display(res);
	response_destroy(res);
	data->transfer_mode = ok ? BINARY : data->transfer_mode;
	return (ok ? 1 : 2);
}