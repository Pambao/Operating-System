/*
Operating System 
Exercise 4.24
Pham Gia Bao
CS2017
Vietnamese-German University
*/
//Program must be compiled with the tag "-lpthread"
#include<stdio.h>
#include<pthread.h>
#include<stdbool.h>

bool isPrime(int num){
	for(int i=2; i<num; i++){
		if(num%i==0){
			return false;
		}
	}
	return true;
}


void* findPrime(void* input){
	for(int i=2; i<=*((int*)input); i++){
		if(isPrime(i))
			printf("Prime: %d\n", i);
	}
	pthread_exit(0);
}

void main(){
	int input;
	do{
		printf("Please enter a limit more than 1:\n");
		scanf("%d", &input);
	}while(input<=1);
	pthread_t threadId;
	pthread_create(&threadId, NULL, &findPrime, (void*) &input);
	pthread_join(threadId, NULL);
}

