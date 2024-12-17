#include <stdio.h>
#include <string.h>
#include "inventory.h"

int editFile(char *fileName, char *string_compare) {

    struct file_data Cart[MAX_PRODUCT];

    FILE *data = fopen(fileName, "r");

    int index = 0;

    char name[20];
    char type[20];
    int quantity;
    float price;

    while (fscanf(data, "%s %s %d %f", name, type, &quantity, &price) != EOF) {
        
        strcpy(Cart[index].name, name);
        strcpy(Cart[index].type, type);
        Cart[index].price = price;

        if (strcmp(name, string_compare) == 0) {

            int new_quan = 0;
            
            do {
                printf("Change the quantity from %d :  to be ", quantity);
                scanf("%d", &new_quan);

                Cart[index].quantity = new_quan;
            }
            
            while (new_quan < 0);
            
        }

        else {
            Cart[index].quantity = quantity;
        }

        index++;
    }

    fclose(data);

    // write the data again
    data = fopen(fileName, "w");

    for (int i = 0; i < index; i++) {
    
        fprintf(data, "%10s %10s %d %f\n", Cart[i].name, Cart[i].type, Cart[i].quantity, Cart[i].price);
    }
    
    return 0;
}