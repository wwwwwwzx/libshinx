#include "structure/raid_spawn.hpp"

// https://github.com/kwsch/PKHeX/blob/master/PKHeX.Core/Saves/Substructures/Gen8/RaidSpawnList8.cs

namespace structure {

    RaidSpawn::RaidSpawn(RaidSpawn::Data raidSpawnData) : data(raidSpawnData) {}
    RaidSpawn::~RaidSpawn() {}

    // void RaidSpawn::FindSpawn(u64 hash, u8 randroll) {
    //     // Look up encounter table entry
    //     // TODO
    // }

}  // namespace structure
