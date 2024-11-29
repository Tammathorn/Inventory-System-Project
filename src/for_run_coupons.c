#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "coupons.h"
#include <sys/stat.h>
#include <sys/types.h>



char *coupon_path = "data/coupons.csv";

int main() {
    printf("Delete expried coupons\n");
    int expired_count = clean_expired_coupons();
    if (expired_count > 0) {
        printf("%d expired coupons were removed.\n", expired_count);
    } else {
        printf("No expired coupons found.\n");
    }

    int choice;
    printf("1. Create a Coupon\n");
    printf("2. View All Coupons\n");
    printf("3. Delete a Coupon\n");
    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        return -1;
    }

    if (choice == 1) {
        if (create_coupon() == 0) {
            printf("Coupon created successfully.\n");
        } else {
            printf("Failed to create coupon.\n");
        }
    } else if (choice == 2) {
        display_coupons();
    } else if (choice == 3) {
        char coupon_code[20];
        printf("Enter the coupon code to delete: ");
        if (scanf("%19s", coupon_code) != 1) {
            printf("Invalid input.\n");
        } else {
            delete_coupon(coupon_code);
        }
    } else {
        printf("Invalid choice. Exiting the program.\n");
    }

    return 0;
}
