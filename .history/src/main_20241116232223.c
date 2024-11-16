#include <stdio.h>
#include <stdlib.h>

int show_list_product();
int search();

int main() {

    char *dataPath = "data/test.csv";
    FILE *data = fopen(dataPath, "r"); // this is an example

    // -- For login system --
    
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

    // ---------------

    // -- For show list of data --
    
    show_list_product(dataPath);

    // -- test run file -- 
    int type;
    search(dataPath &type);
    
    return 0;


    
}

// function to read and print all the product ----- 
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