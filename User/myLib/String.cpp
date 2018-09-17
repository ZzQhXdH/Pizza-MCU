#include "myLib/String.h"
#include "myLib/Template.h"


namespace myLib
{
    static const char HexListUpper[] = {
        '0', '1', '2', '3',
        '4', '5', '6', '7',
        '8', '9', 'A', 'B',
        'C', 'D', 'E', 'F',
    };

    static const char HexListLower[] = {
        '0', '1', '2', '3',
        '4', '5', '6', '7',
        '8', '9', 'a', 'b',
        'c', 'd', 'e', 'f',
    };

    uint32_t xStringGetLength(const char *cString)
    {
        uint32_t len = 0;
        while (*cString != '\0')
        {
            len ++;
            cString ++;
        }
        return len;
    }

    bool xStringEqual(const char *cString1, const char *cString2)
    {
        while ( *cString1 == *cString2 )
        {
            if (*cString1 == '\0') {
                return true;
            }
            cString1 ++;
            cString2 ++;
        }
        return false;
    }

    uint32_t xStringSubString(const char *sourceString, uint32_t start, uint32_t end, char *subString)
    {
        uint32_t len = 0;
        for (; start < end; start ++)
        {
            subString[len] = sourceString[start];
            len ++;
            start ++;
        }
        return len;
    }

    int32_t xStringIndexOf(const char *sourceString, char c)
    {
        int32_t index = 0;
        char t;
        while ( (t = sourceString[index]) != '\0' )
        {
            if (c == t ) {
                return index;
            }
            index ++;
        }
        return -1;
    }

    int32_t xStringIndexOf(const char *sourceString, const char *targetString)
    {
        const char *source = sourceString;
        for (; *source !='\0'; source ++)
        {
            const char *s = source;
            for (const char *p = targetString; *s == *p; s ++, p ++)
            {
                if (*(p + 1) =='\0')
                {
                    return source - sourceString;
                }
            }
        }
        return -1;
    }

    int32_t xStringIndexOfAll(const char *sourceString, const char *targetString)
    {
        const char *source = sourceString;
        for (; *source !='\0'; source ++)
        {
            const char *s = source;
            for (const char *p = targetString; *s == *p; s ++, p ++)
            {
                if (*(p + 1) == '\0')
                {
                    return ((source - sourceString) << 16) + (s - sourceString + 1);
                }
            }
        }
        return -1;
    }

    uint32_t xStringCopy(const char *sourceString, char *targetString)
    {
        uint32_t len = 0;
        while (*sourceString != '\0')
        {
            *targetString = *sourceString;
            targetString ++;
            sourceString ++;
            len ++;
        }
        *targetString = '\0';
        return len;
    }

    void xStringCopy(const char *sourceString, uint32_t size, char *targetString)
    {
        for (uint32_t i = 0; i < size; i ++)
        {
            *targetString = *sourceString;
            targetString ++;
            sourceString ++;
        }
        *targetString = '\0';
    }

    int32_t xStringSplit(const char *sourceString, const char *targetString, char **out)
    {
        int32_t index;
        int32_t count = 0;
        int32_t start = 0;
        int32_t end = 0;

        while (*sourceString != '\0')
        {
            index = xStringIndexOfAll(sourceString, targetString);
            if (index < 0) {
                xStringCopy(sourceString, *out);
                return count + 1;
            }
            start = index >> 16;
            end = index & 0xFFFF;
            xStringCopy(sourceString, start, *out);
            out ++;
            count ++;
            sourceString += end;
        }
        return count;
    }

    int32_t xStringToInt(const char *sourceString, bool *ret)
    {
        if (ret == nullptr)
        {
            int32_t value = 0;
            bool negative = false;
            if (*sourceString == '-') {
                negative = true;
                sourceString ++;
            }
            char c;
            while ( (c = *sourceString) != '\0')
            {
                value *= 10;
                value += c - '0';
                sourceString ++;
            }
            if (negative) {
                return -value;
            } else {
                return value;
            }
        }

        char c;
        int32_t value = 0;
        bool negative = false;
        if (*sourceString == '-') {
            negative = true;
            sourceString ++;
        }

        while ( (c = *sourceString) != '\0' )
        {
            if ( (c < '0') || (c > '9') ) {
                *ret = false;
                return value;
            }
            value *= 10;
            value += c - '0';
            sourceString ++;
        }
        *ret = true;
        if (negative) {
            return -value;
        } else {
            return value;
        }
    }

    uint32_t xStringToHex(const char *sourceString, bool *ret)
    {
        if (ret == nullptr)
        {
            uint32_t value = 0;
            char c;
            while ( (c = *sourceString) != '\0' )
            {
                value <<= 4;
                if ( (c >= '0') && (c <= '9') ) {
                    value += c - '0';
                } else if ( (c >= 'a') && (c <= 'z') ) {
                    value += c - 'a' + 0x0a;
                } else if ( (c >= 'A') && (c <= 'Z') ) {
                    value += c - 'A' + 0x0A;
                }
                sourceString ++;
            }
            return value;
        }

        uint32_t value = 0;
        char c;
        while ( (c = *sourceString) != '\0' )
        {
            value <<= 4;
            if ( (c >= '0') && (c <= '9') ) {
                value += c - '0';
            } else if ( (c >= 'a') && (c <= 'z') ) {
                value += c - 'a' + 0x0a;
            } else if ( (c >= 'A') && (c <= 'Z') ) {
                value += c - 'A' + 0x0A;
            } else {
                *ret = false;
                return value;
            }
            sourceString ++;
        }
        *ret = true;
        return value;
    }

    uint32_t xStringValueOf(char *targetString, int32_t value, uint8_t base, bool isUpper)
    {
        uint32_t length = 1;
        int32_t v = value;
        bool negate = false;
        const char *p;

        while ((v /= base) != 0)
        {
            length ++;
        }

        if (value < 0)
        {
            negate = true;
            *targetString = '-';
            targetString ++;
            value = -value;
        }

        if (isUpper) {
            p = HexListUpper;
        } else {
            p = HexListLower;
        }

        for (uint32_t i = 0; i < length; i ++)
        {
            targetString[length - 1 - i] = p[ value % base ];
            value /= base;
        }

        targetString[length] = '\0';

        if (negate) {
            return length + 1;
        } else {
            return length;
        }
    }
	
	uint32_t xStringValueOf(char *targetString, const uint8_t *byteArray, uint32_t size)
	{
		uint32_t len = 0;
		for (uint32_t i = 0; i < size; i ++)
		{
			len = xStringValueOf(targetString, (int32_t) byteArray[i], 16, true);
			targetString[len ++] = ' ';
			targetString += len;
		}
		return len;
	}

    int32_t ConstString::indexOf(char c) const
    {
        for (uint32_t i = 0; i < nLength; i ++)
        {
            if (c == pData[i]) {
                return i;
            }
        }
        return -1;
    }

    int32_t ConstString::indexOf(const char *s) const
    {
        for (uint32_t i = 0; i < nLength; i ++)
        {
            for (const char *p = s; pData[i] == *p; i ++, p ++)
            {
                if (*(p + 1) == '\0')
                {
                    return i;
                }
            }
        }
        return -1;
    }

    bool ConstString::operator ==(const ConstString &s) const
    {
        if (pData == s.getData()) {
            return true;
        }

        if (nLength != s.getLength()) {
            return false;
        }

        for (uint32_t i = 0; i < nLength; i ++)
        {
            if (pData[i] != s[i]) {
                return false;
            }
        }
        return true;
    }

}









