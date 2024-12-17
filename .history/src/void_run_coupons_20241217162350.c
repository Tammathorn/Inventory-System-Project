#include "coupons.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

char *coupon_path = "data/coupons.csv";

// Function to automatically clean up expired coupons
void auto_cleanup_expired_coupon() {
    printf("Cleaning up expired coupons...\n");
    int expired_count = clean_expired_coupons();
    printf("Auto cleanup complete. Expired coupons removed: %d\n", expired_count);
}

void manage_coupons() {
    int running = 1;
    coupon_t coupons[100];       // Declare coupons array once
    int coupon_count = 0;        // Variable to track loaded coupons

    while (running) {
        printf("\n===== Coupon Management System =====\n");
        printf("1. Create a Coupon\n");
        printf("2. View All Coupons\n");
        printf("3. Delete a Coupon\n");
        printf("4. Back\n");
        printf("Enter your choice: ");

        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting program.\n");
            return;
        }

        switch (choice) {
            case 1: {
                // Create a new coupon
                if (create_coupon() == 0) {
                    printf("Coupon created successfully.\n");
                } else {
                    printf("Failed to create coupon.\n");
                }
                break;
            }
            case 2: {
                // View all coupons
                if (load_coupons(coupons, &coupon_count, coupon_path) == 0) {
                    display_coupons(coupons, coupon_count);
                } else {
                    printf("Failed to load coupons.\n");
                }
                break;
            }
            case 3: {
                // Load coupons before deleting
                if (load_coupons(coupons, &coupon_count, coupon_path) == 0) {
                    display_coupons(coupons, coupon_count);

                    // Delete a coupon by code
                    char coupon_code[20];
                    printf("Enter the coupon code to delete: ");
                    if (scanf("%19s", coupon_code) != 1) {
                        printf("Invalid input.\n");
                    } else {
                        if (delete_coupon(coupon_code) == 0) {
                            printf("Coupon deleted successfully.\n");
                        } else {
                            printf("Coupon not found.\n");
                        }
                    }
                } else {
                    printf("Failed to load coupons.\n");
                }
                break;
            }
            case 4: {
                printf("Back..\n");
                running = 0; // Stop the loop
                break;
            }
            default: {
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
                break;
            }
        }
    }
}