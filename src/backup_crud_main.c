#include <stdio.h>
#include "inventory.h"

// ฟังก์ชันโปรโตไทป์
void create_product();
void view_products();
void edit_product();
void delete_product();
void save_to_file(const char *file_path);
void load_data_from_file(const char *file_path);

int main() {
    const char *file_path = "inventory.csv";  // ชื่อไฟล์ CSV
    int choice;

    load_data_from_file(file_path);  // โหลดข้อมูลจากไฟล์

    while (1) {
        printf("\nInventory Management System\n");
        printf("1. Add Product\n");
        printf("2. View Products\n");
        printf("3. Edit Product\n");
        printf("4. Delete Product\n");
        printf("5. Save to File\n");
        printf("6. Exit\n");
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
                save_to_file(file_path);
                break;
            case 6:
                printf("Exiting program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
