/*
** EPITECH PROJECT, 2018
** ftp / server
** File description:
** status.c
*/

#include "server.h"

const status_string_t status_strings[] = {
	{RESTART_MARKER_REPLY, "Restart Marker Reply"},
	{SERVICE_READY_SOON, "Service Ready Soon"},
	{DATA_CONNECTION_ALREADY_OPENED, "Data Connection Already Opened"},
	{OPENING_DATA_CONNECTION, "Opening Data Connection"},

	{OK, "Ok"},
	{POINTLESS_COMMAND, "Pointless Command"},
	{SYSTEM_STATUS, "System Status"},
	{DIRECTORY_STATUS, "Directory Status"},
	{FILE_STATUS, "File Status"},
	{HELP_MESSAGE, "Help Message"},
	{SYSTEM_TYPE, "System Type"},
	{SERVICE_READY, "Service Ready"},
	{CLOSING_CONNECTION, "Closing Connection"},
	{DATA_CONNECTION_OPENED, "Data Connection Opened"},
	{CLOSING_DATA_CONNECTION, "Closing Data Connection"},
	{ENTERING_PASSIVE_MODE, "Entering Passive Mode"},
	{LOGGED_IN, "Logged In"},
	{FILE_ACTION_OK, "File Action Ok"},
	{DIRECTORY_OK, "Directory Ok"},

	{NEED_PASSWORD, "Need Password"},
	{NEED_ACCOUNT_TO_LOGIN, "Need Account To Login"},
	{NEED_INFORMATION, "Need Information"},

	{SERVICE_UNAVAILABLE, "Service Unavailable"},
	{DATA_CONNECTION_UNAVAILABLE, "Data Connection Unavailable"},
	{TRANSFER_ABORTED, "Transfer Aborted"},
	{FILE_ACTION_ABORTED, "File Action Aborted"},
	{LOCAL_ERROR, "Local Error"},
	{INSUFFICIENT_STORAGE_SPACE, "Insufficient Storage Space"},

	{COMMAND_UNKNOWN, "Command Unknown"},
	{PARAMETERS_UNKNOWN, "Parameters Unknown"},
	{COMMAND_NOT_IMPLEMENTED, "Command Not Implemented"},
	{BAD_COMMAND_SEQUENCE, "Bad Command Sequence"},
	{PARAMETER_NOT_IMPLEMENTED, "Parameter Not Implemented"},
	{NOT_LOGGED_IN, "Not Logged In"},
	{NEED_ACCOUNT_TO_STORE, "Need Account To Store"},
	{FILE_UNAVAILABLE, "File Unavailable"},
	{PAGE_TYPE_UNKNOWN, "Page Type Unknown"},
	{NOT_ENOUGH_MEMORY, "Not Enough Memory"},
	{FILENAME_NOT_ALLOWED, "Filename Not Allowed"},

	{INVALID_RESPONSE, "Invalid Response"},
	{CONNECTION_FAILED, "Connection Failed"},
	{CONNECTION_CLOSED, "Connection Closed"},
	{INVALID_FILE, "Invalid File"},

	{0, NULL}
};

char *ftp_status_as_strings(ftp_status_t s)
{
	for (size_t i = 0; status_strings[i].string; ++i) {
		if (status_strings[i].status == s)
			return (status_strings[i].string);
	}
	return ("Unknown");
}