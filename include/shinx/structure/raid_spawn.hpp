#pragma once

#include "shinx/global.hpp"
#include "shinx/rng/raid.hpp"

namespace shinx {

namespace structure {
    class RaidSpawn {
       public:
        enum RaidType : u8 { EMPTY = 0, COMMON = 1, RARE = 2, WISHING_COMMON = 3, WISHING_RARE = 4, EVENT_COMMON = 5 };

        struct Data {
            u64 hash;
            u64 seed;
            u8 starCount;
            u8 roll;
            RaidType type;
            u8 flags;
            u32 unk;
        } data;

        RaidSpawn(Data& raidSpawnData);
        ~RaidSpawn();

        inline bool isActive() { return data.type != RaidType::EMPTY; }
        inline bool isRare() { return data.type == RaidType::RARE || data.type == RaidType::WISHING_RARE; }
        inline bool isWishingPiece() {
            return data.type == RaidType::WISHING_COMMON || data.type == RaidType::WISHING_RARE;
        }
        inline bool isEvent() { return data.flags & (1 << 1); }
        inline u32 getNextShinyFrameNum() { return rng::getRaidShinyFrame(data.seed); }

        // TODO:
        // void FindSpawn(u64 hash, u8 randroll);

        // TODO: refactor these somewhere else going forward
        // u8 ID;
        // u16 Species;
        // u8 FlawlessIV;
    };

    class RaidSpawnList {
       public:
        static constexpr u32 LIST_SIZE = 111;
        static constexpr u32 DATA_SIZE = sizeof(RaidSpawn) * LIST_SIZE;

        RaidSpawnList(u8 raidSpawnListData[DATA_SIZE]);
        ~RaidSpawnList();

        inline RaidSpawn* getDens() { return (RaidSpawn*)m_data; }
        RaidSpawn* getWishingPieceDen(int& out_denNum);

       private:
        u8 m_data[DATA_SIZE];
    };

}  // namespace structure

}  // namespace shinx
