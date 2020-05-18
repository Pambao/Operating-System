#include <stdio.h>
#include<stdlib.h>

int main(){
    FILE* fileRead;
    FILE* fileWrite;
    char holder;
    char readFile[20];
    char writeFile[20];
    printf("Enter file name you want to copy from\n");
    scanf("%s", readFile);
    fileRead = fopen(readFile, "r");
    if (fileRead == NULL){ // if file not exist
        printf("File is not exist");
        return 1;
    }
    printf("Enter file name you want to copy to\n");
    scanf("%s", writeFile);
    fileWrite = fopen(writeFile, "w");
    if(fileWrite == NULL){
        printf("File is not exist");
        return 1;
    }
    while( (holder = fgetc(fileRead)) != EOF){
        fputc(holder, fileWrite);
    }

    printf("File has been copied!");

    fclose(fileRead);
    fclose (fileWrite);
        return 0;
}đâsd
