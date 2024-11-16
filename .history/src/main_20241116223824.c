#include <stdio.h>
#include <stdlib.h>

int show_list_product();

int main() {

    char *dataPath = "data/test.csv";
    FILE *data = fopen(dataPath, "r"); // this is an example

    // -- For login system --
    
    int choice;
    printf("What is your role : ");
    scanf("%d", &choice);
    
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
    system("./search.c");
    
    return 0;


    
}

// function to read and print all the product ----- 
int show_list_product(char *path) {
    
    FILE *file = fopen(path, "r");
    

    if ( (file == NULL) ) {
        printf("File not found");
    }
    else {

        char *name;
        int quantity;
        float price;

        while ( !feof(file) ) {
            fscanf(file, "%s%d%f", name, &quantity, &price);
            printf("%s %d %f\n", name, quantity, price);
        }

        fclose(file);
        
    }
}