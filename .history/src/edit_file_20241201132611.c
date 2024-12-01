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
            int new_quan;
            

            do {
                printf("Change the quantity from %d :  to be ", quantity);
                scanf("%d", &new_quan);
            }
            
            while (new_quan < 0);

            fprintf(temp, "%10s %d %f\n", name, new_quan, price);
            
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