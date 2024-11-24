#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_NAME_LENGTH 50

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    int quantity;
    float price;
} product_t;

product_t inventory[MAX_PRODUCTS];
int product_count = 0;

// Function to create a product
void create_product() {
    if (product_count >= MAX_PRODUCTS) {
        printf("Inventory is full! Cannot add more products.\n");
        return;
    }

    product_t new_product;
    new_product.id = product_count + 1;

    printf("Enter product name: ");
    scanf(" %[^\n]", new_product.name);

    printf("Enter quantity: ");
    scanf("%d", &new_product.quantity);

    printf("Enter price: ");
    scanf("%f", &new_product.price);

    inventory[product_count++] = new_product;
    printf("Product created successfully!\n");
}

// Function to view all products
void view_products() {
    if (product_count == 0) {
        printf("No products available in the inventory.\n");
        return;
    }

    printf("ID\tName\t\tQuantity\tPrice\n");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < product_count; i++) {
        printf("%d\t%s\t\t%d\t\t%.2f\n", inventory[i].id, inventory[i].name, inventory[i].quantity, inventory[i].price);
    }
}

// Function to edit a product
void edit_product() {
    int product_id;
    printf("Enter product ID to edit: ");
    scanf("%d", &product_id);

    if (product_id < 1 || product_id > product_count) {
        printf("Invalid product ID!\n");
        return;
    }

    product_t *product = &inventory[product_id - 1];
    printf("Editing Product - %s (ID: %d)\n", product->name, product->id);

    printf("Enter new name (current: %s): ", product->name);
    scanf(" %[^\n]", product->name);

    printf("Enter new quantity (current: %d): ", product->quantity);
    scanf("%d", &product->quantity);

    printf("Enter new price (current: %.2f): ", product->price);
    scanf("%f", &product->price);

    printf("Product updated successfully!\n");
}

// Function to delete a product
void delete_product() {
    int product_id;
    printf("Enter product ID to delete: ");
    scanf("%d", &product_id);

    if (product_id < 1 || product_id > product_count) {
        printf("Invalid product ID!\n");
        return;
    }

    // Shift all products after the deleted one
    for (int i = product_id - 1; i < product_count - 1; i++) {
        inventory[i] = inventory[i + 1];
    }

    product_count--;
    printf("Product deleted successfully!\n");
}

// Main function
int main() {
    int choice;

    while (1) {
        printf("\n--- Inventory Management ---\n");
        printf("1. Create Product\n");
        printf("2. View Products\n");
        printf("3. Edit Product\n");
        printf("4. Delete Product\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_product();
                break;
            case 2:
                view_products();
                break;
            case 3:
                edit_product();
                break;
            case 4:
                delete_product();
                break;
            case 5:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
