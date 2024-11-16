#include <stdio.h>
#include <stdlib.h>

int search(char *path) {

    //  -- input and check if it has or not -- 

    // input string 
    char *string;
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
    char *name; 
    char *type;
    if (data == NULL) {
        printf("file not found");
    }

    else {

        while (!feof(data) ) {
            fscanf(data, "%s%s", name, type);

            if (choice == 1 && string == name) {
                printf("Found name");
            }

            if (choice == 2 && string == type) {
                printf("Found type");
            }
            
        }
    }

    return 0;
}