/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands / cdup.c
*/

#include "client.h"

bool ftp_cdup(data_t *data, size_t argc UNUSED, char **argv UNUSED)
{
	send_command(data, "NOOP");return (false);
}