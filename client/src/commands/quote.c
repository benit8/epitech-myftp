/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands / quote.c
*/

#include "client.h"

bool ftp_quote(data_t *data, size_t argc UNUSED, char **argv UNUSED)
{
	send_command(data, "NOOP");return (false);
}