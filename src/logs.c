#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

#include "logs.h"

static FILE *log_f = NULL;

int log_init()
{
    if(log_f)
    {
        return log_report(REPORT_SUCCESS, "Configuration already initialized");
    }
    
    log_f = fopen("config/logs.txt", "a");
    if(!log_f)
    {
        fclose(log_f);
        fprintf(stderr, "Failed to open log file.\n");
        return log_report(REPORT_EXECUTE_ERROR, "Log initialize");
    }
    return log_report(REPORT_SUCCESS, "Log initialized");
}

int log_report(const log_report_t code, const char *action_msg)
{
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    char time_buf[32];
    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", tm_info);

    fprintf(log_f, "[%s] ", time_buf);

    switch (code)
    {
        case REPORT_SUCCESS:
            fprintf(log_f, "Success: %s\n", action_msg);
            break;
        case REPORT_LIMIT_REACHED_ERROR:
            fprintf(log_f, "Error: %s limit reached\n", action_msg);
            break;
        case REPORT_HANDLE_ERROR:
            fprintf(log_f, "Error: %s handle failed\n", action_msg);
            break;
        case REPORT_EXECUTE_ERROR:
            fprintf(log_f, "Error: %s execute failed\n", action_msg);
            break;
        case REPORT_NOT_FOUND_ERROR:
            fprintf(log_f, "Error: %s not found\n", action_msg);
            break;
        case REPORT_ALREADY_EXISTS_ERROR:
            fprintf(log_f, "Error: %s already exist\n", action_msg);
            break;
        case REPORT_UNKNOWN_ERROR:
            fprintf(log_f, "Error: %s unknown\n", action_msg);
            break;
        case REPORT_INVALID_ARGUMENT_ERROR:
            fprintf(log_f, "Error: \"%s\" invalid argument\n", action_msg);
            break;
    }

    fflush(log_f);

    return code;
}

int log_cleanup()
{
    fclose(log_f);
    return 0;
}
