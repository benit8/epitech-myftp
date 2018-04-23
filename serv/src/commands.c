/*
** EPITECH PROJECT, 2018
** myftp / server
** File description:
** commands.c
*/

#include "server.h"

const command_t commands[] = {
	{"cdup", &cdup},
	{"cwd", &cwd},
	{"dele", &not_implemented},
	{"help", &not_implemented},
	{"list", &list},
	{"noop", &noop},
	{"pass", &pass},
	{"pasv", &pasv},
	{"port", &port},
	{"pwd", &pwd},
	{"quit", &quit},
	{"retr", &not_implemented},
	{"stor", &not_implemented},
	{"syst", &syst},
	{"type", &type},
	{"user", &user},
	{NULL, NULL}
};