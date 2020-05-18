/*
Operating System 
Exercise 3.21
Pham Gia Bao
CS2017
Vietnamese-German University
*/
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	int num ,pid;
	
	do{
		printf("Please enter a number to do the Collatz conjecture\n");
		scanf("%d", &num);
	}while(num <= 1);
	
	pid = fork();
	if(pid < 0){
		printf("Failed to create child process\n");
		return -1;
	}
	if(pid == 0){
		printf("Child process is working...\n");
		printf("%d\n", num);
		while(num != 1){
			if(num%2 == 0)
				num /= 2;
			else
				num = 3 * num +1;
			printf("%d\n", num);
		}
	}
	else if(pid > 0){
		printf("\nParent is waiting for child...\n");
		wait(NULL);
		printf("Child process is done\n");
	}
	return 0;
}
