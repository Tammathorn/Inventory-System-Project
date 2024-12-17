#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "inventory.h"

// Function prototypes
void login_system();

// Path to data
char *data_path = "data/inventory.csv";
char *basket_path = "data/Cart.csv";

int main() {
    login_system();
    return 0;
}

void login_system() {
    int choice;
    do {
        printf("What is your role? 1 for customer and 2 for owner: ");
        scanf("%d", &choice);

        if (choice != 1 && choice != 2) {
            printf("Invalid choice! Exiting...\n");
            exit(0); 
        }   
    }while (choice != 1 && choice != 2);
    

    switch(choice) {
        case 1:
            printf("Welcome customer!\n");
            customer_system();  // Call the customer system
            break;

        case 2:
            printf("Welcome owner!\n");

            const char *file_path = "inventory.csv";  
            int action_choice;

            // -- CRUD Operations Menu for Owner --
            while (1) {
                printf("\nInventory Management System for Owner\n");
                printf("1. Add Product\n");
                printf("2. View Products\n");
                printf("3. Edit Product\n");
                printf("4. Delete Product\n");
                printf("5. Save Inventory to File\n");
                printf("6. Exit to Main Menu\n");
                printf("Enter your choice: ");
                scanf("%d", &action_choice);

                switch (action_choice) {
                    case 1:
                        printf("==================================================================================================================\n");
                        create_product();
                        break;
                    case 2:
                        printf("==================================================================================================================\n");
                        view_products();
                        break;
                    case 3:
                        printf("==================================================================================================================\n");
                        edit_product();
                        break;
                    case 4:
                        printf("==================================================================================================================\n");
                        delete_product();
                        break;
                    case 5:
                        printf("==================================================================================================================\n");
                        save_to_file(file_path);
                        break;
                    case 6:
                        printf("==================================================================================================================\n");
                        printf("Returning to main menu.\n");
                        printf("==================================================================================================================\n");
                        login_system();
                        break;
                    default:
                        printf("Invalid choice! Please try again.\n");
                }
            }
            break;
    }
    return ;
}