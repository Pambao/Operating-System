/*
Operating System 
Project 5_1
Pham Gia Bao
CS2017
Vietnamese-German University
*/
//Program must be compiled with the tag "-lpthread"
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

#define NUM_OF_CHAIRS 3
#define MIN_SLEEP_TIME 1
#define MAX_SLEEP_TIME 5
#define MAX_HELP_TIME 2

pthread_mutex_t lock;
sem_t semTeachingAssistant;
sem_t semStudent;

int waitingChairs[NUM_OF_CHAIRS];
int numberOfStudents=0;
int numberOfWaitingStudents=0;
int nextSeatPosition=0;
int nextTeachPosition=0;
int taSleepingFlag=0;

void getInput(){ // This function is used to get number of student from the input console
    printf("Enter number of students:\n");
    scanf("%d", &numberOfStudents);
    while(numberOfStudents <= 0) {
        printf("You have entered invalid number\n");
        printf("Please try again:\n");
        scanf("%d", &numberOfStudents);
    }
}

int isWaiting(int studentId){ // This function is used to determine whether a student is waiting or not
    for(int i=0;i<NUM_OF_CHAIRS;i++){
        if (waitingChairs[i] == studentId)
            return 1;
    }
    return 0;
}

void* studentThread(void* inputStudentId){ // This thread is used for student actions
    int studentId = *(int*) inputStudentId;
    while(1){
        //If the student is waiting on waiting chair
        if(isWaiting(studentId)==1){
            continue;
        }
        // Student is programming themself
        int programmingTime = 
        rand()%(MAX_SLEEP_TIME - MIN_SLEEP_TIME +1) + MIN_SLEEP_TIME;
        printf("Student %d is programming for %d second\n", studentId, programmingTime);
        sleep(programmingTime);

        pthread_mutex_lock(&lock);
        printf("\n");
        //Student come to teaching assistant room after programming themeself
        if(numberOfWaitingStudents < NUM_OF_CHAIRS) { // If there is still remaining chair for waiting
            numberOfWaitingStudents++;
            waitingChairs[nextSeatPosition] = studentId;
            printf("Student %d comes to the teaching assistant room. %d students are wating\n", studentId, numberOfWaitingStudents);
            nextSeatPosition=(nextSeatPosition+1)%NUM_OF_CHAIRS;

            pthread_mutex_unlock(&lock);
            sem_wait(&semTeachingAssistant);
            sem_post(&semStudent);
        } else { // If there is no place for waiting
            pthread_mutex_unlock(&lock);
            printf("Student %d comes to the teaching assistant room, but waiting chairs are full! Try later! \n", studentId);
        }
    }
}

void* taThread(){ // This thread is used for teaching assistant actions
    while(1) { 
        if (numberOfWaitingStudents>0){ // If there are students waiting outside
            taSleepingFlag=0;
            sem_wait(&semStudent);
            pthread_mutex_lock(&lock);

            printf("\n");
            int helpTime = 
            rand()%(MAX_HELP_TIME-MIN_SLEEP_TIME+1)+MIN_SLEEP_TIME;

            numberOfWaitingStudents--;
            printf("Teaching Assistant is helping student %d for %d second\n", waitingChairs[nextTeachPosition], helpTime);
            waitingChairs[nextTeachPosition] =0;
            nextTeachPosition = (nextTeachPosition +1) % NUM_OF_CHAIRS;
            printf("Number of students are waiting left: %d\n\n", numberOfWaitingStudents);
            sleep(helpTime);

            pthread_mutex_unlock(&lock);
            sem_post(&semTeachingAssistant);
        } else { // If there is no student waiting
            if(taSleepingFlag == 0){
                taSleepingFlag = 1;
                printf("There is no student waiting, ta sleep zZz,,,\n\n");
            }
        }
    }
}


int main(){
    getInput();
    int studentIds[numberOfStudents];
    // Initial variable for mutex and semaphore
    pthread_mutex_init(&lock, NULL);
    sem_init(&semStudent,0,0);
    sem_init(&semTeachingAssistant,0,1);
    // Initial thread
    pthread_t students[numberOfStudents];
    pthread_t ta;
    pthread_create(&ta, NULL, &taThread, NULL);
    for(int i=0; i<numberOfStudents; i++) {
        studentIds[i] = i + 1;
        pthread_create(&students[i], NULL, &studentThread, (void*) &studentIds[i]);        
    }
    // Join thread
    pthread_join(ta, NULL);
    for(int i=0; i<numberOfStudents; i++) {
        pthread_join(students[i], NULL);
    }
}