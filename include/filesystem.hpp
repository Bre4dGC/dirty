#pragma once

#include <string>

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
            fs::item *items;
            std::string path;
            int offset;
            int selected;

            int open(void);
            int create(const std::string name, const bool is_dir);
            int rename(const std::string old_name, const std::string new_name);
            int move(const std::string dest);
            int chmod(const fs::perm perm);
            int remove(void);
        };
    }
}