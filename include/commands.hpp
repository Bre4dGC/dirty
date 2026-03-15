#pragma once

#include <string>

#include "filesystem.hpp"
#include "clipboard.hpp"
#include "logs.hpp"

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
        private:
            std::string name;
            std::string description;
            std::string options;

        public:
            command(const std::string name, const std::string description, const std::string options);
            log::type execute(void);
        };
    }
}