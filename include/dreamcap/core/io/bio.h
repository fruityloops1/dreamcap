#pragma once

#include <stdexcept>

namespace dc {
namespace io {

    class BinaryReader {
    public:
        BinaryReader(const void* data, size_t len);
        ~BinaryReader();

        template <typename T>
        T& read()
        {
            if (mPos + sizeof(T) >= mSize)
                throw std::out_of_range("reached end of file");
            T& value = *(T*)&mData[mPos];
            mPos += sizeof(T);
            return value;
        }

        void seek(size_t pos);
        inline size_t tell() const { return mPos; }
        inline size_t size() const { return mSize; }

    private:
        const uint8_t* mData = nullptr;
        size_t mSize = 0;
        size_t mPos = 0;
    };

} // namespace io
} // namespace bfres