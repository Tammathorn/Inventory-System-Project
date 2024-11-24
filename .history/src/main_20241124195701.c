#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"

int show_list_product();
int login_system();
int customer_system();

// path to data
char *data_path = "data/test.csv";
char *basket_path = "data/basket.csv";

int main() {
    
    // -- For login system --
    int choice;

    login_system(data_path);
    // ---------------

    return 0;
}

int login_system(char *data_path) {
    
    int choice;
    
    do {
        printf("What is your role 1 for customer and 2 for owner : ");
        scanf("%d", &choice);
    }

    while (choice != 1 && choice != 2);


    switch(choice) {
        case 1:
            printf("Welcome customer!\n");

            // -- For show list of data --
            show_list_product(data_path);

            customer_system(data_path);
            break;

        case 2:
            printf("Welcome owner!\n");

            // -- For show list of data --
            show_list_product(data_path);

            break;
    }
    return 0;
}
