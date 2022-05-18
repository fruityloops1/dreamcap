#pragma once

#include "dreamcap/core/graphics/color.h"
#include <cstring>
#include <stdexcept>
#include <vector>

namespace dc {
namespace graphics {

    template <typename C>
    struct Sprite {

        Sprite(const std::vector<uint8_t>& vec, int width, int height)
            : data(dupFromVector(vec))
            , width(width)
            , height(height)
        {
        }
        ~Sprite()
        {
            delete[] data;
        }

        const int width, height;

        C& at(int x, int y)
        {
            if (x >= width)
                throw std::invalid_argument("at(): x exceeds width");
            if (y >= height)
                throw std::invalid_argument("at(): y exceeds height");
            return data[x + y * width];
        }
        C& operator()(int x, int y)
        {
            return at(x, y);
        }
        std::vector<uint8_t> toRaw()
        {
            std::vector<uint8_t> rawData;
            rawData.resize(width * height * sizeof(C));
            std::memcpy(rawData.data(), data, width * height * sizeof(C));
            return rawData;
        }

    private:
        C* const data;
        C* dupFromVector(const std::vector<uint8_t>& vec)
        {
            C* data = new C[vec.size() / sizeof(C)];
            std::memcpy(data, vec.data(), vec.size());
            return data;
        }
    };

    typedef Sprite<cRGBA5551> SpriteRGBA5551;
    typedef Sprite<cRGBA8888> SpriteRGBA;
    typedef Sprite<cRGB888> SpriteRGB;

} // namespace graphics
} // namespace dc