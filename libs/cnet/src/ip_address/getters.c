/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** ip_address / getters.c
*/

#include "cnet/ip_address.h"

ip_address_t ip_address_get_local_address(void)
{
	struct sockaddr_in address;
	socklen_t size = sizeof(address);
	int sock = socket(PF_INET, SOCK_DGRAM, 0);

	if (sock == -1)
		return (IP_NONE);
	bzero(&address, sizeof(struct sockaddr_in));
	address.sin_addr.s_addr = INADDR_LOOPBACK;
	address.sin_family = AF_INET;
	address.sin_port = htons(9);
	if (connect(sock, (struct sockaddr *)&address, sizeof(address)) == -1) {
		close(sock);
		return (IP_NONE);
	}
	if (getsockname(sock, (struct sockaddr *)&address, &size) == -1) {
		close(sock);
		return (IP_NONE);
	}
	close(sock);
	return (ntohl(address.sin_addr.s_addr));
}