#include <stdio.h>

#define maxChar 20
int editFile(char *fileName, int line) {

    char temp[maxChar];
    strcpy(temp, "temp");

    FILE *temp = fopen(temp, "r+");
    FILE *data = fopen(fileName, "r+");

    int index = 0;
    while (!feof(data)) {
        
        char name[maxChar];
        int quantity;
        float price;

        fscanf(data, "%10s %d %.2f");

        if (index == line) {

            char input[maxChar];

            printf("Value you want to change");
            scanf("%s", input);

            while (1) {
                if (strcmp(input, "quantity")) {
                    break;
                }
            }

            
        }

        else {
            fprintf(data, "%s %d %f", name, price, quantity);
        }
    }
}