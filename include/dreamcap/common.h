#pragma once

#define BIT(n) (1U << (n))

namespace dc {
namespace common {

    constexpr int defaultWindowWidth = 960;
    constexpr int defaultWindowHeight = 540;
    constexpr int defaultFPSCap = 90;

    constexpr char uiFont[] = "res/NotoSansJP-Regular.otf";

    constexpr char configPath[] = "dreamcap.json";

} // namespace common
} // namespace dreamcap