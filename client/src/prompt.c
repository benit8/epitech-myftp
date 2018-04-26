/*
** EPITECH PROJECT, 2018
** myftp / client
** File description:
** prompt.c
*/

#include <termios.h>
#include "client.h"

char *prompt_ctl(int action, char *arg)
{
	static char *prompt = DEFAULT_PROMPT;

	switch (action) {
	case 0:
		return prompt;
	case 1:
		prompt = arg;
		break;
	default:
		break;
	}
	return (NULL);
}

static ssize_t my_getpass(char **lineptr, size_t *n, FILE *stream)
{
	struct termios old;
	struct termios new;
	int nread;

	if (tcgetattr(fileno(stream), &old) != 0)
		return (-1);
	new = old;
	new.c_lflag &= ~ECHO;
	if (tcsetattr(fileno(stream), TCSAFLUSH, &new) != 0)
		return (-1);
	nread = getline(lineptr, n, stream);
	tcsetattr(fileno(stream), TCSAFLUSH, &old);
	return (nread);
}

char *prompt(char *prompt, bool hidden)
{
	char *prompt_save;
	char *line = NULL;
	size_t s = 0;
	ssize_t r = 0;

	prompt_save = prompt_ctl(0, NULL);
	if (!prompt)
		prompt = DEFAULT_PROMPT;
	prompt_ctl(1, prompt);
	printf("%s ", prompt);
	r = hidden ? my_getpass(&line, &s, stdin) : getline(&line, &s, stdin);
	if (hidden)
		printf("\n");
	prompt_ctl(1, prompt_save);
	if (r < 0) {
		if (line)
			free(line);
		return (NULL);
	}
	line[strlen(line) - 1] = '\0';
	return (line);
}