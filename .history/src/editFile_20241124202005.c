#include <stdio.h>

#define maxLine 100
int editFile(char *fileName) {

    char temp[maxLine];
    strcpy(temp, "temp");

    FILE *temp = fopen(temp, "a");
    FILE *data = fopen(fileName, "r+");


}