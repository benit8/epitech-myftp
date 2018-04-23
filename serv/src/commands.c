/*
** EPITECH PROJECT, 2018
** myftp / server
** File description:
** commands.c
*/

#include "server.h"

const command_t commands[] = {
	{"cdup", &cdup, "CDUP",
		"Change working directory to parent directory"},
	{"cwd", &cwd, "CWD path",
		"Change working directory"},
	{"dele", &dele, "DELE remote-file",
		"Delete file on server"},
	{"help", &help, "HELP [command]",
		"List available commands"},
	{"list", &list, "LIST",
		"List files in the current working directory"},
	{"noop", &noop, "NOOP",
		"Do nothing (prevent timeout)"},
	{"pass", &pass, "PASS password",
		"Specify password for authentification"},
	{"pasv", &pasv, "PASV",
		"Enable \"passive\" mode for data transfer"},
	{"port", &port, "PORT h1,h2,h3,h4,p1,p2",
		"Enable \"active\" mode for data transfer"},
	{"pwd", &pwd, "PWD",
		"Print working directory"},
	{"quit", &quit, "QUIT",
		"Disconnection"},
	{"retr", &retr, "RETR remote-file",
		"Download file from server to client"},
	{"stor", &stor, "STOR local-file",
		"Upload file from client to server"},
	{"syst", &syst, "SYST",
		"Print system type"},
	{"type", &type, "TYPE type",
		"Change transfer type [A/I]"},
	{"user", &user, "USER username",
		"Specify username for authentification"},
	{NULL, NULL, NULL, NULL}
};

const size_t command_count = sizeof(commands) / sizeof(*commands);