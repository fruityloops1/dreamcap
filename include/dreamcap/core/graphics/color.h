#pragma once

#include <cstdint>

namespace dc {
namespace graphics {

    struct cRGB888 {
        uint8_t r, g, b;
    };

    struct cRGBA8888 {
        uint8_t r, g, b, a;
    };

    struct cRGBA5551 {
        int a : 2;
        uint8_t r : 5;
        /*union { // this is stupid
            struct {
                bool a : 1;
                uint8_t b : 5;
                uint8_t g : 5;
            };
            struct {
                uint16_t _abg : 11;
                uint8_t r : 5;
            };
        };*/
    };

} // namespace graphics
} // namespace dc