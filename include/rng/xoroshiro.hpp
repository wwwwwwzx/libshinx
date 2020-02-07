#pragma once

#include "global.hpp"

namespace rng {
    class xoroshiro {
       public:
        xoroshiro(u64 seed);
        u64 nextulong();
        u32 nextuint();
        u32 rand(u32 mask);
        u32 rand(u32 N, u32 mask);
        void reseed(u64 seed);

       private:
        u64 state[2];
    };
}  // namespace rng
