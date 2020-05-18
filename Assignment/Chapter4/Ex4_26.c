/*
Operating System 
Exercise 4.26
Pham Gia Bao
CS2017
Vietnamese-German University
*/
//Program must be compiled with the tag "-lpthread"
#include<stdio.h>
#include<pthread.h>
int sharedResult[1000];

void getInput(int* input){
	printf("Please enter the number of fibonacci element you want to get\n");
	scanf("%d", input);
}

void printOutput(int input){
	for(int i=0; i<input; i++){
		printf("%dth element: %d\n",i,sharedResult[i]);
	}
}

void* fibonacci(void* input){
	int fib0=0, fib1=1, next=0;
	for(int i=0; i<*((int*)input); i++){
		if(i<=1)
			next = i;
		else{
			next = fib0 + fib1;
			fib0 = fib1;
			fib1 = next;
		}
		sharedResult[i] = next;
	}
}
void main(){
	int input;
	getInput(&input);
	
	pthread_t threadId;
	pthread_create(&threadId, NULL, &fibonacci, (void*) &input);
	pthread_join(threadId, NULL);
	
	printOutput(input);
}
