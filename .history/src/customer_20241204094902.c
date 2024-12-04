#include <stdio.h>
#include <string.h>
#include "inventory.h"

int length_list = 0;

int customer_system();
int basket_system(char *name, char *type, int number, float price, int *index);
int basket_data_system();
int check_warehouse();
int read_file();
void basket_save_system();

struct file_data basket[max_product];
struct file_data data[max_product];


int customer_system() {

    char data_name[10];
    char data_type[10];
    float data_price;
    int data_number;

    length_list = read_file(basket_path, basket);
    read_file(data_path, data);

    // loop of select multiple object --
    do {
        
        int found = 0;
        char string[10];

        // loop of search --
        do {
            // input string 
            printf("Search : ");
            scanf("%s", string);
            found = search(string, data_path, data_name, data_type, &data_number, &data_price);
        }

        while (found == 0);

        int amount_warehouse = check_warehouse(string);
        int number;
        int current_number_order = -2;
        int current_index;
        do {

            if (current_number_order >  amount_warehouse) {
                basket[current_index].quantity -= number; 
                length_list--;
            }

            
            do {
                printf("Enter the number of purchase : ");
                scanf("%d", &number);
            } 

            while (number < 0);

            // for the data that selected
            printf("%c %c %d %f\n", data_name[0], data_type[0], number, data_price);
            current_number_order = basket_system(data_name, data_type, number, data_price, &current_index);  
            printf("Name : %s Quantity : %d", data_name, number);
            printf(" Add to the basket\n");
          
            
            if (amount_warehouse == -1) {
                break;
            } 
        }

        while(current_number_order >  amount_warehouse);
        
        // show current status of basket
        printf("Show your current basket ");
        show_list_product_struct(basket, length_list);

        // purchase or not
        printf("Do you want to purchase : ");
        char purchase[5];
        scanf("%s", purchase);
        
        // if purchase
        if (strcmp(purchase, "Yes") == 0) {

            show_list_product_struct(basket, length_list);

            char confirm[7];
            char search_name[max_char];

            // <---- Apply coupon here ---->

            
            printf("Press confirm to confirm : ");
            scanf("%s", confirm);

            while (strcmp(confirm, "confirm") != 0) {
                printf("Which product do you want to change : ");
                scanf("%s", search_name);

                editFile(basket_path, search_name);
                
                printf("Press confirm to confirm : ");
                scanf("%s", confirm);
            }

            basket_save_system();
            printf("Purchase succesfully");
            break;

            //  -- edit the basket here! -- 
        }

    }

    while(1);

    return 0;       
}


int read_file(char *path, struct file_data *data_struct) {
    
    FILE *data = fopen(path, "r+");

    char name_check[max_char], type_check[max_char];
    float price;
    int quantity;
    int index = 0;

    while ( fscanf(data, "%s %s %d %f", name_check, type_check, &quantity, &price) != EOF) {
        strcpy(data_struct[index].name, name_check);
        strcpy(data_struct[index].type, type_check);
        data_struct[index].quantity = quantity;
        data_struct[index].price = price;
        index++;
    }

    return index;
}
// < save data to basket structure here! -- >
int basket_system(char *name, char *type, int number, float price, int *index) {
    
    FILE *data = fopen(basket_path, "r+");
    
    // check in the structure
    int i = 0;
    for (i; i <= length_list; i++) {
        if (strcmp(name, basket[i].name) == 0) {
            basket[i].quantity = number;
            *index = i;
            break;
        }

    }

    if (length_list == 0) {
        i = 0;
    }

    // if it is not found, add a new element
    if (i == length_list) {

        strcpy(basket[i].name, name);
        strcpy(basket[i].type, type);
        basket[i].quantity = number;
        basket[i].price = price;

        *index = length_list;
        length_list++; 
    }

    return basket[i].quantity;
}

// append data from struct to csv here
void basket_save_system() {
    
    FILE *data = fopen(basket_path, "w");

    for (int i = 0; i < length_list; i++) {
        fprintf(data, "%s %s %d %.2f\n", basket[i].name, basket[i].type, basket[i].quantity, basket[i].price);
    }

}

// < change data from basket file to inventory file here! -- >
int basket_data_system() {
    FILE *basket = fopen(basket_path, "r");
    FILE *data = fopen(data_path, "r+");

    char name1[10];
    char name2[10];
    char type[10];
    float price;
    int number1;
    int number2;

    while ( !feof(basket) ) {
        fscanf(basket, "%10s %10s %d %f", name1, type, &number1, &price);
        while (!feof(data)) {
            fscanf(data, "%10s %10s %d %f", name2, type, &number2, &price);
            if (strcmp(name1, name2) == 0) {
                fprintf(data, "%10s %10s %d %f\n", name1, type, number2 - number1, price);
                break;
            }
        }
    }

    fclose(basket);
    fclose(data);

    return 0;   
}


// Also need to fix here 
int check_warehouse(char *name_to_find) {

    char name[10], type[10];
    int quantity;
    float price;
    int i = 0;
    

    for (int i = 0; i <= length_list; i++) {
        
        if (strcmp(name_to_find, data[i].name) == 0) {
            return quantity;
        }
    }

    return -1;
}
