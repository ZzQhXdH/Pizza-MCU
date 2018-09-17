#ifndef		__DS18B20_H
#define		__DS18B20_H

#include "stm32f10x.h"
#include <rtx_os.h>

class DS18B20
{
	public:
		enum Error {
			Ok = 0x00,
			TimeOut = 0x01,
		};
	
	public:
		static void vInit(void);
		
		static bool xGetValue(uint32_t *pValue);
};




#endif
