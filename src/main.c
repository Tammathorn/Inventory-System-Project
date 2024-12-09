#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "inventory.h"
#include "coupons.h"

int login_system();

// path to data
char *data_path = "data/test.csv";
char *basket_path = "data/basket.csv";
char *coupon_path = "data/coupons.csv";

int main() {
    
    // -- For login system --
    int choice;

    login_system();
    // ---------------
    
    return 0;
    
}

int login_system() {
    
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

            customer_system();
            
            break;

        case 2:
            printf("Welcome owner!\n");

            // -- For show list of data --
            show_list_product(data_path);

            // CRUD or coupon here! 

            // Run coupon management operations
            printf("\nManaging Coupons...\n");

            // Example: 
            // 1. Create a coupon
            run_coupons(coupon_path, 1, NULL);

            // 2. View all coupons
            run_coupons(coupon_path, 2, NULL);

            // 3. Delete a specific coupon
            run_coupons(coupon_path, 3, "SPECIAL10");

            break;
    }
    return 0;
}
