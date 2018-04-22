/*
** EPITECH PROJECT, 2018
** myftp / server
** File description:
** commands.c
*/

#include "server.h"

const command_t commands[] = {
	{"user", &user},
	{"pass", &pass},
	{"cwd", &not_implemented},
	{"cdup", &not_implemented},
	{"quit", &quit},
	{"dele", &not_implemented},
	{"pwd", &pwd},
	{"pasv", &pasv},
	{"port", &not_implemented},
	{"help", &not_implemented},
	{"noop", &not_implemented},
	{"retr", &not_implemented},
	{"stor", &not_implemented},
	{"list", &not_implemented},

	{"syst", &syst},

	{NULL, NULL}
};