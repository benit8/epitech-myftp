/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands / lcd.c
*/

#include "client.h"

int ftp_lcd(data_t *data UNUSED, size_t argc, char **argv)
{
	if (argc < 2) {
		printf("usage: cd local-dir\n");
		return (2);
	}
	if (chdir(argv[1]) == -1) {
		printf("%s: %s\n", argv[1], strerror(errno));
		return (2);
	}
	return (1);
}