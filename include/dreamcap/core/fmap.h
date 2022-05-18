#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace dc {

/*
 * This table found in code.bin stores pointers and sizes to files found in FMapDat.dat (FMapDataArchive)
 */
struct FMapDataFileTable {
    struct Entry {
        uint32_t offset;
        uint32_t size;
    };
    std::vector<Entry> entries;
    void load(const std::string& codePath);
    std::vector<uint8_t> toIPS(uint32_t location1, uint32_t location2);
};

/*
 * Offsets to the FMapData File Tables found in code.bin
 * These are used to make IPS patches to replace the tables
 */
static const std::unordered_map<uint16_t, std::pair<uint32_t, uint32_t>> regionOffsets = {
    { 0x2124, { 0x584d44, 0x59229c } /* EU 1.0 */ }, { 0x211c, { 0x584ccc, 0x592224 } /* US 1.0 */ }
};

/*
 * One of these represents 1 room in the game, these are stored back-to-back in FMapDat.dat (FMapDataArchive)
 */
class FMapData {
public:
    class Section {
    public:
        enum Type : uint8_t {
            Unk0 = 0,
            Graphics = 1,
            Unk2 = 2,
            Unk3 = 3,
            Unk4 = 4,
            Unk5 = 5,
            Warp = 6,
            Unk7 = 7,
            CameraLock = 8,
            Unk9 = 9,
            Unk10 = 10,
            Unk11 = 11,
            Model = 12
        };
        Section();
        Section(Type t)
            : mType(t)
        {
        }

        void parse(const std::vector<uint8_t>& data);
        std::vector<uint8_t> toBinary();
        inline Type getType() { return mType; }

    private:
        std::vector<uint8_t> mData;
        Type mType;
    };

    void fromBinary(const std::vector<uint8_t>& data);
    std::vector<uint8_t> toBinary();

private:
    struct Header {
        struct {
            uint32_t offset;
            uint32_t size;
        } sections[13];
    };
    std::vector<Section> mSections;
    bool mIsCGFX = false;
};

/*
 * This is an uncompressed archive that houses FMapData entries, texture archives, and minimaps
 * The offsets to entries in this file are stored in the file table found in the code.bin (FMapDataFileTable)
 */
class FMapDataArchive {
public:
    void fromFile(const std::string& filename, const FMapDataFileTable& table);
    std::vector<uint8_t> toBinary(FMapDataFileTable* table = nullptr);

private:
    std::vector<FMapData> mFiles;
};

} // namespace dc