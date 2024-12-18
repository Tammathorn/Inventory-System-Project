#include <stdio.h>
#include <time.h>
#include "logging.h"

FILE *logFile = NULL;

void init_Log(const char *filename) {
    logFile = fopen(filename, "a");
    if (!logFile) {
        printf("Error: Could not open log file.\n");
    }
}

void log_Action(const char *action) {
    if (!logFile) return;

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    fprintf(logFile, "[%04d-%02d-%02d %02d:%02d:%02d] %s\n",
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec,
            action);
    fflush(logFile);
}

void close_Log() {
    if (logFile) {
        fclose(logFile);
        logFile = NULL;
    }
}