#ifndef FRAME_HPP
#define FRAME_HPP

#include <string>
#include "global.hpp"

class Frame {
 public:
  u64 Seed;
  u32 EC, PID;
  u8 IVs[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  u8 ShinyType, Gender, Ability, Nature;
  std::string toString();  // For debug
};

#endif  // FRAME_HPP