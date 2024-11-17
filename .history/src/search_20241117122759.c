#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search(char *path, char *data_name, char *data_type, int *data_number, float *data_price, int *found) {
    
    //  -- input and check if it has or not -- 

    // input string 
    char string[10];
    printf("\nSearch : ");
    scanf("%s", string);

    // check file 
    FILE *data = fopen(path, "r");

    int number;
    float price;

    if (data == NULL) {
        printf("file not found");
    }

    else {

        
        while (!feof(data) ) {
            fscanf(data, "%s%s%d%f", data_name, data_type, number, price);
            if (strcmp(string, data_name) == 0) {
                printf("Found name\n");
                *found = 1;
                fclose(data);
                *data_number = number;
                *data_price = price;
                return 0;
            }

            else if (strcmp(string, "x") == 0) {
                *found = 2;
                return 0;
            }
            
        }

        if (*found == 0) {
            printf("Name is not found\n");
        }
        
    }

    return 0;
}