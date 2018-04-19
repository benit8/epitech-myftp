/*
** EPITECH PROJECT, 2018
** myftp / server
** File description:
** commands.c
*/

#include "server.h"

const command_t commands[] = {
	{"pasv", &pasv},
	{NULL, NULL}
};