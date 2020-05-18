/*
Operating System 
Exercise 4.20
Pham Gia Bao
CS2017
Vietnamese-German University
*/
// Program must be compiled with the tag "-lpthread"
#include <stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<pthread.h>
#include<unistd.h>

#define MIN_PID 500
#define MAX_PID 3000
#define SIZE  (MAX_PID - MIN_PID + 1)
//lastPid is the last pid that have been allocated
int pidArray[SIZE];
int lastPid;

int allocate_map(){
	for(int i=0; i<SIZE; i++){
		pidArray[i]=0;
	}
	lastPid= MIN_PID;
	// check if the map has successfully been allocated
	if(pidArray[SIZE-1]==0)
		return 1;
	else
		return -1;
		
}

int allocate_pid(){
	//count the times of interation in the loop to determine there is any pid left
	int count=0;
	//assign the nextPidIndex in ther pidArray
	int nextPidIndex= (lastPid==MAX_PID) ? MIN_PID : lastPid+1-MIN_PID;
	//looking for free pid
	while(count<SIZE && pidArray[nextPidIndex]==1){
		count++;
		nextPidIndex = (nextPidIndex+1 >= SIZE-MIN_PID) ? 0 : nextPidIndex+1 ;
	}
	//return -1 if there is no free pid left
	if(count>=SIZE)
		return -1;
	else{
		pidArray[nextPidIndex]=1;
		lastPid= nextPidIndex+MIN_PID;
		return lastPid;
	}
}


void release_pid(int pid){
	pidArray[pid-MIN_PID]=0;
}

void* threadTest(){
	int pid = allocate_pid();
	printf("Allocating Pid :%d\n", pid);
	sleep(rand()%6);
	release_pid(pid);
	printf("Releasing Pid :%d\n", pid);
	pthread_exit(0);
}

int main(void){
	//allocate map
	int map = allocate_map();
		printf("Pid map initialized successfully!\n");

	pthread_t pid[100];
	//create_thread
	for(int i=0; i<100; i++){
		pthread_create(&pid[i], NULL, &threadTest, NULL);
	}
	//join_thread
	for(int i=0; i<100; i++){
		pthread_join(pid[i], NULL);
	}	
}
