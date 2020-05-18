/*
Operating System 
Exercise 3.22
Pham Gia Bao
CS2017
Vietnamese-German University
*/
#include<stdio.h>
#include<stdlib.h>

#include<fcntl.h>
#include<sys/mman.h>
#include<unistd.h>
#include<sys/wait.h>

#ifndef PROTOCOL_H
#define PROTOCOL_H

#define NAME "Ex3_22"
#define NUM 30
#define SIZE (NUM * sizeof(int))
#endif
//Program must be compiled with the "-lrt" flag
int main(){
	
	int num ,pid;
	do{
		printf("Please enter a number to do the Collatz conjecture\n");
		scanf("%d", &num);
	}while(num <= 1);
	//Create child process
	pid = fork();
	if(pid < 0){
		printf("Failed to create child process\n");
		return -1;
	}
	if(pid == 0){
		//Create a shared memory in child process
		printf("Child process is working...\n");	
		int fd = shm_open(NAME, O_CREAT | O_EXCL | O_RDWR, 0600);
		//If file is already create, remove the create tag
		if(fd<0){
			perror("shm_open()");
			fd = shm_open(NAME, O_EXCL | O_RDWR, 0600);
		}
		ftruncate(fd, SIZE);
		//Map the memory with the local variable
		int* data=(int*) mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
		printf("sender mapped address: %p\n", data);
		//Clear the previous data in memory
		for(int i=0;i<NUM;i++){
			data[i]=0;
		}
		//Assign new data
		data[0] = num;
		int counter =1;
		while(num != 1){
			if(num%2 == 0)
				num /= 2;
			else
				num = 3 * num +1;
			data[counter] = num;
			counter++;
		}
		//Unmap data
		munmap(data, SIZE);
		close(fd);
	}
	else if(pid > 0){
		printf("\nParent is waiting for child...\n");
		wait(NULL);
		//Open connection
		int fd = shm_open(NAME, O_RDONLY, 0666);
		if(fd<0){
			perror("shm_open()");
			return EXIT_FAILURE;
		}
		//Map created memory with local variable
		int *data = (int*)mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);
		printf("receiver mapped address: %p\n", data);
		// Display the output
		for(int i=0; i<NUM;i++){
			if(data[i]==0)
				break;
			printf("%d\n", data[i]);
		}
		//Unmap data
		munmap(data, SIZE);
		close(fd);
		printf("Child process is done\n");
		
	return 0;
	}
}
