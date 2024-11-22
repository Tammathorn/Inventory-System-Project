\#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int show_list_product();
int search();
int login_system();
int customer_system();
int basket_system(char *basket_path, char *name, char *type, int number, float price);
int basket_data_system();
int create_coupon();
int get_discount_data(int *discount_type, float *discount_price, int *discount_percent)
int get_product_data(char *product_name, char *product_type)
int save_coupon_data(char *coupon_code, char *product_name, char *product_type, float discount_price, int discount_percent, char *expiry_date) 

// path to data
char *data_path = "data/test.csv";
char *basket_path = "data/basket.csv";
char *coupon_path = "data/coupons.csv";

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
            fscanf(file, "%9s %9s %d %f", name, type, &quantity, &price);
            printf("%9s %9s %d %f\n", name, type, quantity, price);
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
        
        printf("Do you want to purchase : ");
        
        int purchase;
        scanf("%d", &purchase);
        switch (purchase)
        {
        case 1:
            // change data here!
            basket_data_system();
            FILE *file = fopen("basket_path", "w");

            return 0;

        case 0:
            break;
        }

    }

    while(strcmp(data_name, "x") != 0);
    return 0;       
}

int basket_system(char *basket_path, char *name, char *type, int number, float price) {
    
    FILE *basket = fopen(basket_path, "a");

    fprintf(basket, "%s %s %d %f\n", name, type, number, price);

    printf("Save\n");

    fclose(basket);

    return 0;
}

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

int get_discount_data(int *discount_type, float *discount_price, int *discount_percent) {
    printf("Select discount type (1 for Price, 2 for Percentage): ");
    scanf("%d", discount_type);

    if (*discount_type == 1) {
        printf("Enter discount price (e.g., 10.50): ");
        scanf("%f", discount_price);
        *discount_percent = 0;  // Set percent to 0 for price discount
    } else if (*discount_type == 2) {
        printf("Enter discount percentage (0-100): ");
        scanf("%d", discount_percent);
        *discount_price = 0.0;  // Set price to 0 for percentage discount
    } else {
        printf("Invalid discount type.\n");
        return -1;
    }

    return 0;
}

// Function to handle product or type choice
int get_product_data(char *product_name, char *product_type) {
    int choice;
    printf("Apply to 1. Product Name\n2. Product Type\n");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter product name coupon: ");
        scanf("%19s", product_name);
        strcpy(product_type, "");  
    } else if (choice == 2) {
        printf("Enter product type for coupon: ");
        scanf("%19s", product_type);
        strcpy(product_name, "");  
    } else {
        printf("Invalid choice.\n");
        return -1;
    }

    return 0;
}

int create_coupon() {
    char coupon_code[20], product_name[20] = "", product_type[20] = "", expiry_date[11];
    float discount_price = 0.0;
    int discount_percent = 0;
    int discount_type;

    // Get discount data (type, price, percentage)
    if (get_discount_data(&discount_type, &discount_price, &discount_percent) == -1) {
        return -1;
    }

    // Get product name or type
    if (get_product_data(product_name, product_type) == -1) {
        return -1;
    }

    //Expiry date
    printf("Enter coupon code: ");
    scanf("%19s", coupon_code);
    printf("Enter expiry date (YYYY-MM-DD): ");
    scanf("%10s", expiry_date);

    // Save coupon data to file
    if (save_coupon_data(coupon_code, product_name, product_type, discount_price, discount_percent, expiry_date) == 0) {
        printf("Successfully created coupon.\n");
    } else {
        printf("Failed to create coupon.\n");
    }

    return 0;
}

// Save coupon to data
int save_coupon_data(char *coupon_code, char *product_name, char *product_type, float discount_price, int discount_percent, char *expiry_date) {
    FILE *file = fopen(coupon_path, "a");

    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    // Write coupon data to file
    if (strlen(product_name) > 0) {
        fprintf(file, "%s,%s,%.2f,%d,%s,%s\n", coupon_code, product_name, discount_price, discount_percent, expiry_date, ""); 
    } else {
        fprintf(file, "%s,%s,%.2f,%d,%s,%s\n", coupon_code, "", discount_price, discount_percent, expiry_date, product_type); 
    }

    fclose(file);
    return 0;
}
