#include "Driver/RotationMotor.h"
#include <rtx_os.h>

#define PLUS_LOW()		GPIOB->BRR = 0x01
#define PLUS_HIGH()		GPIOB->BSRR = 0x01

uint32_t RotationMotor::CurrentSteps = 0;

RotationMotor::Error RotationMotor::xToTarget(uint32_t absolute)
{
	if (absolute > CurrentSteps) // 前进
	{
		vSetDir(CW);
		for (uint32_t i = absolute; i > CurrentSteps; i --)
		{
			osDelay(1);
			PLUS_HIGH();
			osDelay(1);
			PLUS_LOW();
			if (isFalut()) {
				return Locked;
			}
		}
		CurrentSteps = absolute;
		return Ok;
	}
	vSetDir(CCW);
	for (uint32_t i = 0; i < CurrentSteps; i ++)
	{
		osDelay(1);
		PLUS_HIGH();
		osDelay(1);
		PLUS_LOW();		
		if (isFalut()) {
			return Locked;
		}
	}
	CurrentSteps = absolute;
	return Ok;
}

/**
 * @brief 
 * PB0 <=> 旋转步进电机脉冲输入
 * PB1 <=> 旋转步进电机方向控制
 * PB5 <=> 旋转步进电机使能,低电平使能
 * PA12 <=> 旋转步进电机故障指示
 * PA4 <=> 旋转零点检测
 */
void RotationMotor::vInit(void)
{
	RCC->APB2ENR |= 0x0C;
	
	GPIOA->CRL &= ~0xF0000;
	GPIOA->CRL |= 0x80000;
	GPIOA->BSRR = 0x10;
	
	GPIOA->CRH &= ~0xF0000;
	GPIOA->CRH |= 0xF0000;
	GPIOA->BSRR = 0x1000;
	
	GPIOB->CRL &= ~0xF000FF;
	GPIOB->CRL |= 0x300033;
}

void RotationMotor::vSetDir(Dir dir)
{
	switch (dir)
	{
		case CW: 
			GPIOB->BRR = 0x02;
			break;
		
		case CCW: 
			GPIOB->BSRR = 0x02;
			break;
	}
}

void RotationMotor::vSetEnable(bool flag)
{
	if (flag) {
		GPIOB->BRR = 0x20;
	} else {
		GPIOB->BSRR = 0x20;
	}
}

