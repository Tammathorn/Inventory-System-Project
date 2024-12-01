#include <stdio.h>
#include <string.h>

int editFile(char *fileName, int line) {

    char tempPath[20];
    strcpy(tempPath, "data/temp.csv");

    FILE *temp = fopen(tempPath, "w");
    FILE *data = fopen(fileName, "r+");

    int index = 0;
    while (!feof(data)) {
        
        printf("Time to edit the basket\n");
        char name[20];
        int quantity;
        float price;

        fscanf(data, "%10s %d %.2f", name, &quantity, &price);

        if (index == line) {

            char input[20];

            printf("Value you want to change : ");
            scanf("%s", input);


            // input quantity or delete
            while (1) {

                if (strcmp(input, "quantity") == 0) {

                    int new_quan;
                    printf("Insert your new quantity :");
                    scanf("%d", &new_quan);

                    fprintf(temp, "%s %d %f\n", name, price, new_quan);
                    break;
                }

                else if (strcmp(input, "delete") == 0) {
                    break;
                }
            }
            
        }

        else {
            fprintf(temp, "%s %d %f", name, price, quantity);
        }

        index++;
    }

    
    rename(tempPath, "data/test.csv");
    remove(fileName);
    fclose(data);
    fclose(temp);
    
    return 0;
}