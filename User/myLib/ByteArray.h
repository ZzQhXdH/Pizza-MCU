#ifndef     __X_BYTE_ARRAY_H
#define     __X_BYTE_ARRAY_H

#include <stdint.h>
#include "myLib/Template.h"

namespace myLib
{
    class ByteArray
    {
        public:
            inline ByteArray(uint8_t *buffer) : pByteArrayBuffer(buffer), nIndex(0) {}

            inline ByteArray(const ByteArray &bytes) : pByteArrayBuffer(bytes.getData()), nIndex(bytes.getLength()) {}

            ByteArray& operator =(const ByteArray &bytes)
            {
                pByteArrayBuffer = bytes.getData();
                nIndex = bytes.getLength();
                return *this;
            }

            inline uint8_t& operator [](uint32_t index)
            {
                return pByteArrayBuffer[index];
            }

            inline ByteArray &append(uint8_t byte)
            {
                pByteArrayBuffer[nIndex ++] = byte;
                return *this;
            }

            inline ByteArray &append(const char *bytes, uint32_t size)
            {
                copy(pByteArrayBuffer + nIndex, bytes, size);
                nIndex += size;
                return *this;
            }

            inline uint32_t getLength() const {
                return nIndex;
            }

            inline uint8_t *getData() const {
                return pByteArrayBuffer;
            }

        private:
            uint8_t *pByteArrayBuffer;
            uint32_t nIndex;
    };
}







#endif

