#include <stdio.h>
#include <string.h>
#include "inventory.h"

//restock a selected item
void auto_restock(char *product_name, int threshold, int restock_amount) {
    int found = 0;

    printf("\n===== Auto Restocking for Specific Product =====\n");

    for (int i = 0; i < data_length; i++) {
        if (strcmp(data[i].name, product_name) == 0) { //check product name
            found = 1;

            printf("Product found: %s (Current Quantity: %d)\n", 
                   data[i].name, data[i].quantity);
            //check if below treshold or not
           if (data[i].quantity < threshold) {
                printf("Threshold: %d | Restocking amount: %d\n", threshold, restock_amount);

                data[i].quantity += restock_amount; // เพิ่มจำนวนสินค้า
                printf("New quantity for %s: %d\n", data[i].name, data[i].quantity);
            } else {
                printf("Product quantity is above the threshold. No restocking needed.\n");
            }
            break;
        }
    }
    //If item not found
    if (!found) {
        printf("Error: Product '%s' not found in the inventory.\n", product_name);
        return;
    }

   //Svae to csv file
    save_system(data, data_length, data_path);
    printf("Restocking process complete. Data saved to file.\n");
}

void auto_restock_input(char *product_name, int *threshold, int *restock_amount) {
    do {
        printf("Enter product name to restock: ");
        scanf("%s", product_name);
    } while (strlen(product_name) == 0); // ชื่อสินค้าห้ามว่าง

    do {
        printf("Enter restock threshold (positive number): ");
        scanf("%d", threshold);
        if (*threshold <= 0) {
            printf("Error: Threshold must be a positive number.\n");
        }
    } while (*threshold <= 0);

    do {
        printf("Enter amount to restock (positive number): ");
        scanf("%d", restock_amount);
        if (*restock_amount <= 0) {
            printf("Error: Restock amount must be a positive number.\n");
        }
    } while (*restock_amount <= 0);
}
