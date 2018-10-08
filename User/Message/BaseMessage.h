#ifndef		__BASE_MESSAGE_H
#define 	__BASE_MESSAGE_H

#include <stdint.h>
#include "Custom/BaseOutput.h"
#include "Custom/BaseFormat.h"

class BaseMessage
{
	public:
		enum Error {
			Ok = 0x00,
			HeaderError = 0x01,
			EndError = 0x02,
			CheckError = 0x03,
			LengthError = 0x04,
		};
	
	public:
		inline BaseMessage(void *msg, uint32_t size) : pData((uint8_t *) msg), nSize(size) {}	
			
		inline void set(void *msg, uint32_t size) 
		{
			pData = (uint8_t *) msg;
			nSize = size;
		}
		
		inline void setOutput(BaseOutput *out) { pOutput = out; }
		
		inline BaseOutput &getOutput(void) { return *pOutput; }
		
		inline uint8_t getArg(uint32_t index) const // index >= 1
		{
			return pData[index + 2];
		}
		
		inline uint16_t getArg2(uint32_t index) const 
		{
			return (pData[index + 2] << 7)+ pData[index + 3];
		}
		
		inline uint16_t getArg4(uint32_t index) const 
		{
			return (pData[index + 2] << 21) + (pData[index + 3] << 14) +
				   (pData[index + 4] << 7) + pData[index + 5];
		}
		
		inline uint8_t getAction(void) const { return pData[2]; }
		
		inline uint32_t getSize(void) const 
		{
			return nSize;
		}
		
		inline uint8_t *getData(void) const 
		{
			return pData;
		}
		
	protected:
		Error isChecked(void);
		
	protected:
		uint8_t *pData;
		uint32_t nSize;
		BaseOutput *pOutput;
};





#endif
