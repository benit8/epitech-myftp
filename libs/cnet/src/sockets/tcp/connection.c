/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** sockets / tcp / connection.c
*/

#include "cnet/tcp_socket.h"

socket_status_t tcp_socket_connect(tcp_socket_t *sock, ip_address_t address,
	unsigned short port)
{
	struct sockaddr_in adr;

	if (!tcp_socket_create_handle(sock))
		return (SOCKET_ERROR);
	bzero(&adr, sizeof(struct sockaddr_in));
	adr.sin_addr.s_addr = address;
	adr.sin_family = AF_INET;
	adr.sin_port = htons(port);
	if (connect(sock->handle, (struct sockaddr *)&adr, sizeof(adr)) < 0)
		return (socket_get_error_status());
	return (SOCKET_DONE);
}

void tcp_socket_disconnect(tcp_socket_t *sock)
{
	if (sock->handle > 0) {
		close(sock->handle);
		sock->handle = -1;
	}
}