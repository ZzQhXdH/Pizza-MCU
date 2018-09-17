#include "Custom/BaseFormat.h"
#include "myLib/String.h"
#include "myLib/ByteArray.h"
#include <stdarg.h>


uint32_t BaseFormat::formatWrite(const char *format, ...)
{
	using myLib::xStringCopy;
	using myLib::xStringValueOf;
	using myLib::ByteArray;
	
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
			
			case 'B': // ByteArray
				{
					ByteArray *b = va_arg(ap, ByteArray *);
					len = xStringValueOf((char *) pOutputBuffer + index, b->getData(), b->getLength());
					index += len;
				}
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
    return index;	
}








