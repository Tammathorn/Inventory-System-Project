#include <stdio.h>
#include <string.h>

int editFile(char *fileName, int line) {

    char tempPath[20];
    strcpy(tempPath, "data/temp.csv");

    FILE *temp = fopen(tempPath, "w");
    fclose(temp);

    temp = fopen(tempPath, "a");

    FILE *data = fopen(fileName, "r");

    int index = 0;

    char name[20];
    char type[20];
    int quantity;
    float price;

    while (!feof(data)) {
        
        fscanf(data, "%10s %10s %d %f", name, type, &quantity, &price);
        printf("current index : %d\n", index);

        if (index == line) {

            char input[20];

            printf("Value you want to change : ");
            scanf("%s", input);

            // input quantity or delete
            while (1) {

                if (strcmp(input, "quantity") == 0) {

                    int new_quan;
                    printf("Insert your new quantity : ");
                    scanf("%d", &new_quan);

                    printf("Found desired line\n");
                    printf("%c %d %f\n", name[0], new_quan, price);
                    fprintf(temp, "%10s %d %f\n", name , new_quan, price);
                    break;
                }

                else if (strcmp(input, "delete") == 0) {
                    break;
                }
            }
            
        }

        else {
            printf("Not the desired line\n");
            printf("%c %d %f\n", name[0], quantity, price);
            fprintf(temp, "%10s %d %f\n", name, quantity, price);
        }

        index++;
    }


    
    rename(tempPath, "data/test.csv");
    remove(fileName);
    fclose(data);
    fclose(temp);
    
    return 0;
}