#ifndef		__ELEVATOR_MOTOR_H
#define		__ELEVATOR_MOTOR_H

#include <stdint.h>
#include "stm32f10x.h"

class ElevatorMotor
{
	public:
		enum Error {
			TimeOut = 0x01,
			Locked = 0x02,
			Ok = 0x03,
		};
		
		enum Dir {
			Up = 0x01,
			Down = 0x02,
		};
	
	public:
		static void vInit(void);
		
		inline static bool isFault(void) { return 0x00 != (GPIOA->IDR & 0x80); }
		
		static Error xToTarget(uint32_t absolute = 0);
		
		static void vSetDir(Dir dir);
		
		static void vSetEnable(bool flag);
		
	private:
		static uint32_t CurrentSteps;
	
	private:
		ElevatorMotor(void) {}
};


#endif
