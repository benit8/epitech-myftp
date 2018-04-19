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

////////////////////////////////////////////////////////////////////////////////

#define UNUSED __attribute__((unused))

////////////////////////////////////////////////////////////////////////////////

typedef struct command
{
	char *name;
	void (*func)(client_t *);
} command_t;

typedef struct server_ressources
{
	tcp_listener_t *listener;
	tcp_socket_t *client;
} server_ressources_t;

typedef struct client
{
	tcp_socket_t *control_socket;
	tcp_socket_t *data_socket;
	bool passive;
} client_t;

////////////////////////////////////////////////////////////////////////////////

void client(tcp_socket_t *socket);

////////////////////////////////////////////////////////////////////////////////

extern const command_t commands[];