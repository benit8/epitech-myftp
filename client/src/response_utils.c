/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** response_utils.c
*/

#include "client.h"

void response_display(response_t *res)
{
	printf("%d %s\n", res->code, res->message);
}

int response_wait(data_t *data, bool display)
{
	response_t *res = response_get(data);
	int ret;

	if (!res)
		return (-1);
	ret = (res->code < 400) ? 1 : 2;
	if (display)
		response_display(res);
	response_destroy(res);
	return (ret);
}

char *response_get_quoted(response_t *res)
{
	char *start = res->message;
	size_t size = 0;

	for (; *start && *start != '"'; ++start);
	start++;
	for (size = 0; start[size] && start[size] != '"'; ++size);
	return (strndup(start, size));
}

/*
ip_address_t response_get_ip_address(response_t *res)
{
	char **matches = NULL;

	if ()
}
*/