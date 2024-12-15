#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"

float min_price;
float max_price;
int min_amount;
int max_amount;
char string[10];

int search(char *string, char *path, char *data_name, char *data_type, int *data_number, float *data_price) {
    
    // check file 
    FILE *data = fopen(path, "r");

    int number;
    float price;
    char name[10];
    char type[10];

    if (data == NULL) {
        printf("file not found");
    }

    else {
        while (!feof(data) ) {
            fscanf(data, "%10s %10s %d %f", name, type, &number, &price);
            if (strcmp(string, name) == 0) {

                strcpy(data_name, name);
                strcpy(data_type, type);

                *data_number = number;
                *data_price = price;
                
                fclose(data);
                return 1;
            }

            else if (strcmp(string, "x") == 0) {
                return 0;
            }
            
        }

        printf("Name is not found\n");
        
    }

    return 0;
}


int filter_product() {

    printf("Please insert filter\n");
    printf("Insert \'type\' for type of the product\n");
    printf("Inset \'price\' for filter minimum and maximum price of the product\n");
    printf("Inset \'quantity\' for filter minimum and maximum quantity of the stock\n");
    printf("None for no filter\n");
    
    char filter_type[10];

    printf("Enter product type you want to filter : ");
    scanf("%s", filter_type);

    int filter_choice = 0;

    if (strcmp(filter_type, "type") == 0) {
        filter_choice = 1;
        printf("Enter your product type: ");
        scanf("%s", string);
    }

    else if (strcmp(filter_type, "price") == 0) {

        filter_choice = 2;
        
        printf("Enter minimum price : ");
        scanf("%f", &min_price);

        printf("Enter maximum price : ");
        scanf("%f", &max_price);
    }

    else if (strcmp(filter_type, "amount") == 0) {
        filter_choice = 3;

        printf("Enter minimum amount in the stocks : ");
        scanf("%d", &min_amount);

        printf("Enter maximum amount in the stocks : ");
        scanf("%d", &max_amount);
    }   

    return filter_choice;
}

int show_list_product(char *path) {

    int filter_choice = filter_product(); 

    FILE *file = fopen(path, "r");
    
    if ( (file == NULL) ) {
        printf("File not found");
    }

    else {

        char name[10];
        char type[10];
        int quantity;
        float price;

        while (!feof(file)) {
            
            fscanf(file, "%10s %10s %d %f\n", name, type, &quantity, &price);
            switch (filter_choice)
            {
            case 1:
                if (strcmp(string, type) == 0) {
                    printf("%9s %9s %d %f\n", name, type, quantity, price);
                }
                break;
            
            case 2:
                
                if (price >= min_price && price <= max_price) {
                    printf("%9s %9s %d %f\n", name, type, quantity, price);
                }
                break;

            case 3:
            if (quantity >= min_amount && quantity <= max_amount) {
                    printf("%9s %9s %d %f\n", name, type, quantity, price);
                }
                break;

            default:
                printf("%9s %9s %d %f\n", name, type, quantity, price);
                break;
            }
        }

        fclose(file);
        return 0;
    }
}


int show_list_product_struct(struct file_data *data, int length_struct) {
    
    if ( (data == NULL) ) {
        printf("Struct is not found");
    }

    else {

        int filter_choice = filter_product();

        for (int i = 0; i < length_struct; i++) {
            
            switch (filter_choice)

            {
            case 1:
                if (strcmp(string, data[i].type) == 0) {
                    printf("%9s %9s %d %f\n", data[i].name, data[i].type, data[i].quantity, data[i].price);
                }
                break;
            
            case 2:
                
                if (data[i].price >= min_price && data[i].price <= max_price) {
                    printf("%9s %9s %d %f\n", data[i].name, data[i].type, data[i].quantity, data[i].price);
                }
                break;

            case 3:
            if (data[i].quantity >= min_amount && data[i].quantity <= max_amount) {
                    printf("%9s %9s %d %f\n", data[i].name, data[i].type, data[i].quantity, data[i].price);
                }
                break;

            default:
                printf("%9s %9s %d %f\n", data[i].name, data[i].type, data[i].quantity, data[i].price);
                break;
            }
        }

        return 0;
    }
}