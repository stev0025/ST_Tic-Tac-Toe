#include <stdio.h>
#include <stdarg.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include "logs.h"

static FILE *log_file;
static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

void log_init() {
    char filename[40];
    char filepath[256];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    /* Generate the logs file name: log_yyyymmdd_hhmmss.txt */
    strftime(filename, sizeof(filename), "log_%Y%m%d_%H%M%S.txt", t);

    strcpy(filepath, "../logs/");
    strcat(filepath, filename);

    /* create the logs file */
    log_file = fopen(filepath, "w");
    if (!log_file) {
        perror("Error opening log file");
    }
}

void log_message(int log_level, const char *format, ...) {
    pthread_mutex_lock(&log_mutex);

    /* Get current time */
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%H:%M:%S", t);

    /* write to log file: add time */
    fprintf(log_file, "%s ", time_str);

    /* write to log file: add level */
    switch (log_level) {
        case LOG_INFO:
            fprintf(log_file, "[INFO]: ");
            break;
        case LOG_WARN:
            fprintf(log_file, "[WARN]: ");
            break;
        case LOG_ERROR:
            fprintf(log_file, "[ERROR]: ");
            break;
        default:
            fprintf(log_file, "[UNKNOWN]: ");
            break;
    }

    /* write to log file: add message */
    va_list args;
    va_start(args, format);
    vfprintf(log_file, format, args);
    fprintf(log_file, "\n");

    /* write to log file: flush immediately */
    fflush(log_file);

    va_end(args);

    pthread_mutex_unlock(&log_mutex);
}

void log_cleanup() {
    if (fclose(log_file) != 0) {
        perror("Error closing log file");
        // handle error appropriately
    }
}
