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
	tcp_listener_t *data_listener;
	tcp_socket_t *data_socket;
	ip_address_t data_channel_ip;
	unsigned short data_channel_port;
	char username[32];
	struct passwd *user;
	bool anon;
	bool logged_in;
	bool binary;
	char last_command[256];
	char to_rename[PATH_MAX];
} client_t;

typedef struct command
{
	char *name;
	void (*func)(client_t *, size_t, char **);
	char *usage;
	char *help;
} command_t;

typedef struct status_string
{
	ftp_status_t status;
	char *string;
} status_string_t;

typedef struct transfer_type
{
	char *flag;
	bool binary;
} transfer_type_t;

typedef struct pair
{
	char *first;
	char *second;
} pair_t;

typedef FILE file_t;

////////////////////////////////////////////////////////////////////////////////

server_ressources_t *get_server_ressources(void);

void client(tcp_socket_t *socket);
void client_disconnected(client_t *client);
bool client_is_logged_in(client_t *client);

char *get_input(client_t *client);
void parse_input(char *input, client_t *client);

char *ftp_status_as_strings(ftp_status_t s);

bool init_data_channel(client_t *client);
void close_data_channel(client_t *client, bool ok);
bool send_response(client_t *client, ftp_status_t status, char *fmt, ...);

// Commands

void unknown_command(client_t *client, size_t argc, char **argv);
void not_implemented(client_t *client, size_t argc, char **argv);
void obsolete(client_t *client, size_t argc, char **argv);

void allo(client_t *client, size_t argc, char **args);
void appe(client_t *client, size_t argc, char **args);
void cdup(client_t *client, size_t argc, char **args);
void cwd(client_t *client, size_t argc, char **args);
void dele(client_t *client, size_t argc, char **args);
void help(client_t *client, size_t argc, char **args);
void list(client_t *client, size_t argc, char **args);
void mkd(client_t *client, size_t argc, char **args);
void mode(client_t *client, size_t argc, char **args);
void noop(client_t *client, size_t argc, char **args);
void pass(client_t *client, size_t argc, char **args);
void pasv(client_t *client, size_t argc, char **args);
void port(client_t *client, size_t argc, char **args);
void pwd(client_t *client, size_t argc, char **args);
void quit(client_t *client, size_t argc, char **args);
void retr(client_t *client, size_t argc, char **args);
void rmd(client_t *client, size_t argc, char **args);
void rnfr(client_t *client, size_t argc, char **args);
void rnto(client_t *client, size_t argc, char **args);
void stor(client_t *client, size_t argc, char **args);
void stru(client_t *client, size_t argc, char **args);
void syst(client_t *client, size_t argc, char **args);
void type(client_t *client, size_t argc, char **args);
void user(client_t *client, size_t argc, char **args);

////////////////////////////////////////////////////////////////////////////////

extern const command_t commands[];
extern const status_string_t status_strings[];
extern const size_t command_count;