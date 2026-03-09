#pragma once

#include <string>

#include "filesystem.hpp"
#include "clipboard.hpp"

namespace dirty
{
    namespace cmd
    {
        enum type
        {
            OPEN,
            MOVE,
            RENAME,
            REMOVE,
            CREATE,
            CHMOD,
            COPY,
            CUT,
        };

        class command
        {
            std::string name;
            std::string description;
            std::string options;

            int execute(void);
        };
    }
}