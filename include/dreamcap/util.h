#pragma once

#include "nfd.h"
#include <string>

namespace dc {

/*
 * Opens a dialog to select a file, and returns the path of the file.
 * Returns "none" if the file select is canceled or invalid
 * This function is thread-blocking
 */
std::string fileDialog(nfdfilteritem_t* filter, size_t size, const std::string& startPath);

/*
 * Returns a byte swapped version of value
 * Assumes value is a 24 bit unsigned integer
 */
uint32_t swapUInt24(uint32_t value);

/*
 * Returns a byte swapped version of value
 */
uint16_t swapUInt16(uint16_t value);

} // namespace dc