#ifndef		__BASE_OUTPUT_H
#define		__BASE_OUTPUT_H

#include <stdint.h>

class BaseOutput
{
	public:
		inline BaseOutput(uint8_t *buffer) : pOutputBuffer(buffer), nIndex(0) {}
		
		virtual void write(const uint8_t *pData, uint32_t size) = 0;
			
		inline BaseOutput& setAction(uint8_t action) 
		{
			mAction = action;
			nIndex = 0;
			return *this;
		}
		
		inline BaseOutput& append(uint8_t byte)
		{
			pOutputBuffer[nIndex ++] = byte;
			return *this;
		}
		
		inline void buildAndWrite(void) 
		{
			uint32_t size = build(pOutputBuffer + nIndex);
			write(pOutputBuffer + nIndex, size);
		}
		
		uint32_t build(uint8_t *buildBuffer);
		
	private:
		uint8_t *pOutputBuffer;
		uint32_t nIndex;
		uint8_t mAction;
};


#endif
