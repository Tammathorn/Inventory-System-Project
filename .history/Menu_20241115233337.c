#include <stdio.h>
int showListProduct;

int main() {

    FILE *data = fopen('test.csv', "r"); // this is an example

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

char showListProduct(path) {
    char *name;
    int quantity;
    float price;

    while ( !feof(path)) {
        fscanf(path, "%10s%d%d", quantity, price);

    }
}