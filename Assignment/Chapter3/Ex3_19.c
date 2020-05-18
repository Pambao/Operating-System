/*
Operating System 
Exercise 3.19
Pham Gia Bao
CS2017
Vietnamese-German University
*/
// Run the program in the background and check wether there is a zombie process
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	int pid = fork();
	if(pid < 0){
		printf("Failed to create new process");
		return -1;
	}
	if(pid == 0){
		printf("child process: %d\n", getpid());
	}
	else{
		sleep(20);
		printf("parent process: %d\n", getpid());
		wait(NULL);
	}
	return 0;
}
