#ifndef     __X_STRING_H
#define     __X_STRING_H

#include <stdint.h>

namespace myLib
{
    uint32_t xStringGetLength(const char *cString);

    bool xStringEqual(const char *cString1, const char *cString2);

    uint32_t xStringSubString(const char *sourceString, uint32_t start, uint32_t end, char *subString);

    int32_t xStringIndexOf(const char *sourceString, char c);

    int32_t xStringIndexOf(const char *sourceString, const char *targetString);

    int32_t xStringIndexOfAll(const char *sourceString, const char *targetString);

    uint32_t xStringCopy(const char *sourceString, char *targetString);

    void vStringCopy(const char *sourceString, uint32_t size, char *targetString);

    int32_t xStringSplit(const char *sourceString, const char *targetString, char **out);

    int32_t xStringToInt(const char *sourceString, bool *ret = nullptr);

    uint32_t xStringToHex(const char *sourceString, bool *ret = nullptr);

    uint32_t xStringValueOf(char *targetString, int32_t value, uint8_t base = 10, bool isUpper = false);
	
	uint32_t xStringValueOf(char *targetString, const uint8_t *byteArray, uint32_t size);

    class ConstString
    {
        public:
            inline ConstString(const char *s) : pData(s), nLength( xStringGetLength(s) ) {}
            inline ConstString(const ConstString& s) : pData(s.getData()), nLength(s.getLength()) {}

            inline ConstString& operator=(const ConstString &s)
            {
                pData = s.getData();
                nLength = s.getLength();
                return *this;
            }

            int32_t indexOf(char c) const;

            int32_t indexOf(const char *s) const;

            inline int32_t indexOf(const ConstString &s) const {
                return indexOf(s.getData());
            }

            inline char operator [](uint32_t index) const {
                return pData[index];
            }

            bool operator ==(const ConstString &s) const;

            inline const char *getData() const {
                return pData;
            }

            inline uint32_t getLength() const {
                return nLength;
            }

        private:
            const char *pData;
            uint32_t nLength;
    };
}


#endif
