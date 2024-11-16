#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search(char *path, char *data_name) {
    
    //  -- input and check if it has or not -- 

    // input string 
    char string[10];
    printf("\nSearch : ");
    scanf("%s", string);

    // check file 
    FILE *data = fopen(path, "r");
    char name[10]; 
    if (data == NULL) {
        printf("file not found");
    }

    else {

        char *temp = *data_name;
        while (!feof(data) ) {
            fscanf(data, "%s", name);

            if (strcmp(string, name) == 0) {
                printf("Found name");
                *data_name = *name;
            }
            
        }

        if (*temp == *data_name) {
            printf("Name is not found");
        }
    }

    fclose(data);

    return 0;
}