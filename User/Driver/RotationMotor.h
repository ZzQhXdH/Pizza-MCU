#ifndef		__ROTATION_MOTOR_H
#define		__ROTATION_MOTOR_H

#include "stm32f10x.h"

class RotationMotor
{
	public:
		enum Error {
			Locked = 0x01,
			TimeOut = 0x02,
			Ok = 0x03,
		};
		
		enum Dir {
			CW = 0x01,
			CCW = 0x02,
		};
	
	public:
		static void vInit(void);
		
		static void vSetDir(Dir dir);
	
		static void vSetEnable(bool flag);
	
		static Error xToTarget(uint32_t absolute = 0);
	
		inline static bool isFalut(void) { return 0x00 != (GPIOA->IDR & 0x1000); }
	
	private:
		static uint32_t CurrentSteps;
	
	private:
		RotationMotor(void) {}
};






#endif
