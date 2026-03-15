#pragma once

#include <string>

#include "logs.hpp"

namespace dirty
{
    namespace fs
    {
        enum perm
        {
            NONE = 0,
            READ = 1,
            WRITE = 2,
            EXECUTE = 4,
            ALL = 7
        };

        struct item
        {
            std::string name;
            bool is_dir;
        };

        class directory
        {
        private:
            std::vector<fs::item> items;
            std::string path;
            int offset;
            int selected;
            
        public:
            directory(const std::string path);

            log::type open(void);
            log::type create(const std::string name, const bool is_dir);
            log::type rename(const std::string old_name, const std::string new_name);
            log::type move(const std::string dest);
            log::type copy(const std::string dest);
            log::type chmod(const fs::perm perm);
            log::type remove(void);
        };
    }
}