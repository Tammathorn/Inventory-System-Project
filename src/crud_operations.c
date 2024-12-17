#include "inventory.h"
#include <stdio.h>

// Global variables
product_t inventory[MAX_PRODUCTS]; // Array to store products
int product_count = 0;             // Number of products in inventory

// Function to create a new product
void create_product() {
    if (product_count >= MAX_PRODUCTS) {
        printf("Inventory is full! Cannot add more products.\n");
        return;
    }

    product_t new_product;
    new_product.id = product_count + 1;

    // Get product details from the user
    printf("Enter product name: ");
    scanf(" %[^\n]", new_product.name);

    printf("Enter quantity: ");
    scanf("%d", &new_product.quantity);

    printf("Enter price: ");
    scanf("%f", &new_product.price);

    // Add the new product to the inventory
    inventory[product_count++] = new_product;
    printf("Product created successfully!\n");
}

// Function to display all products in the inventory
void view_products() {
    if (product_count == 0) {
        printf("No products available in the inventory.\n");
        return;
    }

    // Print product details in a table format
    printf("ID\tName\t\tQuantity\tPrice\n");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < product_count; i++) {
        printf("%d\t%s\t\t%d\t\t%.2f\n", inventory[i].id, inventory[i].name, inventory[i].quantity, inventory[i].price);
    }
}

// Function to edit a product by its ID
void edit_product() {
    int product_id;

    // Prompt the user to enter the product ID
    printf("Enter product ID to edit: ");
    scanf("%d", &product_id);

    // Validate product ID
    if (product_id < 1 || product_id > product_count) {
        printf("Invalid product ID!\n");
        return;
    }

    product_t *product = &inventory[product_id - 1]; // Get the product to edit

    // Allow the user to update product details
    printf("Editing Product - %s (ID: %d)\n", product->name, product->id);

    printf("Enter new name (current: %s): ", product->name);
    scanf(" %[^\n]", product->name);

    printf("Enter new quantity (current: %d): ", product->quantity);
    scanf("%d", &product->quantity);

    printf("Enter new price (current: %.2f): ", product->price);
    scanf("%f", &product->price);

    printf("Product updated successfully!\n");
}

// Function to delete a product by its ID
void delete_product() {
    int product_id;

    // Prompt the user to enter the product ID
    printf("Enter product ID to delete: ");
    scanf("%d", &product_id);

    // Validate product ID
    if (product_id < 1 || product_id > product_count) {
        printf("Invalid product ID!\n");
        return;
    }

    // Shift all products after the deleted product one position to the left
    for (int i = product_id - 1; i < product_count - 1; i++) {
        inventory[i] = inventory[i + 1];
    }

    product_count--; // Decrease the product count
    printf("Product deleted successfully!\n");
}

// Function to save the inventory to a CSV file
void save_to_file(const char *file_path) {
    FILE *file = fopen(file_path, "w");
    if (!file) {
        printf("Error saving data to file.\n");
        return;
    }

    // Write product data to the file
    for (int i = 0; i < product_count; i++) {
        fprintf(file, "%d,%s,%d,%.2f\n", inventory[i].id, inventory[i].name, inventory[i].quantity, inventory[i].price);
    }

    fclose(file);
    printf("Data saved successfully!\n");
}

// Function to load the inventory from a CSV file
void load_data_from_file(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        printf("No existing data found.\n");
        return;
    }

    product_count = 0;

    // Read product data from the file
    while (fscanf(file, "%d,%49[^,],%d,%f\n", 
                  &inventory[product_count].id, 
                  inventory[product_count].name, 
                  &inventory[product_count].quantity, 
                  &inventory[product_count].price) == 4) {
        product_count++;
    }

    fclose(file);
    printf("Data loaded successfully!\n");
}


