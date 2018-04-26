/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands / pwd.c
*/

#include "client.h"

int ftp_pwd(data_t *data, size_t argc UNUSED, char **argv UNUSED)
{
	send_command(data, "PWD");
	return (response_wait(data, true));
}