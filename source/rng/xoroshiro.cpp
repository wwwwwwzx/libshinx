#include "rng/xoroshiro.hpp"

static inline u64 rotl(u64 x, u8 k) {
    return (x << k) | (x >> (64 - k));
}

namespace rng {
    xoroshiro::xoroshiro(u64 seed) : state{seed, 0x82A2B175229D6A5B} {}

    u64 xoroshiro::nextulong() {
        const u64 s0 = state[0];
        u64 s1 = state[1];
        const u64 result = s0 + s1;

        s1 ^= s0;
        state[0] = rotl(s0, 24) ^ s1 ^ (s1 << 16);
        state[1] = rotl(s1, 37);

        return result;
    }

    u32 xoroshiro::nextuint() { return static_cast<u32>(nextulong()); }

    u32 xoroshiro::rand(u32 mask) { return nextulong() & mask; }

    u32 xoroshiro::rand(u32 N, u32 mask) {
        u32 result;
        do {
            result = nextulong() & mask;
        } while (result >= N);
        return result;
    }

    void xoroshiro::reseed(u64 seed) {
        state[0] = seed;
        state[1] = 0x82A2B175229D6A5B;
    }
}  // namespace rng
