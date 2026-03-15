#include "hotkeys.hpp"

namespace dirty
{
    namespace hk
    {
        hotkey::hotkey(const std::string comb, const cmd::command cmd)
        {
            this->comb = comb;
            this->cmd = cmd;
        }

        log::type hotkey::execute(void)
        {
            // TODO: implement
        }
    }
}