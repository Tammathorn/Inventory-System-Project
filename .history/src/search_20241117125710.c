#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search(char *path, char *data_name, char *data_type, int *found) {
    
    //  -- input and check if it has or not -- 

    // input string 
    char string[10];
    printf("\nSearch : ");
    scanf("%s", string);

    // check file 
    FILE *data = fopen(path, "r");

    int number;
    float price;
    char name[10];
    char type[10];

    if (data == NULL) {
        printf("file not found");
    }

    else {

        
        while (!feof(data) ) {
            fscanf(data, "%10s%10s%d%f", name, type, &number, &price);
            if (strcmp(string, name) == 0) {
                printf("Found name\n");
                *found = 1;

                strcmp(data_name, name);
                strcmp(data_type, type);

                fclose(data);
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