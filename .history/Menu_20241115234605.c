#include <stdio.h>

int showListProduct();

int main() {

    char *dataPath = "test.csv";
    FILE *data = fopen(dataPath, "r"); // this is an example

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

    // -- For show list of data --
    showListProduct(dataPath);
    return 0;
}

int showListProduct(char *path) {
    
    FILE *file = fopen(path, "r");
    char *name;
    int quantity;
    float price;

    if ( (file != NULL) ) {

        while ( !feof(file) ) {
            fscanf(file, "%10s%d%d", quantity, price);
            printf("%d%d\n", quantity, price);
        }

    }
}