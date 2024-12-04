#include <stdio.h>
#include <string.h>
#include "inventory.h"

int customer_system();
int basket_system(char *name, char *type, int number, float price, int *index);
int basket_data_system();
int check_warehouse();
void read_older_file();

struct file_data {
    char name[max_char];
    char type[max_char];
    int quantity;
    float price;
}; 

int basket_length = 0;
struct file_data basket[max_product];


int customer_system() {

    char data_name[10];
    char data_type[10];
    float data_price;
    int data_number;

    printf("pass");
    read_older_file();

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
        int current_number_order;
        int current_index;
        do {

            if (current_number_order >  amount_warehouse) {
                basket[current_index].quantity -= number; 
            }

            do {
                printf("Enter the number of purchase : ");
                scanf("%d", &number);
            } 
            while (number < 0);

            // for insert data to basket
            printf("%c %c %d %f\n", data_name[0], data_type[0], number, data_price);

            current_number_order = basket_system(data_name, data_type, number, data_price, &current_index);            
            
        }

        while(current_number_order >  amount_warehouse);
        
        // show current status of basket
        printf("Show your current basket ");
        show_list_product(basket_path); 

        // purchase or not
        printf("Do you want to purchase : ");
        char purchase[5];
        scanf("%s", purchase);
        
        // if purchase
        if (strcmp(purchase, "Yes") == 0) {

            show_list_product(basket_path);

            char confirm[7];
            char search_name[max_char];
            
            printf("Press confirm to confirm : ");
            scanf("%s", confirm);
            
            do {
                printf("Which product do you want to change : ");
                scanf("%s", search_name);

                editFile(basket_path, search_name);
                
                printf("Press confirm to confirm : ");
                scanf("%s", confirm);
                
            }

            while (strcmp(confirm, "confirm") != 0);

            printf("Purchase succesfully");
            break;

            //  -- edit the basket here! -- 
        }

    }

    while(1);
    return 0;       
}


void read_older_file() {
    
    FILE *data = fopen(basket_path, "r+");

    char name_check[max_char], type_check[max_char];
    float price;
    int quantity;
    int index = 0;

    while ( fscanf(data, "%s %s %d %f", name_check, type_check, quantity, price) != EOF) {
        strcpy(basket[index].name, name_check);
        strcpy(basket[index].type, type_check);
        basket[index].quantity = quantity;
        basket[index].price = price;

        basket_length++;
        index++;
    }
}
// < save data to basket file here! -- >
int basket_system(char *name, char *type, int number, float price, int *index) {
    
    FILE *data = fopen(basket_path, "r+");
    
    // check in the structure
    int i = 0;
    for (i; i <= basket_length; i++) {
        if (strcmp(name, basket[i].name) == 0) {
            basket[i].quantity = number;
            *index = i;
        }
    }

    // if it is not found, add a new element
    if (i == basket_length) {

        strcpy(basket[i].name, name);
        strcpy(basket[i].type, type);
        basket[i].quantity = number;
        basket[i].price = price;

        basket_length++; 
        *index = basket_length;
    }

    printf("Add to the basket\n");

    return basket[i].quantity;
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

int check_warehouse(char *name_to_find) {

    FILE *file = fopen(data_path, "r");
    char name[10], type[10];
    int quantity;
    float price;
    int found = 0;
    

    while ( !feof(file) ) {
        fscanf(file, "%10s %10s %d %f", name, type, &quantity, &price);
        
        if (strcmp(name_to_find, name) == 0) {
            found = 1;
            return quantity;
        }
    }

    fclose(file);
}
