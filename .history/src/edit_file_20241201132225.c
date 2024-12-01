#include <stdio.h>
#include <string.h>

int editFile(char *fileName, char *string_compare) {

    char tempPath[20];
    strcpy(tempPath, "data/temp.csv");

    FILE *temp = fopen(tempPath, "w");

    FILE *data = fopen(fileName, "r");

    int index = 0;

    char name[20];
    char type[20];
    int quantity;
    float price;

    while (fscanf(data, "%10s %10s %d %f", name, type, &quantity, &price) != EOF) {
        
        printf("current index : %d\n", index);

        if (strcmp(name, string_compare) == 0) {

            char input[20];

            printf("Value you want to change : ");
            scanf("%s", input);

            // input quantity or delete
            while (1) {

                if (strcmp(input, "quantity") == 0) {

                    int new_quan;
                    printf("Insert your new quantity : ");
                    scanf("%d", &new_quan);

                    fprintf(temp, "%10s %d %f\n", name , new_quan, price);
                    break;
                }

                else if (strcmp(input, "delete") == 0) {
                    break;
                }
            }
            
        }

        else {
            fprintf(temp, "%10s %d %f\n", name, quantity, price);
        }

        index++;
    }

    fclose(data);
    fclose(temp);
    
    if (rename(tempPath, fileName) == 0)
    {
        printf("File renamed successfully.\n");
    }

    else {
        printf("Can't rename the file\n");
    }

    if (remove(fileName) == 0) {
        printf("Remove succesfully\n");
    }

    else {
        printf("Cant remove a file\n");
    }

    return 0;
}