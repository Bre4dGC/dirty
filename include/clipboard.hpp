#pragma once

#include <string>

#include "filesystem.hpp"

#define CLIPBOARD_LIMIT 5

namespace dirty
{
    namespace cb
    {
        struct item
        {
            std::string path;
            std::string name;
            bool is_cut;
        };

        class clipboard
        {
            cb::item items[CLIPBOARD_LIMIT];
            int selected;

            int copy(fs::item item);
            int cut(fs::item item);
            int paste(fs::directory dir, const int index);
        };
    }
}