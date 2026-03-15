#pragma once

#include <string>

#include "commands.hpp"
#include "logs.hpp"

namespace dirty
{
    namespace hk
    {
        class hotkey
        {
        private:
            std::string comb;
            cmd::command cmd;
            
        public:
            hotkey(const std::string comb, const cmd::command cmd);
            log::type execute(void);
        };
    }
}