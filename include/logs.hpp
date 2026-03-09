#pragma once

#include <string>

namespace dirty
{
    namespace log
    {
        enum type
        {
            SUCCESS,
            UNKNOWN_ERROR,
            LIMIT_REACHED_ERROR,
            HANDLE_ERROR,
            EXECUTE_ERROR,
            NOT_FOUND_ERROR,
            ALREADY_EXISTS_ERROR,
            INVALID_ARGUMENT_ERROR,
        };

        int report(const log::type code, const std::string action);
    }
}