#include "Driver/Motor.h"


/**
 * @brief 
 * PC11, PC12 电机正反转控制 
 * PC7 <=> 取物门电机
 * PC8 <=> 内推货电机
 * PC9 <=> 保温门电机
 * PC13 <=> 外升降直流电机
 * PC14 <=> 外推货直流电机 
 */
void Motor::vInit(void)
{
	RCC->APB2ENR |= 0x10;
	
	GPIOC->CRH &= ~0xFF000;
	GPIOC->CRH |= 0x33000;
	vSetDir();
	
	GPIOC->CRL &= ~0xF0000000;
	GPIOC->CRL |= 0x30000000;
	
	GPIOC->CRH &= ~0xFF000FF;
	GPIOC->CRH |= 0x3300033;
}

void Motor::vSetDir(Dir dir)
{
	switch (dir)
	{
		case CW:
			GPIOC->BRR = 0x800;
			GPIOC->BSRR = 0x1000;
			break;
		
		case CCW:
			GPIOC->BRR = 0x1000;
			GPIOC->BSRR = 0x800;
			break;
		
		case Brake:
			GPIOC->BSRR = 0x1800;
			break;
	}
}





