#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "coupons.h"

extern char *coupon_path;
 //Compare expired date with todays
int is_expired(const char *expiry_date) {
    struct tm expiry = {0};
    time_t now = time(NULL);

    if (sscanf(expiry_date, "%4d-%2d-%2d", &expiry.tm_year, &expiry.tm_mon, &expiry.tm_mday) != 3) {
        return 0;
    }

    expiry.tm_year -= 1900;
    expiry.tm_mon -= 1;

    time_t expiry_time = mktime(&expiry);
    return difftime(expiry_time, now) < 0; //Compare expired date with todays
}

//Clean up expired coupons
int clean_expired_coupons() {
    FILE *file = fopen(coupon_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    FILE *temp_file = fopen("temp.csv", "w");
    if (temp_file == NULL) {
        perror("Error opening temporary file");
        fclose(file);
        return -1;
    }

    char line[256];
    int expired_count = 0;

    while (fgets(line, sizeof(line), file)) {
        char expiry_date[11];
        sscanf(line, "%*[^,],%*[^,],%*[^,],%*f,%*d,%10s", expiry_date);

        if (is_expired(expiry_date)) {
            expired_count++;
            continue;
        }

        fputs(line, temp_file);
    }

    fclose(file);
    fclose(temp_file);

    remove(coupon_path);
    rename("temp.csv", coupon_path);

    return expired_count;
}
