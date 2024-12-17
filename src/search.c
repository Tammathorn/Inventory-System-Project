#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"

float min_price;
float max_price;
int min_amount;
int max_amount;

int input_min_max();

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
            
        }

        printf("Name is not found\n");
        
    }

    return 2;
}


int filter_product(float *min, float *max, char *string) {

    printf("Please insert filter\n");
    printf("Insert 0 for category of the product\n");
    printf("Insert 1 for filter minimum and maximum price of the product\n");
    printf("Insert 2 for filter minimum and maximum quantity of the stock\n");
    
    int filter_type;
    do {
        printf("Enter product type you want to filter : ");
        scanf("%d", &filter_type);
    }
    
    while (filter_type != 0 && filter_type != 1 && filter_type != 2);

    if (filter_type == 0) {
        printf("Enter your category: ");
        scanf("%s", string);
    }

    else if (filter_type == 1) {
        
        input_min_max(min, max);
    }

    else if (filter_type == 2) {

        input_min_max(min, max);
    }   

    return filter_type;
}

int show_list_product(char *path, int filter_choice, float *min, float *max, char *string) {

    int show = 0;
    FILE *inventory = fopen(path, "r");
    

    if ( (inventory == NULL) ) {
        printf("File not found");
    }

    else {

        char name[MAX_CHAR];
        char type[MAX_CHAR];
        int quantity;
        float price;

        while (fscanf(inventory, "%s %s %d %f", name, type, &quantity, &price) != EOF) {
            
            switch (filter_choice)
            {
            case 0:
                if (strcmp(string, type) == 0) {
                    printf("%9s %9s %d %.2f\n", name, type, quantity, price);
                    show++;
                }

                break;
            
            case 1:
                
                if (price >= *min && price <= *max) {
                    printf("%9s %9s %d %.2f\n", name, type, quantity, price);
                    show++;
                }

                break;

            case 2:
            if (quantity >= *min && quantity <= *max) {
                    printf("%9s %9s %d %.2f\n", name, type, quantity, price);
                    show++;
                }
                
                break;

            default:
                printf("%9s %9s %d %f\n", name, type, quantity, price);
                show++;
                break;
            }
        }

        if (show == 0) {
            printf("No data is found\n");
        }

        fclose(inventory);
        return 0;
    }
}


int show_list_product_struct(struct file_data *data, int length_struct, int filter_choice, char *string) {
    
    int show = 0;

    if ( (data == NULL) ) {
        printf("Struct is not found");
    }

    else {

        for (int i = 0; i < length_struct; i++) {
            
            switch (filter_choice)

            {
            case 1:
                if (strcmp(string, data[i].type) == 0) {
                    printf("%9s %9s %d %f\n", data[i].name, data[i].type, data[i].quantity, data[i].price);
                    show++;
                }
                break;
            
            case 2:
                
                if (data[i].price >= min_price && data[i].price <= max_price) {
                    printf("%9s %9s %d %f\n", data[i].name, data[i].type, data[i].quantity, data[i].price);
                    show++;
                }
                break;

            case 3:
            if (data[i].quantity >= min_amount && data[i].quantity <= max_amount) {
                    printf("%9s %9s %d %f\n", data[i].name, data[i].type, data[i].quantity, data[i].price);
                    show++;
                }
                break;

            default:
                printf("%9s %9s %d %f\n", data[i].name, data[i].type, data[i].quantity, data[i].price);
                show++;
                break;
            }
        }

        if (show == 0) {
            printf("No data is found\n");
        }

        return 0;
    }
}

int input_min_max(float *min, float *max) {

    do {
        printf("Enter minimum : ");
        scanf("%f", min);
    }

    while(*min < 0);

    do {
        printf("Enter maximum : ");
        scanf("%f", max);
    }

    while(*max < 0 || *max <= *min);
    
    return 0;
}