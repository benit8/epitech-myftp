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

#define DEFAULT_PROMPT "myftp>"

////////////////////////////////////////////////////////////////////////////////

typedef struct data
{
	tcp_socket_t *control_socket;
	ip_address_t control_ip;
	unsigned short control_port;

	tcp_socket_t *data_socket;
	tcp_listener_t *data_listener;
	ip_address_t data_ip;
	unsigned short data_port;

	bool passive;
	int debug;
	ftp_transfer_mode_t transfer_mode;
} data_t;

typedef struct command
{
	char *name;
	int (*func)(data_t *, size_t, char **);
	char *help;
} command_t;

typedef struct response
{
	int code;
	char *message;
	char *raw;
} response_t;

typedef struct pair
{
	char *first;
	char *second;
} pair_t;

////////////////////////////////////////////////////////////////////////////////

char *prompt_ctl(int action, char *arg);
char *prompt(char *custom_prompt, bool hidden);

bool connected(data_t *data);
bool not_connected(data_t *data);

int exec_command(data_t *data, char *input);
void send_command(data_t *data, char *fmt, ...);

response_t *response_get(data_t *data);
void response_destroy(response_t *res);
void response_display(response_t *res);
int response_wait(data_t *data, bool display);
char *response_get_quoted(response_t *res);

int ftp_append(data_t *data, size_t argc, char **argv);
int ftp_ascii(data_t *data, size_t argc, char **argv);
int ftp_binary(data_t *data, size_t argc, char **argv);
int ftp_cd(data_t *data, size_t argc, char **argv);
int ftp_cdup(data_t *data, size_t argc, char **argv);
int ftp_debug(data_t *data, size_t argc, char **argv);
int ftp_delete(data_t *data, size_t argc, char **argv);
int ftp_disconnect(data_t *data, size_t argc, char **argv);
int ftp_exit(data_t *data, size_t argc, char **argv);
int ftp_help(data_t *data, size_t argc, char **argv);
int ftp_lcd(data_t *data, size_t argc, char **argv);
int ftp_list(data_t *data, size_t argc, char **argv);
int ftp_llist(data_t *data, size_t argc, char **argv);
int ftp_lpwd(data_t *data, size_t argc, char **argv);
int ftp_mkdir(data_t *data, size_t argc, char **argv);
int ftp_noop(data_t *data, size_t argc, char **argv);
int ftp_open(data_t *data, size_t argc, char **argv);
int ftp_passive(data_t *data, size_t argc, char **argv);
int ftp_pwd(data_t *data, size_t argc, char **argv);
int ftp_quote(data_t *data, size_t argc, char **argv);
int ftp_recv(data_t *data, size_t argc, char **argv);
int ftp_rename(data_t *data, size_t argc, char **argv);
int ftp_rmdir(data_t *data, size_t argc, char **argv);
int ftp_send(data_t *data, size_t argc, char **argv);
int ftp_user(data_t *data, size_t argc, char **argv);

////////////////////////////////////////////////////////////////////////////////

extern const command_t commands[];
extern const size_t command_count;
extern const pair_t aliases[];
extern const size_t alias_count;