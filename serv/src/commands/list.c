/*
** EPITECH PROJECT, 2018
** ftp / server
** File description:
** commands / list.c
*/

#include "server.h"

void list(client_t *client, size_t argc UNUSED, char **argv UNUSED)
{
	int fd_save;
	pid_t pid;

	if (!init_data_connection(client)) {
		send_response(client, DATA_CONNECTION_UNAVAILABLE, NULL);
		return;
	}
	send_response(client, OPENING_DATA_CONNECTION,
		"Here comes the directory listing");
	fd_save = dup(1);
	dup2(client->data_socket->handle, 1);
	pid = fork();
	if (pid == 0)
		execl("/bin/ls", "ls", "-l", NULL);
	else
		waitpid(pid, 0, WSTOPPED);
	dup2(fd_save, 1);
	tcp_socket_disconnect(client->data_socket);
	send_response(client, CLOSING_DATA_CONNECTION, NULL);
}