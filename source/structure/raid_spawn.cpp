#include "structure/raid_spawn.hpp"

// https://github.com/kwsch/PKHeX/blob/master/PKHeX.Core/Saves/Substructures/Gen8/RaidSpawnList8.cs

namespace structure {

    RaidSpawn::RaidSpawn(Data& raidSpawnData) : data(raidSpawnData) {}
    RaidSpawn::~RaidSpawn() {}

    // void RaidSpawn::FindSpawn(u64 hash, u8 randroll) {
    //     // Look up encounter table entry
    //     // TODO
    // }

    RaidSpawnList::RaidSpawnList(u8 raidSpawnListData[DATA_SIZE]) {
        std::copy(raidSpawnListData, raidSpawnListData + DATA_SIZE, m_data);
    }

    RaidSpawnList::~RaidSpawnList() {}

    RaidSpawn* RaidSpawnList::getWishingPieceDen(int& denNum) {
        for (denNum = 0; denNum < (int)LIST_SIZE; denNum++) {
            RaidSpawn* curDen = &getDens()[denNum];
            if (curDen->isWishingPiece()) {
                return curDen;
            }
        }
        denNum = -1;
        return nullptr;
    }

}  // namespace structure
