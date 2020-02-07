#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <cstdint>
#include <string>

using u64 = uint64_t;
using u32 = uint32_t;
using u16 = uint16_t;
using u8 = uint8_t;

enum GameVersion { Sword, Shield } CurrentGame;

namespace Util {
  u8 getShinyType(u32 tid, u32 pid);  // 0: No shiny, 1:Star shiny, 2: Squre shiny
  std::string Num2Str(u32 number);
  std::string Num2Str(u64 number);
}  // namespace Util

#endif  // GLOBAL_HPP