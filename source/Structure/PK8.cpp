#include "structure/pk8.hpp"

namespace structure {
    // https://github.com/kwsch/PKHeX/blob/master/PKHeX.Core/PKM/PK8.cs

    PK8::PK8(u8* data) {
        std::copy(data, data + storedSize, this->data);
        if (this->isEncrypted())
            Decrypt();
    }
    PK8::~PK8() { delete[] data; }

    bool PK8::isValid() { return 0 < Species() && Species() < maxSpecies && Checksum() == CalculateChecksum(); }

    u16 PK8::Species() { return *(u16*)(data + 0x8); }
    u16 PK8::AltForm() { return *(u16*)(data + 0x24); }
    bool PK8::isGMax() { return (*(u8*)(data + 0x14) & 16) != 0; }

    u32 PK8::EC() { return *(u32*)data; }
    u16 PK8::TID() { return *(u16*)(data + 0xC); }
    u16 PK8::SID() { return *(u16*)(data + 0xE); }
    u32 PK8::PID() { return *(u32*)(data + 0x1C); }
    u8 PK8::ShinyType() { return Util::getShinyType(*(u32*)(data + 0xC), PID()); }

    u32 PK8::IV32() { return *(u32*)(data + 0x8C); }
    bool PK8::isEgg() { return ((IV32() >> 30) & 1) == 1; }
    static constexpr const u8 StatsOrder[] = {0, 1, 2, 4, 5, 3};
    u8 PK8::IV(u8 stat) { return (IV32() >> (5 * StatsOrder[stat])) & 0x1F; }
    u8 PK8::EV(u8 stat) { return *(u8*)(data + 0x26 + StatsOrder[stat]); }
    u16 PK8::Move(u8 slot) { return *(u16*)(data + 0x72 + (slot * 2)); }
    u8 PK8::Ability() { return *(u8*)(data + 0x14); }
    u8 PK8::Nature() { return *(u8*)(data + 0x20); }
    u8 PK8::StatNature() { return *(u8*)(data + 0x21); }
    u8 PK8::Gender() { return (*(u8*)(data + 0x22) >> 2) & 0x3; }
    bool PK8::isOT() { return *(u8*)(this->data + 0xC4) == 0; }
    u8 PK8::Friendship() { return isOT() ? *(u8*)(data + 0x112) : *(u8*)(data + 0xC8); }

    u16 PK8::Checksum() { return *(u16*)(data + 0x6); }
    u16 PK8::CalculateChecksum() {
        u16 chk = 0;
        for (u16 i = 8; i < storedSize; i += 2) {
            chk += *(u16*)(data + i);
        }
        return chk;
    }

    bool PK8::isEncrypted() { return *(u16*)(data + 0x70) != 0 && *(u16*)(data + 0xC0) != 0; }
    static inline u32 lcrng(u32 seed) { return seed * 0x41C64E6D + 0x00006073; }
    // clang-format off
    static constexpr const u8 BlockPosition[128] = {
        0, 1, 2, 3,
        0, 1, 3, 2,
        0, 2, 1, 3,
        0, 3, 1, 2,
        0, 2, 3, 1,
        0, 3, 2, 1,
        1, 0, 2, 3,
        1, 0, 3, 2,
        2, 0, 1, 3,
        3, 0, 1, 2,
        2, 0, 3, 1,
        3, 0, 2, 1,
        1, 2, 0, 3,
        1, 3, 0, 2,
        2, 1, 0, 3,
        3, 1, 0, 2,
        2, 3, 0, 1,
        3, 2, 0, 1,
        1, 2, 3, 0,
        1, 3, 2, 0,
        2, 1, 3, 0,
        3, 1, 2, 0,
        2, 3, 1, 0,
        3, 2, 1, 0,

        // duplicates of 0-7 to eliminate modulus
        0, 1, 2, 3,
        0, 1, 3, 2,
        0, 2, 1, 3,
        0, 3, 1, 2,
        0, 2, 3, 1,
        0, 3, 2, 1,
        1, 0, 2, 3,
        1, 0, 3, 2,
    };
    // clang-format on

    void PK8::Decrypt() {
        u32 seed = EC();
        u8 sv = (EC() >> 13) & 31;

        // CryptPKM
        u16* pword;
        for (u32 i = 8; i < storedSize; i += 2) {
            seed = lcrng(seed);
            pword = (u16*)(data + i);
            *pword = *pword ^ (seed >> 16);
        }

        // Shuffle Array
        u8 index = sv * 4;
        u8 sdata[storedSize];
        std::copy(data, data + storedSize, sdata);

        for (u8 block = 0; block < 4; block++) {
            u8 ofs = BlockPosition[index + block];
            std::copy(sdata + 8 + blockSize * ofs, sdata + 8 + blockSize * (ofs + 1), data + 8 + blockSize * block);
        }
    }
}  // namespace structure
