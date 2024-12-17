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
        perror("Error opening coupon file");
        return;
    }

    printf("Reading coupons from: %s\n", coupon_path); // แจ้งให้รู้ว่าไฟล์เปิดสำเร็จ

    char line[256];
    int count = 0;

    printf("==========================================================================================================================\n");
    printf("| %-20s | %-20s | %-20s | %-15s | %-15s | %-15s |\n", 
           "Coupon Code", "Product Name", "Category", "Discount Price", "Discount Percent", "Expiry Date");
    printf("==========================================================================================================================\n");

    while (fgets(line, sizeof(line), file)) {
        coupon_t coupon;

        // อ่านข้อมูลจากบรรทัด CSV โดยใช้ sscanf
        int matched = sscanf(line, "%19[^,],%49[^,],%29[^,],%f,%d,%10s", 
                             coupon.code, 
                             coupon.product_name, 
                             coupon.category, 
                             &coupon.discount_price, 
                             &coupon.discount_percent, 
                             coupon.expiry_date);

        if (matched == 6) { // ตรวจสอบว่ามีการอ่านครบทุกคอลัมน์
            // แทนค่าว่างเป็น "N/A" ถ้าข้อมูลว่าง
            if (strlen(coupon.product_name) == 0) {
                strcpy(coupon.product_name, "N/A");
            }
            if (strlen(coupon.category) == 0) {
                strcpy(coupon.category, "N/A");
            }

            printf("| %-20s | %-20s | %-20s | %-15.2f | %-15d | %-15s |\n",
                   coupon.code, 
                   coupon.product_name, 
                   coupon.category, 
                   coupon.discount_price, 
                   coupon.discount_percent, 
                   coupon.expiry_date);
            count++;
        }
    }

printf("==========================================================================================================================\n");
    fclose(file);
}


int load_coupons(coupon_t *coupons, int *coupon_count, const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1; // Return error if file can't be opened
    }

    *coupon_count = 0; // Reset coupon count

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%19[^,],%49[^,],%29[^,],%f,%d,%10s", 
                   coupons[*coupon_count].code, 
                   coupons[*coupon_count].product_name, 
                   coupons[*coupon_count].category, 
                   &coupons[*coupon_count].discount_price, 
                   &coupons[*coupon_count].discount_percent, 
                   coupons[*coupon_count].expiry_date) == 6) {
            (*coupon_count)++; // Successfully read a line, increment count
        }
    }

    fclose(file);
    return 0; // Success
}

// delete coupons by its code
int delete_coupon(const char *coupon_code) {
    FILE *file = fopen(coupon_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    FILE *temp_file = fopen("data/temp.csv", "w");
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
        rename("data/temp.csv", coupon_path);
        printf("Coupon deleted successfully.\n");
    } else {
        printf("Coupon not found.\n");
        remove("data/temp.csv");
    }

    return found ? 0 : -1;
}

