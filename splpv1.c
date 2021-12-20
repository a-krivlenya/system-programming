/*
* SPLPv1.c
* The file is part of practical task for System programming course.
* This file contains validation of SPLPv1 protocol.
*/


/*
Кривленя Анастасия
13 группа
 */


#include "splpv1.h"
#include "string.h"
#include <stdlib.h>


int CurrentState = 1;
int WhatCommand;

const char base64[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 };

const char data[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 };

const char* commands[] = { "GET_DATA", "GET_FILE", "GET_COMMAND" };


enum test_status validate_message(struct Message* msg) {
	char* message = msg->text_message;
	if (msg->direction == A_TO_B) {
		if (CurrentState == 1 && !strcmp(message, "CONNECT")) {
			CurrentState = 2;
			return MESSAGE_VALID;
		}
		else if (CurrentState == 3) {
			if (!strcmp(message, "GET_VER")) {
				CurrentState = 4;
				return MESSAGE_VALID;
			}
			else if (!strcmp(message, "GET_DATA")) {
				WhatCommand = 0;
				CurrentState = 5;
				return MESSAGE_VALID;
			}
			else if (!strcmp(message, "GET_FILE")) {
				WhatCommand = 1;
				CurrentState = 5;
				return MESSAGE_VALID;
			}
			else if (!strcmp(message, "GET_COMMAND")) {
				WhatCommand = 2;
				CurrentState = 5;
				return MESSAGE_VALID;
			}
			else if (!strcmp(message, "GET_B64")) {
				CurrentState = 6;
				return MESSAGE_VALID;
			}
			else if (!strcmp(message, "DISCONNECT")) {
				CurrentState = 7;
				return MESSAGE_VALID;
			}
		}
	}
	else {
		if (CurrentState == 2 && !strcmp(message, "CONNECT_OK")) {
			CurrentState = 3;
			return MESSAGE_VALID;
		}
		else if (CurrentState == 7 && !strcmp(message, "DISCONNECT_OK")) {
			CurrentState = 1;
			return MESSAGE_VALID;
		}
		else if (CurrentState == 4 && !strncmp(message, "VERSION ", 8)) {
			message += 8;
			if (*message > 48 && *message < 58) {
				for (++message; *message != '\0'; message++)
					if (*message < 48 || *message > 57) {
						CurrentState = 1;
						return MESSAGE_INVALID;
					}
				CurrentState = 3;
				return MESSAGE_VALID;
			}
		}
		else if (CurrentState == 5) {
			int l = strlen(commands[WhatCommand]);
			if (!strncmp(message, commands[WhatCommand], l))
			{
				message += l;
				if (*message == ' ')
				{
					message++;
					char* s;
					for (; data[*message + 128]; ++message);
					s = (*message == ' ') ? message + 1 : NULL;
					if (s && !strcmp(s, commands[WhatCommand])) {
						CurrentState = 3;
						return MESSAGE_VALID;
					}
				}
			}
		}
		else if (CurrentState == 6 && !strncmp(message, "B64: ", 5)) {
			message += 5;
			char* begin = message;
			for (; base64[*message + 128]; ++message);
			char check = 0;
			for (; (check < 2) && (message[check] == '='); ++check);
			if ((message - begin + check) % 4 == 0 && !message[check]) {
				CurrentState = 3;
				return MESSAGE_VALID;
			}
		}
	}
	CurrentState = 1;
	return MESSAGE_INVALID;
}