#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search(char *path, char *data_name, char *data_type, int *data_number, float *data_price) {
    
    //  -- input and check if it has or not -- 

    // input string 
    char string[10];
    printf("\nSearch : ");
    scanf("%s", string);

    // check file 
    FILE *data = fopen(path, "r");

    int number;
    float price;
    char name[10];
    char type[10];

    if (data == NULL) {
        printf("file not found");
    }

    else {
    
        while (!feof(data) ) {
            fscanf(data, "%10s%10s%d%f", name, type, &number, &price);
            if (strcmp(string, name) == 0) {
                printf("Found name\n");

                strcmp(data_name, name);
                strcmp(data_type, type);

                *data_number = number;
                *data_price = price;
                
                fclose(data);
                return 1;
            }

            else if (strcmp(string, "x") == 0) {
                return 0;
            }
            
        }

        printf("Name is not found\n");
        
    }

    return 0;
}

int show_list_product(char *path) {
    
    char *filter_type;
    char *string;
    float min_price;
    float max_price;
    int min_amount;
    int max_amount;

    printf("Filter type : ");
    scanf("%s", filter_type);

    int filter_choice = 0;

    if (strcmp(filter_type, "type") == 0) {
        filter_choice = 1;
        printf("Enter your type : ");
        scanf("%s", string);
    }

    else if (strcmp(filter_type, "price") == 0) {

        filter_choice = 2;
        
        printf("Minimum price : ");
        scanf("%d", &min_price);

        printf("Maximum price : ");
        scanf("%d", &max_price);
    }

    else if (strcmp(filter_type, "amount") == 0) {
        filter_choice = 3;

        printf("Minimum amount : ");
        scanf("%d", &min_amount);

        printf("Maximum amount : ");
        scanf("%d", &max_amount);
    }   

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

            switch (filter_choice)
            {
            case 1:
                if (strcmp(string, type) == 0) {
                    fprintf(file, "%9s %9s %d %f", name, type, quantity, price);
                }
                break;
            
            case 2:
                if (price >= min_price && price <= max_price) {
                    fprintf(file, "%9s %9s %d %f", name, type, quantity, price);
                }
                break;

            case 3:
            if (quantity >= min_amount && quantity <= max_amount) {
                    fprintf(file, "%9s %9s %d %f", name, type, quantity, price);
                }
                break;

            default:
                fprintf(file, "%9s %9s %d %f", name, type, quantity, price);
                break;
            }
        }

        fclose(file);
        return 0;
    }
}
