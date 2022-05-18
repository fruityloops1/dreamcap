#include "dreamcap/core/io/bio.h"
#include <cstring>

dc::io::BinaryReader::BinaryReader(const void* data, size_t len)
{
    mData = new unsigned char[len];
    mSize = len;
    std::memcpy((void*)mData, data, len);
}

dc::io::BinaryReader::~BinaryReader()
{
    delete[] mData;
}

void dc::io::BinaryReader::seek(size_t pos)
{
    if (pos >= mSize)
        throw std::out_of_range("pos larger than size");
    mPos = pos;
}