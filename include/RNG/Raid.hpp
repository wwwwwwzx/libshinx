#ifndef RAID_HPP
#define RAID_HPP

#include "Frame.hpp"

namespace RNG {
  Frame Raid(u64 seed, u8 FlawlessIV, u8 AbilityFlag, bool isRandomGender);
  u32 getRaidShinyFrame(u64 seed);
}  // namespace RNG

#endif  // RAID_HPP