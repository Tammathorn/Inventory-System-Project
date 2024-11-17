#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search(char *path, char *data_name, int *found) {
    
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

        
        while (!feof(data) ) {
            fscanf(data, "%s", name);

            if (strcmp(string, name) == 0) {
                printf("Found name\n");
                strcpy(data_name, name);
                *found = 1;
                fclose(data);
                return 0;
            }

            else if (strcmp(string, "x")) {
                found = 2;
                return 0;
            }
            
        }

        if (*found == 0) {
            printf("Name is not found\n");
        }
        
    }
}