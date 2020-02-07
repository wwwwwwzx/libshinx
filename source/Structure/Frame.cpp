#include "structure/Frame.hpp"

#include <sstream>

std::string Frame::toString() {
    // dump raw info
    std::stringstream ss;
    ss << std::hex << Seed << " " << EC << " " << PID << " " << std::dec << +ShinyType;
    ss << " " << +IVs[0] << " " << +IVs[1] << " " << +IVs[2] << " " << +IVs[3] << " " << +IVs[4] << " " << +IVs[5];
    ss << " " << +Nature << " " << +Ability << " " << +Gender;
    return ss.str();
};
