// log_reader.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ฟังก์ชันสำหรับอ่านและแสดงข้อมูลจาก sold.csv
void view_log() {
    FILE *file = fopen("data/sold.csv", "r");
    if (file == NULL) {
        printf("Error: Unable to open data/sold.csv\n");
        return;
    }

    char line[256];
    printf("==================================================================================================================\n");
    printf("Sold Products Log:\n");
    printf("==================================================================================================================\n");

    // อ่านและแสดงหัวข้อคอลัมน์ (สมมติว่าไฟล์มีหัวข้อ)
    if (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    // อ่านและแสดงข้อมูลแต่ละแถว
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    printf("==================================================================================================================\n");

    fclose(file);
}
