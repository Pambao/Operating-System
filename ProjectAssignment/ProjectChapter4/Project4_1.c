/*
Operating System 
Project 4_1
Pham Gia Bao
CS2017
Vietnamese-German University
*/
//Program must be compiled with the tag "-lpthread"
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define M_SIZE 9
#define N_SIZE 9

struct Parameters{      //Define data structre as paramter of checkSquare thread
    int row, column; 
};
int sudokuTable [M_SIZE][N_SIZE] = {};
int indexCounter = 0; //Counter for the index of the checkResult array
int checkResult[11]={}; // Result of each thread will be stored here

void printTable (int table[M_SIZE][N_SIZE]){ // This function is used to print the whole table
    printf("Your inputed sudoku table:\n");
    printf("*****************\n");
    for(int i=0;i<M_SIZE;i++){
        for(int j=0;j<N_SIZE;j++){
            printf("%d ", table[i][j]);
        }
            printf("\n");
    }
    printf("*****************\n");
}

void* checkRows(){ // This thread is used to check all rows of the table
    for(int row = 0; row < M_SIZE; row++){
            int histogram[9]={}; // This array is used to store the numbers of time the digit appear in each row 
        for(int col = 0; col < N_SIZE; col++){
            histogram[sudokuTable[row][col]-1] ++;
        }
        for(int i=0;i<9;i++){
            if(histogram[i] != 1){ // If the # of occurences of the digit in row is not equal to 1 then the thread will be terminated
                indexCounter++;
                return (void*) -1;
            }
        }
    }
        checkResult[indexCounter++] = 1; // Otherwise mark the next index of the result array by 1
}

void* checkCols(){ // This thread is used to check all columns of the table
    for(int col = 0; col < N_SIZE; col++){
        int histogram[9]={}; // This array is used to store the numbers of time the digit appear in each column
        for(int row = 0; row < M_SIZE ; row++){
            histogram[sudokuTable[row][col]-1] ++;
        }
        for(int i = 0; i<9; i++){ // If the # of occurences of the digit in column is not equal to 1 then the thread will be terminated
            if(histogram[i] != 1){
                indexCounter++;
                return (void*) -1;
            }
        }
    }
    checkResult[indexCounter++] = 1; // Otherwise mark the next index of the result array by 1
}

void* checkSquare(void* indexPointer){ // This thread is used to check all 3x3 squares of the sudoku table
// The paramter of this thread will be the index of the frist position in 3x3 table (Ex:{0,0}, {0,6}, {3,0})
    struct Parameters index = *((struct Parameters*) indexPointer);
    int histogram[9] ={}; // This array is used to store the numbers of time the digit appear in each 3x3 square
    for(int row = index.row; row < index.row + 3; row ++){
        for(int col = index.column; col < index.column+ 3 ; col++){
            histogram[sudokuTable[row][col] - 1] ++;
        }
    }
        for(int i = 0 ; i<9 ; i++){ // If the # of occurences of the digit in square is not equal to 1 then the thread will be terminated
            if (histogram[i] != 1){
                indexCounter++;
                return (void*) -1;
            }
    }
    checkResult[indexCounter++] = 1; // Otherwise mark the next index of the result array by 1
}

void createParameter(struct Parameters index[9]){ // This function is used to create paramter of each 3x3 table and stored in the "index" array
    int counter = 0;
    for(int row = 0; row<9; row+=3){
        for(int col = 0; col <9; col  +=3){
            index[counter++] = (struct Parameters) {row,col};
        }
    }
}

void getInput(){ // This function is used to get input of the table
    int inRowCounter = 0;
    while(inRowCounter < 9){

        printf("Enter row %dth\n", inRowCounter +1);
        printf("Each digit must be separated by a space\n");
        printf("Each digit will correspond to an arrow above it\n");
        for(int row=0; row<2;row++){
            for(int col=0;col<18; col++){
                if((col==0 || col%2 ==0)&& row==0){
                    printf("| ");
                } else if((col==0 || col%2 ==0)&& row==1){
                    printf("v ");
                }
            }
            printf("\n");
        }

        char inputString[50];
        int inputInteger[9] ={};
        fgets(inputString, 50, stdin);

        for(int col = 0; col<17 ;col++){
            if(col == 0 || (col%2) ==0){
                if((isdigit(inputString[col]) ==1) 
                    && (inputString[col] - '0' >0)
                    && (inputString[col] - '0' <10) 
                ){
                    sudokuTable[inRowCounter][col/2] = inputString[col] - '0'; 
                } else {
                    printf("\t\t*************\n");
                    printf("Your row you have inputed has some errors\n");
                    printf("Enter it again\n");
                    inRowCounter --;
                    break;
                }
            }
        }
                    inRowCounter ++;
    }
}

void main (){
    getInput();
    printTable(sudokuTable);
    
    struct Parameters a[9]; 
    createParameter(a); // This function call is used to generate the paramters of each 3x3 table

    pthread_t threadId[11]; // Array to store 11 thread
    for(int i = 0; i < 9; i++){ // The first 9 thread will check 9 squares
        pthread_create(&threadId[i], NULL, &checkSquare, (void*) &a[i]); // Pass each paramters index in array "a" to each thread
        pthread_join(threadId[i], NULL);
    }

    pthread_create(&threadId[9], NULL, &checkRows, NULL); // Thread 9 is used to check rows
    pthread_join(threadId[9], NULL);
    pthread_create(&threadId[10], NULL, &checkCols, NULL); // Thread 10 is used to check columns
    pthread_join(threadId[10], NULL);
    
    int checkResultCounter = 0; // This variable is used to count the number of thread return the valid reuslt
    for(int i=0; i<11; i++){
        if(checkResult[i] == 1)
            checkResultCounter ++;
    }

    if(checkResultCounter == 11){ // Display the result to the screen
        printf("Your sudoku table is VALID\n");
    } else {
        printf("Your sudoku table is INVALID\n");
    }

    
}
