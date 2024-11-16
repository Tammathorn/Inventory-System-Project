#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search(char *path, int *data_type) {
    
    //  -- input and check if it has or not -- 

    // input string 
    char string[10];
    printf("\nSearch : ");
    scanf("%s", string);

    *data_type = choice;


    // check file 
    FILE *data = fopen(path, "r");
    char name[10]; 
    if (data == NULL) {
        printf("file not found");
    }

    else {

        while (!feof(data) ) {
            fscanf(data, "%s", name);

            if (strcmp(string, name) == 0) {
                printf("Found name");
                return name;
            }

            else {
                printf("Name is not found");
            }

            
        }
    }

    fclose(data);

    return 0;
}