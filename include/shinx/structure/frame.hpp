#pragma once

#include <string>
#include "shinx/global.hpp"

namespace shinx {

class Frame {
   public:
    u64 Seed;
    u32 EC, PID;
    u8 IVs[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    u8 ShinyType, Gender, Ability, Nature;
    std::string toString();  // For debug
};

}  // namespace shinx
