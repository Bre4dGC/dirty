#include <stdio.h>

#include "include/logs.h"

int log_message(const char *message, ...)
{
        va_list args;
        va_start(args, message);

        FILE *log_f = fopen("../config/logs.txt", "a");

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
        FILE *log_f = fopen("../config/logs.txt", "a");

        if (log_f == NULL)
        {
                return -1;
        }

        switch (status)
        {
        case SUCCESS:
                fprintf(log_f, "Success: %s", action);
                break;

        case LIMIT_REACHED_ERROR:
                fprintf(log_f, "Error: %s limit reached", action);
                break;

        case HANDLE_ERROR:
                fprintf(log_f, "Error: %s handle failed", action);
                break;

        case EXECUTE_ERROR:
                fprintf(log_f, "Error: %s execute failed", action);
                break;

        case NOT_FOUND_ERROR:
                fprintf(log_f, "Error: %s not found", action);
                break;

        case ALREADY_EXISTS_ERROR:
                fprintf(log_f, "Error: %s already exist", action);
                break;

        case UNKNOWN_ERROR:
                fprintf(log_f, "Error: %s unknown", action);
                break;
        }

        fclose(log_f);

        return status;
}