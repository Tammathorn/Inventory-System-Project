
#include <stdio.h>

int main() {

    // -- For login system --
    
    int choice;
    printf("What is your role : ");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            printf("Welcome customer");
            break;

        case 2:
            printf("Welcome owner");
            break;
    }

    // ---------------
    return 0;
}