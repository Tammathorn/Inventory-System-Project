#ifndef INVENTORY_H
#define INVENTORY_H

// Constants
#define MAX_PRODUCTS 100
#define MAX_CHAR 10
#define MAX_PRODUCT 100

// Product Structure (from inventory1.h)
typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
} product_t;

// File Data Structure (from inventory2.h)
struct file_data {
    char name[MAX_CHAR];
    char type[MAX_CHAR];
    int quantity;
    float price;
};

// External variables (from inventory2.h)
extern char *data_path;
extern char *basket_path;
extern char *coupon_path; 

// Function Prototypes (combined from both headers)
void create_product();
void view_products();
void edit_product();
void delete_product();
void save_to_file(const char *file_path);
void load_data_from_file(const char *file_path);
void show_list_product(const char *file_path);

// Function prototypes from inventory2.h
int customer_system();
int editFile();
int search();
void show_list_product_struct();

#endif // INVENTORY_H
