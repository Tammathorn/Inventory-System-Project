#include <stdio.h>
#include <string.h>
#include "inventory.h"

struct file_data {
    char name[max_char];
    char type[max_char];
    int quantity;
    float price;
};

int editFile(char *fileName, char *string_compare) {

    struct file_data basket[max_product];

    FILE *data = fopen(fileName, "r");

    int index = 0;

    char name[20];
    char type[20];
    int quantity;
    float price;

    while (fscanf(data, "%s %s %d %f", name, type, &quantity, &price) != EOF) {
        
        strcpy(basket[index].name, name);
        strcpy(basket[index].type, type);
        basket[index].price = price;

        printf("current index : %d\n", index);

        if (strcmp(name, string_compare) == 0) {

            int new_quan = 0;
            
            do {
                printf("Change the quantity from %d :  to be ", quantity);
                scanf("%d", &new_quan);

                basket[index].quantity = new_quan;
            }
            
            while (new_quan < 0);
            
        }

        else {
            basket[index].quantity = quantity;
        }

        index++;
    }

    fclose(data);

    // write the data again
    data = fopen(fileName, "w");

    for (int i = 0; i < index; i++) {
    
        fprintf(data, "%10s %10s %d %f\n", basket[i].name, basket[i].type, basket[i].quantity, basket[i].price);
    }
    
    return 0;
}