#ifndef		__BASE_FORMAT_H
#define		__BASE_FORMAT_H

#include <stdint.h>

class BaseFormat
{
	public:
		inline BaseFormat(uint8_t *buffer) : pOutputBuffer(buffer), nIndex(0) {}
		
		virtual void write(const uint8_t *pData, uint32_t size) = 0;
		
		uint32_t formatWrite(const char *format, ...);
		
	private:
		uint8_t *pOutputBuffer;
		uint32_t nIndex;
};






#endif
