/*
Operating System 
Exercise 3.26
Pham Gia Bao
CS2017
Vietnamese-German University
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<ctype.h>
// define limit of input string
# define LIMIT 50
// This function chage upperCase -> lowerCase and vice versa of a digit in a string 
char* toggle(char* string){
	for(int i=0; i<strlen(string); i++){
		if(string[i]>=65&&string[i]<=90){
			string[i] = string[i] + 32;
		}
		else if(string[i]>=97&&string[i]<=122){
			string[i] = string[i] - 32;
		}
	}
	return string;
}

int main(){
	int fd1[2];
	int fd2[2];
	int pipe1 =pipe(fd1);
	int pipe2= pipe(fd2);
	
	if(pipe1==-1){
		printf("Pipe one failed\n");
		return 1;
	}
	
	if(pipe2==-1){
		printf("Pipe two failed\n");
		return 1;
	}
	
	int pid = fork();
	if(pid<0){
		printf("Fork failed\n");
		return 1;
	}
	
	if(pid>0){ //Parent process input and send to child process via a pipe
		char output[LIMIT];
		char input[LIMIT];
		//Input
		printf("Enter your input string:\n");
		fgets(input, LIMIT, stdin);
		close(fd1[0]);
		//Send input		
		printf("Parent process send: %s\n", input);
		write(fd1[1], input, strlen(input)+1);
		close(fd1[1]);
		wait(NULL);
		//Receive output from child process
		close(fd2[1]);
		read(fd2[0],output, LIMIT );
		close(fd2[0]);
		printf("Parent process received, final output: %s\n", output);
	}
	else{
		//Child process receive a string
		close(fd1[1]);
		char received[LIMIT];
		read(fd1[0], received, LIMIT);
		printf("Child process received: %s\n", received);
		//Process string
		toggle(received);
		//Send string after processed to parent
		close(fd1[0]);
		close(fd2[0]);
		printf("Child process sent: %s\n", received);
		write(fd2[1], received, strlen(received)+1);
		close(fd2[1]);
	}
	return 0;
}
