#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int show_list_product();
int search();
int login_system();
int customer_system();
int basket_system(char *basket_path, char *name, char *type, int number, float price);
int basket_data_system();
int check_basket();

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
        }

        while (found == 0);

        // check amount of product in the basket

        int amount = check_basket(data_name);
        int number;
        do {

            if (number > amount) {
                printf("We don't have enough storage for your order\n");
            }

            printf("Enter the number of purchase : ");
            scanf("%d", &number);
        }

        while(number > amount);
        

        basket_system(basket_path, data_name, data_type, data_number, data_price);
        
        printf("Do you want to purchase : ");
        
        char purchase[5];
        scanf("%s", purchase);
        
        if (strcmp(purchase, "yes")) {
            break;
        }

    }

    while(strcmp(data_name, "x") != 0);
    return 0;       
}

// < save data to basket file here! -- >
int basket_system(char *basket_path, char *name, char *type, int number, float price) {
    
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
    
    for (int i = 0; i < strlen(name_to_find); i++) {
        printf("%c", name_to_find[i]);
    }

    while ( !feof(file) ) {
        fscanf(file, "%10s %10s %d %f", name, type, &quantity, &price);
        if (strcmp(name_to_find, name) == 0) {
            printf("%d", quantity);
            return quantity;
        }
    }

    return 0;

}
