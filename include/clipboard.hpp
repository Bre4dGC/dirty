#pragma once

#include <string>

#include "filesystem.hpp"
#include "logs.hpp"

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
        private:
            cb::item items[CLIPBOARD_LIMIT];
            int selected;

        public:
            clipboard();
            log::type add(const cb::item item, const bool is_cut);
            log::type paste(fs::directory dir, const int index);
            log::type clear(void);
        };
    }
}