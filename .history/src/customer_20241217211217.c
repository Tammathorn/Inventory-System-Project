#include <stdio.h>
#include <string.h>
#include "inventory.h"
#include "coupons.h"

int basket_length = 0;
int data_length = 0;

int showInstruction();
int customer_system();
int basket_system(char *name, char *type, int number, float price, int *index);
int check_warehouse();
int basket_data_system();
void save_system();
int read_file();
int filter_product();

// declare structure of basket and inventory
struct file_data basket[MAX_PRODUCT];
struct file_data data[MAX_PRODUCT];


int customer_system() {

    // Variable to input name, type, price, number 
    char data_name[10];
    char data_type[10];
    float data_price;
    int data_number;

    int current_index;

    current_index = read_file(basket_path, basket);
    data_length = read_file(data_path, data);

    int choice;

    // loop of select multiple object --
    do {
        
        showInstruction();

        printf("Enter your choice : ");
        scanf("%d", &choice);

        // check the remaining stock in the inventory
        int amount_warehouse;
        int number;
        int current_number_order = 0;

        // for finding the name in the inventory
        int found;
        char string[MAX_CHAR];
        
        // for filter part
        int filter = -1;
        int filter_number = 3;
        float min;
        float max;
        char type_input[MAX_CHAR];

        switch(choice) {
            
            case 1:

                do {
                    printf("Press 0 to not using filter, and 1 for use : ");
                    scanf("%d", &filter);
                }

                while (filter != 0 && filter != 1);

                if (filter == 1) {
                    filter_number = filter_product(&min, &max, type_input);
                }
                
                show_list_product(data_path, filter_number, &min, &max, type_input);
                break;

            // search product in the inventory
            case 2:

                // loop of search --
                do { 
                    printf("Select : ");
                    scanf("%s", string);
                    found = search(string, data_path, data_name, data_type, &data_number, &data_price);
                }
                // if it is not found loop again
                while (found == 0);

                amount_warehouse = check_warehouse(string);

                do {
                    
                    if (current_number_order >  amount_warehouse) {
                        printf("We don't have enough stock\n");
                        basket[current_index].quantity -= number; 
                        basket_length--;
                    }

                    // input the positive number
                    do {
                        printf("Enter the number of purchase : ");
                        scanf("%d", &number);

                        if (number < 0) {
                            printf("Number is not valid\n");
                        }
                    } 

                    while (number < 0);

                    // for the data that selected
                    current_number_order = basket_system(data_name, data_type, number, data_price, &current_index);  
                    printf("Name : %s Quantity : %d", data_name, number);
                    printf("Add to the basket\n");
            
                    // when it is not found in the inventory
                    if (amount_warehouse == 0) {
                        break;
                    }
                }

                while(current_number_order >  amount_warehouse);
                break;


            // show list of coupon here!
            case 3:
                break;
    

            // show current status of basket
            case 4:
                printf("Show your current basket ");
                show_list_product_struct(basket, basket_length, type_input);

                break;
            // edit basket
            case 5:
                printf("Which product do you want to change : ");
                scanf("%s", string);

                editFile(basket_path, string);

                break;

            // Purchase
            case 6:
                
                printf("Do you want to purchase (Enter \' Yes \' to confirm your order) : ");
                char purchase[5];
                scanf("%s", purchase);

                if (strcmp(purchase, "Yes") == 0) {

                    show_list_product_struct(basket, basket_length, 3);
                    basket_data_system();
                    save_system(basket, basket_length, basket_path);
                    save_system(data, data_length, data_path);
                    printf("Purchase successfully");

                }

                break;

            // Exit
            case 7:
                printf("--------Exit the program--------");
                return 0;

        }      

        while (choice < 1 || choice > 7);     
    }

    while (1);

    return 0;
}


int read_file(char *path, struct file_data *data_struct) {
    
    FILE *data = fopen(path, "r+");

    char name_check[MAX_CHAR], type_check[MAX_CHAR];
    float price = 0;
    int quantity = 0;
    int index = 0;

    while (fscanf(data, "%s %s %d %f", name_check, type_check, &quantity, &price) != EOF) {
        strcpy(data_struct[index].name, name_check);
        strcpy(data_struct[index].type, type_check);
        data_struct[index].quantity = quantity;
        data_struct[index].price = price;
        index++;
    }

    fclose(data);

    return index;
}
// save data to basket structure 
int basket_system(char *name, char *type, int number, float price, int *index) {
    
    FILE *data = fopen(basket_path, "r+");
    
    // check in the structure
    int i = 0;
    for (i; i <= basket_length; i++) {

        // if it has the same name plus and if it not remove
        if (strcmp(name, basket[i].name) == 0) {
            basket[i].quantity += number;
            *index = i;
            break;
        }

    }

    // for the first element
    if (basket_length == 0) {
        i = 0;
    }

    // if it is not found, add a new element
    if (i == basket_length) {

        strcpy(basket[i].name, name);
        strcpy(basket[i].type, type);
        basket[i].quantity += number;
        basket[i].price = price;

        *index = basket_length;
        basket_length++; 
    }

    return basket[i].quantity;
}

// append data from struct to csv here
void save_system(struct file_data *data, int length, char *path) {
    
    FILE *file = fopen(path, "w");

    for (int i = 0; i < length; i++) {
        fprintf(file, "%s %s %d %.2f\n", data[i].name, data[i].type, data[i].quantity, data[i].price);
    }

}

// change data from basket file to inventory file here
int basket_data_system() {

    for (int i = 0; i < basket_length; i++) {
        for (int j = 0; j < data_length; j++) {

            // loop if both have the same name remove the quantity of the inventory
            if (strcmp(data[i].name, basket[j].name) == 0) {

                
                data[i].quantity -= basket[j].quantity;
            }
        }
    }

    return 0;   
}


// Check number of remaining stock
int check_warehouse(char *name_to_find) {

    char name[10], type[10];
    float price;
    int i = 0;
    

    for (int i = 0; i <= data_length; i++) {
        
        // if found return number of quantity
        if (strcmp(name_to_find, data[i].name) == 0) {
            return data[i].quantity;
        }
    }

    return 0;
}
