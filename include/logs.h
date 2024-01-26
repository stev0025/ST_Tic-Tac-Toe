#ifndef LOGS_H
#define LOGS_H

/* log levels */
#define LOG_INFO  1
#define LOG_WARN  2
#define LOG_ERROR 3

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

#endif // LOGS_H
