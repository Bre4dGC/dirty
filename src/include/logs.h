#pragma once

#include <stdarg.h>
#include "./errors.h"

int log_message(const char *message, ...);
int log_status(const error_t status, const char *action);