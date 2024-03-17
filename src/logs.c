#include <stdio.h>
#include <stdarg.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "game_logic.h"
#include "event.h"
#include "state_machine.h"
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

    /* TBD: disable DEBUG if DEBUG_EN is not true */

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
        case LOG_DEBUG:
            fprintf(log_file, "[DEBUG]: ");
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

    return;
}

void log_cleanup() {
    if (fclose(log_file) != 0) {
        perror("Error closing log file");
        // handle error appropriately
    }
}

// clang-format off
const char *log_enum_to_str_states(States state) {
    switch (state) {
        case STATE_NONE:        return STR_STATE_NONE;
        case STATE_INIT:        return STR_STATE_INIT;
        case STATE_EMPTY_BOARD: return STR_STATE_EMPTY_BOARD;
        case STATE_PLAYER_TURN: return STR_STATE_PLAYER_TURN;
        case STATE_CHECK_WIN:   return STR_STATE_CHECK_WIN;
        case STATE_END_GAME:    return STR_STATE_END_GAME;
        case STATE_ERROR:       return STR_STATE_ERROR;
        default:                return STR_STATE_LAST;
    }
}

const char *log_enum_to_str_events(Events event) {
    switch (event) {
        case EVENT_START_PROGRAM:       return STR_EVENT_START_PROGRAM;
        case EVENT_START_GAME:          return STR_EVENT_START_GAME;
        case EVENT_FIRST_PLAYER_ACTION: return STR_EVENT_FIRST_PLAYER_ACTION;
        case EVENT_PLAYER_FILLED_IN:    return STR_EVENT_PLAYER_FILLED_IN;
        case EVENT_PLAYER_NEXT_TURN:    return STR_EVENT_PLAYER_NEXT_TURN;
        case EVENT_WINNER_ANNOUNCE:     return STR_EVENT_WINNER_ANNOUNCE;
        case EVENT_END_GAME:            return STR_EVENT_END_GAME;
        case EVENT_RESTART:             return STR_EVENT_RESTART;
        default:                        return STR_EVENT_LAST;
    }
}
// clang-format on