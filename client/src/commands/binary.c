/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands / binary.c
*/

#include "client.h"

bool ftp_binary(data_t *data, size_t argc UNUSED, char **argv UNUSED)
{
	send_command(data, "NOOP");return (false);
}