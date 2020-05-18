/*
Operating System 
Project 5_2
Pham Gia Bao
CS2017
Vietnamese-German University
*/
//Program must be compiled with the tag "-lpthread"
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>

#define MAX_NUMBER_OF_PHILOSOPHER 5
#define MAX_NUMBER_OF_DINNING 5
#define MAX_WAITING_TIME 3
#define MIN_WAITING_TIME 1
enum state{thinking, hungry, dinning};

pthread_mutex_t lock;
pthread_cond_t philosopherCond[MAX_NUMBER_OF_PHILOSOPHER];
enum state philosopherState[MAX_NUMBER_OF_PHILOSOPHER];
int philosopherIdentity[MAX_NUMBER_OF_PHILOSOPHER];

void initialPhilosopherProperties(){ // This function is used to initialise the philosopher identity and state
    for(int i =0; i< MAX_NUMBER_OF_PHILOSOPHER; i++) {
        philosopherIdentity[i] = i;
        philosopherState[i] = thinking;
    }
}

int generateRandomTime() { // This function is used to generate random time
    return rand()%(MAX_WAITING_TIME-MIN_WAITING_TIME+1) + MIN_WAITING_TIME;
}

int leftNeighbor(int philosopherId) { // This function return left neighbor of a given philosopherId
    return (philosopherId == 0) ? (MAX_NUMBER_OF_PHILOSOPHER -1) : (philosopherId -1);  
}

int rightNeighbor(int philosopherId) { // This funtion return right neighbor of a given philosopherId
    return (philosopherId == MAX_NUMBER_OF_PHILOSOPHER -1) ? 0 : (philosopherId +1);
}

void signal(int philosopherId){ // This function is used to change the state of philosopherId by some conditions
    int leftNeighborId = leftNeighbor(philosopherId);
    int rightNeightborId = rightNeighbor(philosopherId);
    // If left and right neighbor of the given philosopher is not dinning and philosopher state is hungry
    // The given philosopher state will be eating
    if((philosopherState[leftNeighborId] != dinning)
        && (philosopherState[rightNeightborId] != dinning)
        && (philosopherState[philosopherId] == hungry)
    ){
        philosopherState[philosopherId] = dinning;
        pthread_cond_signal(&philosopherCond[philosopherId]); // signal the waiting cond of the philosopher to continue
    }
}

void pickup_fork(int philosopherId){ // This function change the state of the philosopher to dinning after waiting for his neighbor to finish
    pthread_mutex_lock(&lock);
    philosopherState[philosopherId] = hungry;
    signal(philosopherId);
    while(philosopherState[philosopherId] != dinning){
        pthread_cond_wait(&philosopherCond[philosopherId], &lock); // Wait for neighbor philosopher to finish eating
    }
    pthread_mutex_unlock(&lock);
}

void return_fork(int philosopherId){ // Change the state of his neighbor to dinning when they are waiting for this philosopher
    int leftNeighborId = leftNeighbor(philosopherId);
    int rightNeighborId = rightNeighbor(philosopherId);
    pthread_mutex_lock(&lock);
    philosopherState[philosopherId] = thinking;
    signal(leftNeighborId); // Allow left neighbor to eat when satisfy conditions
    signal(rightNeighborId); // Allow left neighbor to eat when satisfy conditions
    pthread_mutex_unlock(&lock);
}

void* philosopher(void* inPhilosopherId){ // Philosopher thread
    
    int philosopherId = *(int*) inPhilosopherId;
    int randomTime;
    time_t start, end;
    double hungryTime;
    
    printf("Philosopher %d is running\n", philosopherId+1);
    // Philosopher is allow to eat for MAX_NUMBER_OF_DINNNG times
    for(int eatingCounter=0; eatingCounter<MAX_NUMBER_OF_DINNING; eatingCounter++) {
        printf("Philosopher %d eat for %d times\n",philosopherId+1, eatingCounter);
        // Thinking
        randomTime = generateRandomTime();
        printf("Philosopher %d is thinking for %d seconds\n", philosopherId+1, randomTime);
        sleep(randomTime);
        // Waiting to pick up fork
        time(&start);
        pickup_fork(philosopherId);
        time(&end);
        hungryTime = end - start;
        printf("Philosopher %d is hungry for %f seconds\n", philosopherId+1,hungryTime);
        // Eating for a random time
        randomTime = generateRandomTime();
        printf("Philosopher %d is eating at time %d for %d seconds\n", philosopherId+1, eatingCounter+1,randomTime);
        sleep(randomTime);
        // Return fork and signal other philosophers are waiting
        return_fork(philosopherId);
    }

}

void main(){
    initialPhilosopherProperties();
    // Create thread
    pthread_t philosopherThread[MAX_NUMBER_OF_PHILOSOPHER];
    for(int i =0; i<MAX_NUMBER_OF_PHILOSOPHER; i++) {
        pthread_create(&philosopherThread[i], NULL, &philosopher, (void*) &philosopherIdentity[i]);
    }
    // Join thread
    for(int i =0; i<MAX_NUMBER_OF_PHILOSOPHER; i++) {
        pthread_join(philosopherThread[i], NULL);
    }
}