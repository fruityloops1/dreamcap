
#include "dreamcap/core/fmap.h"
#include "dreamcap/util.h"
#include <cstdint>
#include <cstring>
#include <fstream>
#include <vector>

void dc::FMapDataFileTable::load(const std::string& codePath)
{
    std::ifstream code(codePath, std::ios::binary);
    code.unsetf(std::ios::skipws);
    code.seekg(0x44); // region id is at 0x44
    uint16_t region;
    code.read((char*)&region, 2);
    if (!dc::regionOffsets.contains(region))
        throw std::invalid_argument("Region unsupported (EU 1.0, US 1.0 supported)");
    code.seekg(dc::regionOffsets.at(region).first + 8);
    uint32_t length;
    code.read((char*)&length, 4);
    length -= 16; // skip header
    length /= sizeof(Entry);
    uint32_t cOffset = dc::regionOffsets.at(region).first + 16;
    for (int i = 0; i < length; i++) {
        code.seekg(cOffset);
        Entry e;
        code.read((char*)&e, sizeof(Entry));
        entries.push_back(e);
        cOffset += 8;
    }
    code.close();
}

std::vector<uint8_t> dc::FMapDataFileTable::toIPS(uint32_t location1, uint32_t location2)
{
    std::vector<uint8_t> data;
    uint16_t size = dc::swapUInt16(entries.size() * sizeof(Entry));
    uint32_t offset = dc::swapUInt24(location1 + 0x10);
    data.insert(data.begin(), { 0x50, 0x41, 0x54, 0x43, 0x48 }); // "PATCH"
    data.insert(data.end(), (char*)&offset, ((char*)&offset) + 3);
    data.insert(data.end(), (char*)&size, ((char*)&size) + sizeof(size));
    data.insert(data.end(), (char*)entries.data(), (char*)entries.data() + entries.size() * sizeof(Entry));
    offset = dc::swapUInt24(location2 + 0x10);
    data.insert(data.end(), (char*)&offset, ((char*)&offset) + 3);
    data.insert(data.end(), (char*)&size, ((char*)&size) + sizeof(size));
    data.insert(data.end(), (char*)entries.data(), (char*)entries.data() + entries.size() * sizeof(Entry));
    data.insert(data.end(), { 0x45, 0x4F, 0x46 }); // "EOF"
    return data;
}

void dc::FMapData::fromBinary(const std::vector<uint8_t>& data)
{
    if (*(uint32_t*)data.data() == 1481000771) // "CGFX"
    {
        mIsCGFX = true;
        mSections.push_back(Section(Section::Model));
        mSections[mSections.size() - 1].parse(data);
        return;
    }
    Header header = *(Header*)data.data();
    Section::Type type = Section::Type::Unk0;
    for (int i = 0; i < 13; i++) {
        std::vector<uint8_t> sectionData;
        sectionData.reserve(header.sections[i].size);
        sectionData.insert(sectionData.begin(), data.begin() + header.sections[i].offset, data.begin() + header.sections[i].offset + header.sections[i].size);
        mSections.push_back(Section(type));
        mSections[mSections.size() - 1].parse(sectionData);
        (*(uint8_t*)&type)++;
    }
}

std::vector<uint8_t> dc::FMapData::toBinary()
{
    if (mSections.empty())
        return {};
    else if (mSections[0].getType() == Section::Type::Model)
        return mSections[0].toBinary();

    std::vector<uint8_t> data;
    Header header;
    for (int i = 0; i < 13; i++) {
        header.sections[i].offset = data.size() + sizeof(Header);
        std::vector<uint8_t> sectionData = mSections[i].toBinary();
        header.sections[i].size = sectionData.size();
        data.insert(data.end(), sectionData.begin(), sectionData.end());
    }
    data.insert(data.begin(), (char*)&header, ((char*)&header) + sizeof(Header));
    return data;
}

void dc::FMapDataArchive::fromFile(const std::string& filename, const FMapDataFileTable& table)
{
    std::ifstream data(filename, std::ios::binary);
    data.unsetf(std::ios::skipws);
    for (const FMapDataFileTable::Entry& entry : table.entries) {
        std::vector<uint8_t> dataVector;
        data.seekg(entry.offset);
        dataVector.resize(entry.size);
        data.read((char*)dataVector.data(), entry.size);
        FMapData fmap;
        fmap.fromBinary(dataVector);
        mFiles.push_back(fmap);
    }
}

std::vector<uint8_t> dc::FMapDataArchive::toBinary(FMapDataFileTable* table)
{
    if (table)
        table->entries.clear();
    std::vector<uint8_t> data;
    for (FMapData& fmap : mFiles) {
        std::vector<uint8_t> fmapData = fmap.toBinary();
        if (table)
            table->entries.push_back({ (uint32_t)(data.size()), (uint32_t)(fmapData.size()) });
        data.insert(data.end(), fmapData.begin(), fmapData.end());
    }
    return data;
}

std::vector<uint8_t> dc::FMapData::Section::toBinary()
{
    return mData;
}

void dc::FMapData::Section::parse(const std::vector<uint8_t>& data)
{
    mData = data;
}