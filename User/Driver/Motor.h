#ifndef		__MOTOR_H
#define		__MOTOR_H

#include "Driver/PositionSwitch.h"
#include <rtx_os.h>

class Motor
{
	public:
		enum Dir {
			CW = 0x01,
			CCW = 0x02,
			Brake = 0x03,
		};
		
		enum Error {
			TimeOut = 0x81, // 超时
			Locked = 0x82, // 堵转
			Ok = 0x83, // OK
		};
	
	public:
		static void vInit(void);
	
	private:
		static void vSetDir(Dir dir = Brake);		
	
		/** 取物门电机控制 **/
		inline static void vEnablePickingDoor(void) { GPIOC->BRR = 0x80; } 
		inline static void vDisablePickingDoor(void) { GPIOC->BSRR = 0x80; }
		
		/** 内推货电机控制 **/
		inline static void vEnableInteriorPush(void) { GPIOC->BRR = 0x100; }
		inline static void vDisableInteriorPush(void) { GPIOC->BSRR = 0x100; }
		
		/** 保温门电机控制 **/
		inline static void vEnableThermalDoor(void) { GPIOC->BRR = 0x200; }
		inline static void vDisableThermalDoor(void) { GPIOD->BSRR = 0x200; } 
		
		/** 外升降电机控制 **/
		inline static void vEnableExternalUpDown(void) { GPIOC->BRR = 0x2000; }
		inline static void vDisableExternalUpDown(void) { GPIOC->BSRR = 0x2000; }
		
		/** 外推货电机控制 **/
		inline static void vEnableExternalPush(void) { GPIOC->BRR = 0x4000; }
		inline static void vDisableExternalPush(void) { GPIOC->BSRR = 0x4000; }
		
	private:
		Motor(void) {}
};


#endif
