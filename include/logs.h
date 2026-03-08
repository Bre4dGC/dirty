#pragma once

#include <stdarg.h>

typedef enum {
    REPORT_SUCCESS,
    REPORT_UNKNOWN_ERROR,
    REPORT_LIMIT_REACHED_ERROR,
    REPORT_HANDLE_ERROR,
    REPORT_EXECUTE_ERROR,
    REPORT_NOT_FOUND_ERROR,
    REPORT_ALREADY_EXISTS_ERROR,
    REPORT_INVALID_ARGUMENT_ERROR,
} log_report_t;

int log_init();
int log_report(const log_report_t rep_code, const char *act_msg);
int log_cleanup();
