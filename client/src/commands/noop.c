/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands / noop.c
*/

#include "client.h"

int ftp_noop(data_t *data, size_t argc UNUSED, char **argv UNUSED)
{
	send_command(data, "NOOP");
	response_wait(data, true);
	return (1);
}