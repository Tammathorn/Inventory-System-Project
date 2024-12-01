//Manage and Display coupons by its code
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coupons.h"

extern char *coupon_path;

// Display all coupons
void display_coupons() {
    FILE *file = fopen(coupon_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[256];

    // Print header with separators
    printf("+-----------------+----------------------+-----------------+----------------------+--------------------+-----------------+\n");
    printf("| %-15s | %-20s | %-15s | %-20s | %-18s | %-15s |\n", 
           "CouponCode", "ProductName", "ProductType", "DiscountPrice", "DiscountPercent", "ExpiryDate");
    printf("+-----------------+----------------------+-----------------+----------------------+--------------------+-----------------+\n");

    // Print coupon data
    while (fgets(line, sizeof(line), file)) {
        char couponCode[20], productName[20], productType[20], discountPrice[20], discountPercent[20], expiryDate[20];
        sscanf(line, "%19[^,],%19[^,],%19[^,],%19[^,],%19[^,],%19[^,\n]", 
               couponCode, productName, productType, discountPrice, discountPercent, expiryDate);

        printf("| %-15s | %-20s | %-15s | %-20s | %-18s | %-15s |\n", 
               couponCode, productName, productType, discountPrice, discountPercent, expiryDate);
    }

    printf("+-----------------+----------------------+-----------------+----------------------+--------------------+-----------------+\n");
    fclose(file);
}

// delete coupons by its code
int delete_coupon(const char *coupon_code) {
    FILE *file = fopen(coupon_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    FILE *temp_file = fopen("temp.csv", "w");
    if (temp_file == NULL) {
        perror("Error opening temporary file");
        fclose(file);
        return -1;
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        char current_code[20];
        sscanf(line, "%19[^,]", current_code);

        // Skip writing the coupon to delete
        if (strcmp(current_code, coupon_code) == 0) {
            found = 1;
            continue;
        }

        fputs(line, temp_file);
    }

    fclose(file);
    fclose(temp_file);

    // Replace original file with the updated file
    if (found) {
        remove(coupon_path);
        rename("temp.csv", coupon_path);
        printf("Coupon deleted successfully.\n");
    } else {
        printf("Coupon not found.\n");
        remove("temp.csv");
    }

    return found ? 0 : -1;
}

