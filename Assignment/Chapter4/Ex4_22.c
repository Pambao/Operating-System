/*
Operating System 
Exercise 4.22
Pham Gia Bao
CS2017
Vietnamese-German University
*/
// Program must be compile with the tag "-lpthread" and "-lm"
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>
#include<stdbool.h>

int MAX=1;
int MIN=-1;
int pointInCircle=0;

bool isInCircle(double x, double y){
	return ( sqrt(x*x+y*y) <= 1) ? true : false;
}

double getPi( int totalPoint){
	return 4*(double)pointInCircle/totalPoint;
}

void* monteCarlo(void* input){
	for(int i=0; i< *((int*)input); i++){
		double x = (double)rand()/RAND_MAX*(MAX-MIN)+MIN;
		double y = (double)rand()/RAND_MAX*(MAX-MIN)+MIN;
		printf("Generated point: (%f,%f)\n", x,y);
		
		if(isInCircle(x,y))
			pointInCircle++;
	}
}


void main(){
	int totalPoint;
	double pi;
	do{
		printf("Input the number of points you want to create\n");
		scanf("%d",&totalPoint);
	}while(totalPoint<=0);
	
	pthread_t threadId;
	pthread_create(&threadId, NULL, monteCarlo, (void*)&totalPoint);
	pthread_join(threadId, NULL);
	
	pi = getPi(totalPoint);
	printf("Pi calculated is: %f\n", pi);
}

