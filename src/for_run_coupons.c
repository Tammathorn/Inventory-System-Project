#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coupons.h"
#include <sys/stat.h>
#include <sys/types.h>

// Coupon file path
char *coupon_path = "data/coupons.csv";

// Function to manage coupons
void run_coupons(const char *data_path, int operation, const char *coupon_code) {
    // Clean expired coupons
    printf("Deleting expired coupons...\n");
    int expired_count = clean_expired_coupons();
    if (expired_count > 0) {
        printf("%d expired coupons were removed.\n", expired_count);
    } else {
        printf("No expired coupons found.\n");
    }

    // Perform the requested operation
    switch (operation) {
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
        case 3: // Delete a specific coupon
            if (coupon_code != NULL && strlen(coupon_code) > 0) {
                delete_coupon(coupon_code);
            } else {
                printf("Invalid coupon code provided for deletion.\n");
            }
            break;
        default: // Invalid operation
            printf("Invalid operation. Exiting.\n");
            break;
    }
}
