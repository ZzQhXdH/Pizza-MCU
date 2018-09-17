#ifndef		__FLASH_H
#define		__FLASH_H

#include "stm32f10x.h"

#define FLASH_BASE_ADDRESS	0x8000000
#define FLASH_PAGE_SIZE		2048

class Flash
{
	public:
		enum Error {
			Ok = 0x00,
			Busy = 0x01,
			ProgramError = 0x02,
			WriteProtectedError = 0x03,
			TimeOut = 0x04,
		};
	
	public:		
		static Error write(uint32_t address, const void *pData, uint32_t size);
		
		static void read(uint32_t address, void *pData, uint32_t size);
		
};


#endif
