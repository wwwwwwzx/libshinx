#pragma once

#include "global.hpp"

namespace structure {
    class PK8 {
       public:
        PK8(u8* data);
        ~PK8();

        bool isValid();

        u16 Species();
        u16 AltForm();
        bool isGMax();

        u32 EC();  // Encryption Constant
        u32 PID();
        u16 SID();
        u16 TID();
        u8 ShinyType();

        bool isEgg();
        u8 IV(u8 stat);
        u8 EV(u8 stat);
        u16 Move(u8 slot);
        u8 Ability();
        u8 Nature();
        u8 StatNature();
        u8 Gender();
        bool isOT();
        u8 Friendship();

        const u32 blockSize = 80;
        const u32 storedSize = 0x148;
        const u32 partySize = 0x158;
        const u32 maxSpecies = 891;

       private:
        u8* data = new u8[storedSize];

        bool isEncrypted();
        void Decrypt();

        u16 Checksum();
        u16 CalculateChecksum();

        u32 IV32();
    };
}  // namespace structure
