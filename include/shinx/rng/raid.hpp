#pragma once

#include "../structure/frame.hpp"

namespace shinx {

namespace rng {
    Frame raid(u64 seed, u8 FlawlessIV, u8 AbilityFlag, bool isRandomGender);
    u32 getRaidShinyFrame(u64 seed);
}  // namespace rng

}  // namespace shinx
