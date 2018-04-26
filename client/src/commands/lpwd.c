/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands / lpwd.c
*/

#include "client.h"

int ftp_lpwd(data_t *data UNUSED, size_t argc UNUSED, char **argv UNUSED)
{
	char buff[PATH_MAX];

	if (!getcwd(buff, sizeof(buff))) {
		printf("Failed to get CWD\n");
		return (0);
	}
	else {
		printf("%s\n", buff);
		return (1);
	}
}