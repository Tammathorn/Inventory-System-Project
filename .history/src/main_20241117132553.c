#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int show_list_product();
int search();
int login_system();
int customer_system();
int basket_system(char *basket_path, char *name, char *type, int number, float price);

// path to data
char *data_path = "data/test.csv";
char *basket_path = "data/basket.csv";

int main() {
    
    // -- For login system --
    int choice;

    login_system(data_path);
    // ---------------

    return 0;
}

int login_system(char *data_path) {
    
    int choice;
    
    do {
        printf("What is your role 1 for customer and 2 for owner : ");
        scanf("%d", &choice);
    }

    while (choice != 1 && choice != 2);
    
    switch(choice) {
        case 1:
            printf("Welcome customer!\n");
            break;

        case 2:
            printf("Welcome owner!\n");
            break;
    }

    // -- For show list of data --
    
    show_list_product(data_path);

    if (choice == 1) {
        customer_system(data_path);
    }

    return 0;
}

int show_list_product(char *path) {
    
    FILE *file = fopen(path, "r");
    

    if ( (file == NULL) ) {
        printf("File not found");
    }
    else {

        char name[10];
        char type[10];
        int quantity;
        float price;

        while ( !feof(file) ) {
            fscanf(file, "%10s%10s%d%f", name, type, &quantity, &price);
            printf("%s %s %d %f\n", name, type, quantity, price);
        }

        fclose(file);
        return 0;
    }
}

int customer_system(char *data_path) {

    char data_name[10];
    char data_type[10];
    float data_price;
    int data_number;

    // loop of select multiple object --
    do {
        
        int found = 0;

        // loop of search --
        do {
            found = search(data_path, data_name, data_type, &data_number, &data_price);

            if (found == 2) {
                login_system(data_path);
                return 0;
            }
        }

        while (found == 0);

        if (found == 2) {
            break;
        }

        int number;
        do {
            
            printf(" enter the number of purchase : ");
            scanf("%d", &number);
        }

        while(number > data_number);
        

        basket_system(basket_path, data_name, data_type, data_number, data_price);

    }

    while(1);
    return 0;       
}

int basket_system(char *basket_path, char *name, char *type, int number, float price) {
    
    FILE *basket = fopen(basket_path, "a");

    show_list_product(basket_path);
    fprintf(basket, "%s %s %d %f\n", name, type, number, price);

    printf("Save\n");
    fclose(basket);

    return 0;
}