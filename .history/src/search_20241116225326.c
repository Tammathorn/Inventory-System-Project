#include <stdio.h>

int search() {

    // input and check if it has or not -- 

    // input string 
    char *string;
    printf("Search : ");
    scanf("%s", string);

    int choice;
    
    

    do {
        printf("Enter your choice 1 for name, 2 for type : ");
        scanf("%d", &choice);
    }

    while (choice != 1 && choice != 2);
    return 0;
}