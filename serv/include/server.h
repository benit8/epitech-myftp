/*
** EPITECH PROJECT, 2018
** myftp / server
** File description:
** server.h
*/

#pragma once
#define _GNU_SOURCE

////////////////////////////////////////////////////////////////////////////////

#include <limits.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "cnet/tcp_listener.h"
#include "cnet/tcp_socket.h"
#include "cnet/ftp.h"
#include "my/regex.h"
#include "my/string.h"

////////////////////////////////////////////////////////////////////////////////

#define UNUSED __attribute__((unused))

////////////////////////////////////////////////////////////////////////////////

typedef struct server_ressources
{
	tcp_listener_t *listener;
	tcp_socket_t *client;
	unsigned short port;
	char *anon_home;
} server_ressources_t;

typedef struct client
{
	tcp_socket_t *control_socket;
	tcp_socket_t *data_socket;
	char name[256];
} client_t;

typedef struct command
{
	char *name;
	void (*func)(client_t *, char **);
} command_t;

typedef struct status_string
{
	ftp_status_t status;
	char *string;
} status_string_t;

typedef struct user
{
	char *name;
	char *pass;
} user_t;

////////////////////////////////////////////////////////////////////////////////

void client(tcp_socket_t *socket);
void client_disconnected(client_t *client);

char *get_input(client_t *client);
void parse_input(char *input, client_t *client);

char *ftp_status_as_strings(ftp_status_t s);

bool send_response(client_t *client, ftp_status_t status, char *fmt, ...);

// Commands

void unknown_command(client_t *client, char **args);
void not_implemented(client_t *client, char **args UNUSED);

void pass(client_t *client, char **args);
void pasv(client_t *client, char **args);
void pwd(client_t *client, char **args);
void quit(client_t *client, char **args);
void syst(client_t *client, char **args);
void user(client_t *client, char **args);

////////////////////////////////////////////////////////////////////////////////

extern const command_t commands[];
extern const status_string_t status_strings[];
extern const user_t users[];