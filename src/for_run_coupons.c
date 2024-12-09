#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "coupons.h"
#include <sys/stat.h>
#include <sys/types.h>

char *coupon_path = "data/coupons.csv";

// Function to manage coupons
void run_coupons() {
    // Clean expired coupons
    printf("Deleting expired coupons...\n");
    int expired_count = clean_expired_coupons();
    if (expired_count > 0) {
        printf("%d expired coupons were removed.\n", expired_count);
    } else {
        printf("No expired coupons found.\n");
    }

    // Display menu
    int choice;
    printf("\nCoupon Management Menu:\n");
    printf("1. Create a Coupon\n");
    printf("2. View All Coupons\n");
    printf("3. Delete a Coupon\n");
    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        return;
    }

    // Process user choice
    switch (choice) {
        case 1: // Create a coupon
            if (create_coupon() == 0) {
                printf("Coupon created successfully.\n");
            } else {
                printf("Failed to create coupon.\n");
            }
            break;
        case 2: // View all coupons
            display_coupons();
            break;
        case 3: { // Delete a coupon
            char coupon_code[20];
            printf("Enter the coupon code to delete: ");
            if (scanf("%19s", coupon_code) != 1) {
                printf("Invalid input.\n");
            } else {
                delete_coupon(coupon_code);
            }
            break;
        }
        default: // Invalid choice
            printf("Invalid choice. Returning to main menu.\n");
            break;
    }
}

int main() {
    // Call the function to manage coupons
    run_coupons();
    return 0;
}
