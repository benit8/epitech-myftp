/*
** EPITECH PROJECT, 2018
** myftp / server
** File description:
** server.h
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "cnet/tcp_listener.h"
#include "cnet/tcp_socket.h"
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
	const char anon_home;
} server_ressources_t;

typedef struct client
{
	tcp_socket_t *control_socket;
	tcp_socket_t *data_socket;
	bool passive;
} client_t;

typedef struct command
{
	char *name;
	void (*func)(client_t *, char **);
} command_t;

////////////////////////////////////////////////////////////////////////////////

void client(tcp_socket_t *socket);

char *get_input(tcp_socket_t *control_socket);
void parse_input(char *input, client_t *client);

// Commands

void unknown_command(client_t *client, char **args);
void pasv(client_t *client, char **args);

////////////////////////////////////////////////////////////////////////////////

extern const command_t commands[];