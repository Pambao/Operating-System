/*
Operating System 
Project 3_1
Pham Gia Bao
CS2017
Vietnamese-German University
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND 10
#define MAX_CHAR_NUMBER 80

char commandHistory[MAX_COMMAND][MAX_CHAR_NUMBER];
int commandNumber = 0;

void displayHistory() { // This function is used to display the commandHistory
	int historyCounter = commandNumber;
	int charIndex = 0;
	for (int i = 0; i<MAX_COMMAND; i++) {
		printf ("%d. ", historyCounter);
		while ((commandHistory[i][charIndex] != '\n') && (commandHistory[i][charIndex] != '\0')) {
			printf ("%c", commandHistory[i][charIndex]);
			charIndex++;
		}	
		printf ("\n");
		charIndex = 0;
		historyCounter--;
		if (historyCounter == 0) {
			break;
		}
	}
}

void argProcess (char buffer[], char *args[], int *Ampers) { // This function process argument from the consoles
	int length = read(STDIN_FILENO, buffer, MAX_CHAR_NUMBER);
	if (length == 0) {
		exit (0);
	} else if (length < 0) {
		printf ("Could not read command!\n");
		exit (-1);
	}
	int pointer = -1;
	int charIndex = 0;
	
	for (int i = 0; i < length; i++) {
		switch (buffer[i]) {
			case ' ':
			case '\t':
				if (pointer != -1) {
					args[charIndex] = &buffer[pointer];
					charIndex++;
				}
				buffer[i] = '\0';
				pointer = -1;
				break;
			case '\n':
				if (pointer != -1) {
					args[charIndex] = &buffer[pointer];
					charIndex++;
				}
				buffer[i] = '\0';
				args[charIndex] = NULL;
				break;
			case '&':
				*Ampers = 1;
				buffer[i] = '\0';
				break;
			default:
				if (pointer == -1)
				{
					pointer = i;
				}
		}
	}
	args[charIndex] = NULL;
	if (strcmp (args[0], "history") == 0) {
		if (commandNumber > 0) {
			displayHistory();
		}
		else {
			printf ("\nNo commands in history.\n");
		}
	}
	else if (**args == '!') { // Check for "!"
		if (args[0][1]-'0' > commandNumber) {
			printf ("\nCommand no found!\n");
			strcpy (buffer, "Invalid command");
		} else if (args[0][2] != 0) {
			printf ("\nInput too large. History maximum is 10 commands.\n");
			strcpy (buffer, "Invalid command");
		} else {
			if (args[0][1]-'0' == -15) {
				strcpy (buffer, commandHistory[0]);
			} else if (args[0][1]-'0' == 0) {
				printf ("Cannot enter 0. Enter ! and integer 1-9.\n");
				strcpy (buffer, "Invalid command");
			} else if (args[0][1]-'0' >= 1)
			{
				strcpy (buffer, commandHistory[commandNumber-(args[0][1]-'0')]);
			}
		}
	}
	for (int i = 9; i > 0; i--) { // Update to command history
		strcpy (commandHistory[i], commandHistory[i-1]);
		strcpy (commandHistory[0], buffer);
		commandNumber++;
		if (commandNumber > MAX_COMMAND) {
			commandNumber = MAX_COMMAND;
		}			
	}
}

void nextCommand (void) { // This function is used to process the next command from the consoles
	char buffer[MAX_CHAR_NUMBER];
	char *args[MAX_CHAR_NUMBER/2+1];
	int ampersand;
	
	while (1) {
		ampersand = 0;
		printf ("osh> ");
		fflush (stdout);
		argProcess (buffer, args, &ampersand); // Get input from the console
		
		pid_t pid = fork();
		if (pid < 0) {
			printf ("Fork failed.\n");
			exit (1);
		} else if (pid == 0) {
			if ((execvp (args[0], args) == -1) 
			&& (strcmp (buffer, "history") != 0)
			){
				printf ("Invalid command.\n");
			}
		} else {
			if (ampersand == 0) {
				wait (NULL);
			}
		}
	}
}

void main () {
	nextCommand();
}
