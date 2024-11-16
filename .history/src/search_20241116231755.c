#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search(char *path) {
    
    //  -- input and check if it has or not -- 

    // input string 
    char string[10];
    printf("\nSearch : ");
    scanf("%s", string);

    int choice;
    do {
        printf("Enter your choice 1 for name, 2 for type : ");
        scanf("%d", &choice);
    }

    while (choice != 1 && choice != 2);


    // check file 
    FILE *data = fopen(path, "r");
    char name[10]; 
    char type[10];
    if (data == NULL) {
        printf("file not found");
    }

    else {

        while (!feof(data) ) {
            fscanf(data, "%s%s", name, type);

            if (choice == 1 && strcmp(string, name) == 0) {
                printf("Found name");
            }

            if (choice == 2 && strcmp(string, type) == 0) {
                printf("Found type");
            }
            
        }
    }

    fclose(data);

    return 0;
}