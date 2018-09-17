#ifndef		__BASE_MESSAGE_H
#define 	__BASE_MESSAGE_H

#include <stdint.h>

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
};





#endif
