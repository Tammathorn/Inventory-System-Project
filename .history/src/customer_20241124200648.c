#include <stdio.h>
#include <string.h>
#include "inventory.h"

int customer_system();
int basket_system(char *name, char *type, int number, float price);
int basket_data_system();
int check_basket();
int check_warehouse();

// function from other script
int search();
int show_list_product();

int customer_system(char *data_path) {

    char data_name[10];
    char data_type[10];
    float data_price;
    int data_number;

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

        // check amount of product in the basket
        int amount_basket = check_basket(string);
        int amount_warehouse = check_warehouse(string);
        int number;
        do {

            printf("Enter the number of purchase : ");
            scanf("%d", &number);

        }

        while(number + amount_basket >  amount_warehouse);
        

        basket_system(data_name, data_type, data_number, data_price);
        
        printf("Show your current basket : ");
        show_list_product(basket_path); 

        printf("Do you want to purchase : ");
        char purchase[5];
        scanf("%s", purchase);
        
        if (strcmp(purchase, "Yes")) {
            show_list_product(basket_path);

            //  -- edit the basket here! -- 
            break;
        }

    }

    while(1);
    return 0;       
}

// < save data to basket file here! -- >
int basket_system(char *name, char *type, int number, float price) {
    
    FILE *basket = fopen(basket_path, "a");
    
    fprintf(basket, "%s %s %d %f\n", name, type, number, price);

    printf("Add to the basket\n");

    fclose(basket);

    return 0;
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

int check_basket(char *name_to_find) {

    FILE *file = fopen(basket_path, "r");
    char name[10], type[10];
    int quantity;
    float price;
    int found = 0;
    

    while ( !feof(file) ) {
        fscanf(file, "%s %10s %d %f", name, type, &quantity, &price);
        
        if (strcmp(name_to_find, name) == 0) {
            found = 1;
            return quantity;
        }
    }

    if (found == 0) {
        return 0;
    } 
    

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
}