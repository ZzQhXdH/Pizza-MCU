#include "myLib/Logger.h"
#include "myLib/String.h"

#include <stdarg.h>


namespace myLib
{
    Logger::Logger(uint8_t *buffer) : pOutputBuffer(buffer)
    {

    }


    Logger& Logger::operator <<(int32_t value)
    {
        uint32_t len = xStringValueOf((char *) pOutputBuffer, value);
        write(pOutputBuffer, len);
        return *this;
    }

    void Logger::format(const char *format, ...)
    {
        va_list ap;
        uint32_t index = 0;
        va_start(ap, format);
        char c;
        while ( (c = *format) != '\0' )
        {
            if (c != '%')
            {
                pOutputBuffer[index] = c;
                format ++;
                index ++;
                continue;
            }
            c = *(format + 1);
            uint32_t len;
            switch (c)
            {
                case 'd':
                    len = xStringValueOf((char *) pOutputBuffer + index, va_arg(ap, int32_t), 10, false);
                    index += len;
                    break;

                case 'f':
                    break;

                case 'X':
                    len = xStringValueOf((char *) pOutputBuffer + index, va_arg(ap, int32_t), 16, true);
                    index += len;
                    break;

                case 's':
                    len = xStringCopy(va_arg(ap, const char *), (char *) pOutputBuffer + index);
                    index += len;
                    break;

                case 'x':
                    len = xStringValueOf((char *) pOutputBuffer + index, va_arg(ap, int32_t), 16, false);
                    index += len;
                    break;
            }
            format += 2;
        }
        write((const uint8_t *) pOutputBuffer, index);
        return;
    }
}











