#pragma once

#include <string>

namespace dc {

struct Config {
    bool load(const std::string& filename);
    void save(const std::string& filename);
    void defaultv();

    std::string extractedFMapPath;
    int uiSize = 16;
};

} // namespace dc