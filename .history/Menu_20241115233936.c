#include <stdio.h>

int showListProduct();

int main() {

    char *path = "test.csv";
    FILE *data = fopen(path, "r"); // this is an example

    // -- For login system --
    
    int choice;
    printf("What is your role : ");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            printf("Welcome customer!");
            break;

        case 2:
            printf("Welcome owner!");
            break;
    }

    // ---------------

    return 0;
}

int showListProduct(path) {
    
    FILE *file = fopen(path, "r");
    char *name;
    int quantity;
    float price;

    while ( !feof(file)) {
        fscanf(file, "%10s%d%d", quantity, price);
    }
}