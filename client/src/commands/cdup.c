/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands / cdup.c
*/

#include "client.h"

int ftp_cdup(data_t *data, size_t argc UNUSED, char **argv UNUSED)
{
	if (!connected(data))
		return (2);
	send_command(data, "CDUP");
	return (response_wait(data, true));
}