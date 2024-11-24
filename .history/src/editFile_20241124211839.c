#include <stdio.h>
#include <string.h>

int editFile(char *fileName, int line) {

    char tempPath[20];
    strcpy(tempPath, "data/temp.csv");

    FILE *temp = fopen(tempPath, "r+");
    FILE *data = fopen(fileName, "r+");

    int index = 0;
    while (!feof(data)) {
        
        char name[20];
        int quantity;
        float price;

        fscanf(data, "%10s %d %.2f");

        if (index == line) {

            char input[maxChar];

            printf("Value you want to change");
            scanf("%s", input);


            // input quantity or delete
            while (1) {

                if (strcmp(input, "quantity")) {

                    int newQuan;
                    printf("Insert your new quantity :");
                    scanf("%d", &newQuan);

                    fprintf(temp, "%s %d %f", name, price, newQuan);
                    break;
                }

                else if (strcmp(input, "delete")) {
                    break;
                }
            }
            
        }

        else {
            fprintf(temp, "%s %d %f", name, price, quantity);
        }
    }

    rename(tempPath, fileName);
    remove(fileName);
    
    return 0;
}