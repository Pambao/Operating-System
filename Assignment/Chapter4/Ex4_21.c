/*
Operating System 
Exercise 4.21
Pham Gia Bao
CS2017
Vietnamese-German University
*/
//Program must be compiled with the tag "-lpthread"
#include <stdio.h>
#include<stdlib.h>
#include <pthread.h>

int average, minimum, maximum;
int size = 7;
int num[7];

void input(){
	for(int i=0; i<size; i++){
		printf("Please input 7 numbers to calculate\n");
		scanf("%d", num+i);
	}
}

void* avg(){
	int total = 0;
	for(int i=0; i<size; i++){
		total += num[i];
	}
	average = total / size;
}

void* min(){
	minimum = num[0];
	for(int i=1; i<size; i++){
		if(minimum>num[i]){
		minimum = num[i];
		}
	}
}
	
void* max(){
	maximum = num[0];
	for(int i=1; i<size; i++){
		if(maximum<num[i]){
		maximum = num[i];
		}
	}
}
void main(){
	input();
	
	pthread_t threadId1;
	pthread_t threadId2;
	pthread_t threadId3;
	
	pthread_create(&threadId1, NULL, &avg, NULL);
	pthread_join(threadId1, NULL);
	printf("The average value is %d\n", average);
	
	pthread_create(&threadId2, NULL, &min, NULL);
	pthread_join(threadId2, NULL);
	printf("The minimum value is %d\n", minimum);
	
	pthread_create(&threadId3, NULL, &max, NULL);
	pthread_join(threadId3, NULL);
	printf("The maximum value is %d\n", maximum);

}
