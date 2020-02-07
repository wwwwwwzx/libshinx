#include "global.hpp"
#include <sstream>

u8 Util::getShinyType(u32 tid, u32 pid) {
    auto XOR = (tid & 0xFFFF) ^ (tid >> 16) ^ (pid & 0xFFFF) ^ (pid >> 16);
    if (XOR > 15)
        return 0;
    else
        return (XOR == 0 ? 2 : 1);
}

std::string Util::Num2Str(u32 number) {
    std::stringstream sss;
    sss << std::hex << number;
    return sss.str();
}

std::string Util::Num2Str(u64 number) {
    std::stringstream sss;
    sss << std::hex << number;
    return sss.str();
}
