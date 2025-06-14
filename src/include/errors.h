#pragma once

typedef enum tag_error_e
{
        SUCCESS = 0,
        LIMIT_REACHED_ERROR = 1,
        HANDLE_ERROR = 2,
        EXECUTE_ERROR = 3,
        NOT_FOUND_ERROR = 4,
        ALREADY_EXISTS_ERROR = 5,
        UNKNOWN_ERROR = 6,
        INVALID_ARGUMENT_ERROR = 7,
} error_t;