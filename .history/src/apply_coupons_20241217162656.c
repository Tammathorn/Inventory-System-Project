#include "coupons.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"

extern int basket_length;             // Number of items in the basket
extern struct file_data basket[];     // Structure for items in the basket

// Function to delete a used coupon
void delete_used_coupon(const char *used_coupon_code) {
    FILE *file = fopen(coupon_path, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    FILE *temp_file = fopen("data/temp.csv", "w"); // Temporary file
    if (temp_file == NULL) {
        perror("Error opening temporary file");
        fclose(file);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char current_code[20];
        sscanf(line, "%19[^,]", current_code);

        // Copy all coupons except the used one
        if (strcmp(current_code, used_coupon_code) != 0) {
            fputs(line, temp_file);
        }
    }

    fclose(file);
    fclose(temp_file);

    // Replace the original coupon file with the updated file
    if (remove(coupon_path) != 0 || rename("data/temp.csv", coupon_path) != 0) {
        perror("Error updating coupon file");
    } else {
        printf("Coupon '%s' removed successfully.\n", used_coupon_code);
    }
}

// Function to apply a coupon
void apply_coupon() {
    char coupon_code[20];            // Variable to store the coupon code
    coupon_t coupons[100];           // Array to store loaded coupons
    int coupon_count = 0;

    // 1. Load coupons from the file
    FILE *file = fopen(coupon_path, "r");
    if (file == NULL) {
        perror("Error opening coupon file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        coupon_t temp_coupon;
        if (sscanf(line, "%19[^,],%49[^,],%29[^,],%f,%d,%10s",
                   temp_coupon.code,
                   temp_coupon.product_name,
                   temp_coupon.category,
                   &temp_coupon.discount_price,
                   &temp_coupon.discount_percent,
                   temp_coupon.expiry_date) == 6) {
            coupons[coupon_count++] = temp_coupon; // Store valid coupons
        }
    }
    fclose(file);

    // 2. Display available coupons to the user
    printf("\nAvailable Coupons:\n");
    printf("================================================================================================================\n");
    printf("| %-20s | %-20s | %-20s | %-15s | %-15s | %-15s |\n",
           "Coupon Code", "Product Name", "Category", "Discount Price", "Discount Percent", "Expiry Date");
    printf("================================================================================================================\n");

    for (int i = 0; i < coupon_count; i++) {
        printf("| %-20s | %-20s | %-20s | %-15.2f | %-15d | %-15s |\n",
               coupons[i].code,
               strlen(coupons[i].product_name) > 0 ? coupons[i].product_name : "N/A",
               strlen(coupons[i].category) > 0 ? coupons[i].category : "N/A",
               coupons[i].discount_price,
               coupons[i].discount_percent,
               coupons[i].expiry_date);
    }
    printf("================================================================================================================\n");

    // 3. Prompt user for a coupon code
    printf("Enter a valid coupon code to apply (or 'none' to skip): ");
    scanf("%19s", coupon_code);

    if (strcmp(coupon_code, "none") == 0) {
        printf("No coupon applied.\n");
        return; // Exit if the user chooses not to apply any coupon
    }

    // 4. Validate and apply the coupon to matching products in the basket
    int coupon_found = 0;
    for (int i = 0; i < coupon_count; i++) {
        if (strcmp(coupons[i].code, coupon_code) == 0) {
            printf("Coupon '%s' found!\n", coupon_code);
            coupon_found = 1;

            for (int j = 0; j < basket_length; j++) {
                if ((strlen(coupons[i].product_name) > 0 && strcmp(coupons[i].product_name, basket[j].name) == 0) ||
                    (strlen(coupons[i].category) > 0 && strcmp(coupons[i].category, basket[j].type) == 0)) {

                    // Apply discount
                    if (coupons[i].discount_price > 0) {
                        basket[j].price -= coupons[i].discount_price;
                        if (basket[j].price < 0) basket[j].price = 0; // Prevent negative prices
                    } else if (coupons[i].discount_percent > 0) {
                        basket[j].price *= (1 - (coupons[i].discount_percent / 100.0));
                    }

                    printf("Coupon applied to product '%s'. New price: %.2f\n", basket[j].name, basket[j].price);
                }
            }

            // 5. Remove the used coupon
            delete_used_coupon(coupon_code);
            break; // Exit after applying the coupon
        }
    }

    if (!coupon_found) {
        printf("Invalid coupon code. No coupon applied.\n");
    }
}
