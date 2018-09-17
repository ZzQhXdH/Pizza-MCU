#ifndef     __X_LOGGER_H
#define     __X_LOGGER_H

#include <stdint.h>
#include "myLib/ByteArray.h"

namespace myLib
{
    class Logger
    {
        public:
            Logger(uint8_t *buffer);

            virtual Logger& operator <<(const char *msg) =0;

            virtual Logger& write(const uint8_t *byteArray, uint32_t length) = 0;

            inline Logger& operator <<(const ByteArray &bytes) {
                write(bytes.getData(), bytes.getLength());
                return *this;
            }

            Logger& operator <<(int32_t value);

            void format(const char *format, ...);

            Logger& arg(const char *msg);

        private:
            uint8_t *pOutputBuffer;
            uint32_t nIndex;
    };
}






#endif












