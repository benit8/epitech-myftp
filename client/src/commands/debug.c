/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands / debug.c
*/

#include "client.h"

int ftp_debug(data_t *data, size_t argc, char **argv)
{
	int d = 0;

	if (argc < 2)
		data->debug = !data->debug;
	else {
		d = atoi(argv[1]);
		if (d < 0) {
			printf("%s: bad debugging value\n", argv[1]);
			return (2);
		}
		data->debug = d;
	}
	printf("Debugging %s (debug=%d)\n", data->debug ? "on" : "off",
		data->debug);
	return (1);
}