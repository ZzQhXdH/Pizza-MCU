#ifndef			__CURRENT_SENSE_H
#define 		__CURRENT_SENSE_H

#include "stm32f10x.h"

class CurrentSense
{
	public:
		static void vStartCheck(void);
		
		inline static uint16_t xGetValue(void) { return CurrentValue; }
	
	private:
		CurrentSense() {}
			
		static uint16_t CurrentValue;
};





#endif
