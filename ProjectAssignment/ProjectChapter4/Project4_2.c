/*
Operating System 
Project 4_2
Pham Gia Bao
CS2017
Vietnamese-German University
*/
//Program must be compiled with the tag "-lpthread"
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define SIZE 10

int array[SIZE] = {}; // This array is used to stored the input
int joinedArray[SIZE]={}; // This array is used to stored merged array

void* bubbleSort(void* index){ // This thread is used to sort array by ascending order. Its parameter will be the position for the thread to start sorting
// The algorithm used here is bubbleSort
    int swapCounter=0;
    do{
        swapCounter =0;
        int iterationCounter = 0; // this variable is used to count the number of index to be sorted
        for(int i = *(int*)index; iterationCounter < ((SIZE /2)- 1); i++){
            iterationCounter ++;
            if(array[i]>array[i+1]){
                int temp = array[i];
                array[i] = array[i+1];
                array[i+1] = temp;
                swapCounter++;
            }
        }
    } while(swapCounter > 0); // If after looping through the array and there aren't any swap occur, then the sorting will finish
    return NULL;
}

void* join (void* index){ // This thread is used to merge 2 half of the array into one sorted array
    int firstHalfCounter = 0;
    int secondHalfCounter = *(int*) index;
    for(int i=0; i < SIZE; i++){
        if(firstHalfCounter==SIZE/2 ){ // If all value of the first half of the array are all assigned to the joinedArray
            joinedArray[i] = array[secondHalfCounter++]; // Then just assigned the remaining second half to the joinedArray
        } else if(secondHalfCounter == SIZE){ // Vice versa
            joinedArray[i] = array[firstHalfCounter++];
        } else{ // If both first and second half still exist values to be assigned to the joinedArray
            joinedArray[i] = (array[firstHalfCounter] < array[secondHalfCounter]) ?
            array[firstHalfCounter++] : array[secondHalfCounter++];
        }
    }
}

void displayArray(char message[]){ // This function is just used to output the array to the screen
    for(int i=0; message[i] != '\0'; i++){
        printf("%c", message[i]);
    }
    printf("[ ");
    for(int i = 0; i<SIZE; i++){
        printf("%d ", array[i]);
    }
    printf("]");
    printf("\n");
}

void displayMergedArray(char message[]){ // This function is just used to output the mergedArray to the screen
     for(int i=0; message[i] != '\0'; i++){
        printf("%c", message[i]);
    }
    printf("[ ");
    for(int i = 0; i<SIZE; i++){
        printf("%d ", joinedArray[i]);
    }
    printf("]");
    printf("\n");
}

void getInput(){ // This function is just used to get input from the console
    char input[20];
    int counter = 0;
    int check = 0;
    while(check == 0){
        counter = 0;
        printf("Enter 10 abitary 1 digit integer:\n");
        printf("Each digit must be sepatated by a space\n");
        fgets(input, 20, stdin);
        for(int i =0; i< 20; i++){
            if(i==0 || (i%2) ==0){
                if(isdigit(input[i]) == 1){
                    array[counter++] = input[i] - '0';
                } else {
                    printf("Your input you have enter have some errors\n");
                    printf("Please try again\n");
                    check--;
                    break;
                }
            }
        }
        check++;
        printf("\n");
    }
}
void main(){
    getInput();

    int index1 = 0;
    int index2 = SIZE / 2 ;
    displayArray("Original array:\n");

    pthread_t thread1; // This is the thread to sort first half of the array
    pthread_create(&thread1, NULL, &bubbleSort, (void*) &index1);
    pthread_join(thread1, NULL);   
    displayArray("Array after sorting the first half:\n");

    pthread_t thread2; // This is the thread to sort second half of the array
    pthread_create(&thread2, NULL, &bubbleSort, (void*) &index2);
    pthread_join(thread2, NULL);
    displayArray("Array after sorting the first half & second half:\n");

    pthread_t thread3; // This is the thread to merge 2 half if the array into another array in ascending order
    pthread_create(&thread3, NULL, &join, (void*) &index2);
    pthread_join(thread3, NULL);
    displayMergedArray("Merged array:\n");

}
