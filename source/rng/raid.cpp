#include "rng/Raid.hpp"
#include "rng/xoroshiro.hpp"

namespace rng {
    Frame Raid(u64 seed, u8 FlawlessIV, u8 AbilityFlag, bool isRandomGender) {
        Frame result;
        auto rng = xoroshiro(seed);
        result.Seed = seed;

        // EC
        result.EC = rng.nextuint();

        // PID and Shininess
        u32 OT = rng.nextuint();
        result.PID = rng.nextuint();
        result.ShinyType = Util::getShinyType(OT, result.PID);

        // IVs
        for (u8 i = 0; i < FlawlessIV;) {
            u8 index = static_cast<u8>(rng.rand(6, 7));
            if (result.IVs[index] == 0xFF) {
                result.IVs[index] = 31;
                i++;
            }
        }
        for (u8 i = 0; i < 6; i++)
            if (result.IVs[i] == 0xFF) {
                result.IVs[i] = static_cast<u8>(rng.rand(0x1F));
            }

        // Ability
        if (AbilityFlag == 4)  // Allow HA
            result.Ability = rng.rand(3) + 1;
        else if (AbilityFlag == 3)
            result.Ability = rng.rand(2, 3) + 1;
        else
            result.Ability = AbilityFlag + 1;

        // Gender
        result.Gender = isRandomGender ? rng.rand(253, 0xFF) : 0xFF;

        // Nature
        result.Nature = rng.rand(25, 0x1F);

        return result;
    }

    u32 getRaidShinyFrame(u64 seed) {
        u32 ShinyFrame = 0;
        while (ShinyFrame < 99999) {
            auto rng = xoroshiro(seed);
            seed = rng.nextulong();  // Also advance for EC
            u32 TID = rng.nextuint();
            u32 PID = rng.nextuint();
            if (Util::getShinyType(TID, PID) > 0)
                return ShinyFrame;
            else
                ShinyFrame++;
        }
        return ShinyFrame;
    }
}  // namespace rng
