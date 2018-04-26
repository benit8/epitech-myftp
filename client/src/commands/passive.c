/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** commands / passive.c
*/

#include "client.h"

int ftp_passive(data_t *data, size_t argc UNUSED, char **argv UNUSED)
{
	data->passive = !data->passive;
	printf("Passive mode %s\n", data->passive ? "on" : "off");
	return (1);
}