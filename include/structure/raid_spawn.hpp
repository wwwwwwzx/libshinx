#pragma once

#include "global.hpp"

namespace structure {
    class RaidSpawn {
       public:
        RaidSpawn(u8* data, u8 id);
        ~RaidSpawn();
        u8 ID;
        u64 Seed;
        u8 Stars;

        bool isActive();
        bool isRare();
        bool isWishingPiece();
        bool isEvent();

        u32 ShinyFrame();
        u16 Species;
        u8 FlawlessIV;

       private:
        u8 DenType;
        u8 Flags;
        void FindSpawn(u64 hash, u8 randroll);
    };
}  // namespace structure
