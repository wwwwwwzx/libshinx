#include "structure/raid_spawn.hpp"
#include "rng/raid.hpp"

namespace structure {
    // https://github.com/kwsch/PKHeX/blob/master/PKHeX.Core/Saves/Substructures/Gen8/RaidSpawnList8.cs

    enum RaidType : u8 { None = 0, Common = 1, Rare = 2, CommonWish = 3, RareWish = 4, Event = 5 };

    RaidSpawn::RaidSpawn(u8* data, u8 id) {
        ID = id;
        u64 Hash = *(u64*)data;
        Seed = *(u64*)(data + 8);
        Stars = *(u8*)(data + 0x10) + 1;
        u8 RandRoll = *(u8*)(data + 0x11);
        DenType = *(u8*)(data + 0x12);
        Flags = *(u8*)(data + 0x13);
        FindSpawn(Hash, RandRoll);
    }

    bool RaidSpawn::isActive() { return DenType != RaidType::None; }
    bool RaidSpawn::isRare() { return DenType == RaidType::Rare || DenType == RaidType::RareWish; }
    bool RaidSpawn::isWishingPiece() { return DenType == RaidType::CommonWish || DenType == RaidType::RareWish; }
    bool RaidSpawn::isEvent() { return isActive() && ((Flags >> 1) & 1) == 1; }

    u32 RaidSpawn::ShinyFrame() { return rng::getRaidShinyFrame(Seed); }
    void RaidSpawn::FindSpawn(u64 hash, u8 randroll) {
        // Look up encounter table entry
        // To do
        Species = 0;
        FlawlessIV = 4;
    }

}  // namespace structure