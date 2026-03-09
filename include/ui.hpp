#pragma once

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

        int init(void);
        int run(void);
        int update(void);
        int draw(void);
        int handle_input(void);
        int cleanup(void);
    }
}