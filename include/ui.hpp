#pragma once

#include "logs.hpp"

namespace dirty
{
    namespace ui
    {
        enum section
        {
            DIRECTORY,
            CONTENT,
            INFO,
            RECENT,
            CLIPBOARD,
            CMD
        };

        enum content_type
        {
            LIST,
            TEXT,
            IMAGE
        };

        log::type init(void);
        log::type run(void);
        log::type update(void);
        log::type draw(void);
        log::type handle_input(void);
        log::type cleanup(void);
    }
}