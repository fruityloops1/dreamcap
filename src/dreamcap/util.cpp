#include "dreamcap/util.h"
#include "nfd.hpp"

std::string dc::fileDialog(nfdfilteritem_t* filter, size_t size, const std::string& startPath)
{
    nfdchar_t* path;
    nfdresult_t result = NFD::OpenDialog(path, filter, size, startPath.c_str());
    if (result == NFD_OKAY) {
        std::string p(path);
        NFD::FreePath(path);
        return p;
    } else
        return "none";
}

uint32_t dc::swapUInt24(uint32_t value)
{
    uint8_t* a = (uint8_t*)&value;
    uint8_t t = a[0];
    a[0] = a[2];
    a[2] = t;
    return value;
}

uint16_t dc::swapUInt16(uint16_t value)
{
    uint8_t* a = (uint8_t*)&value;
    uint8_t t = a[0];
    a[0] = a[1];
    a[1] = t;
    return value;
}