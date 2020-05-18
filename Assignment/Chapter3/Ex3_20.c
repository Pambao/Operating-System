/*
Operating System 
Exercise 3.20
Pham Gia Bao
CS2017
Vietnamese-German University
*/
#include <stdio.h>
#include<stdlib.h>
#include<limits.h>

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

int main(void){
	//create map
	int map = allocate_map();
		printf("Pid map initialized successfully!\n");
	//allocate 2503 pid to test if the last pid return -1
	for(int i=0; i<2502;i++){
		int pid = allocate_pid();
		printf("Process %dth with pid: %d\n",i,pid);
	}
	//release pid 502 and allocate again to see wether it return 502
	release_pid(502);
	int pid = allocate_pid();
	printf("Allocate another pid: %d\n", pid);
	
}
