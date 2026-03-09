#pragma once

#include <string>

#include "commands.hpp"

namespace dirty
{
    namespace hk
    {
        class hotkey
        {
            std::string comb;
            cmd::command cmd;

            int execute(void);
        };
    }
}