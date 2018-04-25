/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** client.h
*/

#pragma once
#define _GNU_SOURCE

////////////////////////////////////////////////////////////////////////////////

#include <limits.h>
#include <pwd.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include "cnet/tcp_listener.h"
#include "cnet/tcp_socket.h"
#include "cnet/ftp.h"
#include "my/regex.h"
#include "my/string.h"

////////////////////////////////////////////////////////////////////////////////

#define UNUSED __attribute__((unused))

////////////////////////////////////////////////////////////////////////////////

typedef struct client
{
	tcp_socket_t *control_socket;
	ip_address_t control_channel_ip;
	unsigned short control_channel_port;

	tcp_socket_t *data_socket;
	tcp_listener_t *data_listener;
	ip_address_t data_channel_ip;
	unsigned short data_channel_port;

	bool passive;
} client_t;