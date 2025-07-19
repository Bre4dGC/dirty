#include <stdio.h>
#include <time.h>

#include "logs.h"

static FILE *log_f = NULL;

int log_init()
{
        return SUCCESS;
}

int log_message(const char *message, ...)
{
        va_list args;
        va_start(args, message);

        log_f = fopen("config/logs.txt", "a");

        if (log_f == NULL)
        {
                return -1;
        }

        vfprintf(log_f, message, args);
        fprintf(log_f, "\n");
        fclose(log_f);

        va_end(args);

        return SUCCESS;
}

int log_status(const error_t status, const char *action)
{
        log_f = fopen("config/logs.txt", "a");

        if (log_f == NULL)
        {
                return -1;
        }

        time_t t = time(NULL);
        struct tm *tm_info = localtime(&t);

        char time_buf[32];
        strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", tm_info);

        fprintf(log_f, "[%s] ", time_buf);

        switch (status)
        {
        case SUCCESS:
                fprintf(log_f, "Success: %s\n", action);
                break;

        case LIMIT_REACHED_ERROR:
                fprintf(log_f, "Error: %s limit reached\n", action);
                break;

        case HANDLE_ERROR:
                fprintf(log_f, "Error: %s handle failed\n", action);
                break;

        case EXECUTE_ERROR:
                fprintf(log_f, "Error: %s execute failed\n", action);
                break;

        case NOT_FOUND_ERROR:
                fprintf(log_f, "Error: %s not found\n", action);
                break;

        case ALREADY_EXISTS_ERROR:
                fprintf(log_f, "Error: %s already exist\n", action);
                break;

        case UNKNOWN_ERROR:
                fprintf(log_f, "Error: %s unknown\n", action);
                break;
        }

        fflush(log_f);

        return status;
}
