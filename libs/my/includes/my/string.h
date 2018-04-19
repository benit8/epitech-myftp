/*
** EPITECH PROJECT, 2018
** libmy
** File description:
** string.h
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////

char **explode(char *string, const char *delim);
bool str_empty(const char *string);
char *str_trim(char *str);