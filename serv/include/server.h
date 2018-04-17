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

typedef struct server_ressources
{
	tcp_listener_t *listener;
	tcp_socket_t *client;
} server_ressources_t;