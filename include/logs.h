#ifndef LOGS_H
#define LOGS_H

/* log levels */
#define LOG_INFO  1
#define LOG_WARN  2
#define LOG_ERROR 3
#define LOG_DEBUG 4

/**
 * @brief initiate log file
 */
void log_init();

/**
 * @brief add log message to log file
 */
void log_message(int log_level, const char *format, ...);

/**
 * @brief clean up log file
 */
void log_cleanup();

/**
 * @brief enum to string translations for enum States
 */
const char* log_enum_to_str_states(States state);

/**
 * @brief enum to string translations for enum Events
 */
const char* log_enum_to_str_events(Events event);

#endif // LOGS_H
