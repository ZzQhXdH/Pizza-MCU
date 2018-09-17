#include "Driver/ElevatorMotor.h"
#include <rtx_os.h>

#define PLUS_LOW()			GPIOA->BRR = 0x01
#define PLUS_HIGH()			GPIOA->BSRR= 0x01

uint32_t ElevatorMotor::CurrentSteps = 0;

void ElevatorMotor::vSetEnable(bool flag)
{
	if (flag) {
		GPIOA->BSRR = 0x20;
	} else {
		GPIOA->BRR = 0x20;
	}
}

void ElevatorMotor::vSetDir(Dir dir)
{
	switch (dir)
	{
		case Up: 
			GPIOA->BRR = 0x02;
			break;
		
		case Down:
			GPIOA->BSRR = 0x02;
			break;
	}
}

ElevatorMotor::Error ElevatorMotor::xToTarget(uint32_t absolute)
{	
	if (CurrentSteps > absolute)
	{
		vSetDir(Down);
		for (uint32_t i = absolute; i < CurrentSteps; i ++)
		{
			osDelay(1);
			PLUS_LOW();
			osDelay(1);
			PLUS_HIGH();
			if (isFault()) {
				return Locked;
			}
		}
		CurrentSteps = absolute;
		return Ok;
	}
	
	vSetDir(Up);
	for (uint32_t i = absolute; i > CurrentSteps; i --)
	{
		osDelay(1);
		PLUS_LOW();
		osDelay(1);
		PLUS_HIGH();
		if (isFault()) {
			return Locked;
		}		
	}
	CurrentSteps = absolute;
	return Ok;
}

/**
 * @brief 升降步进电机控制器
 * PA0 <=> 升降步进电机脉冲输入
 * PA1 <=> 升降步进电机方向控制 
 * PA5 <=> 升降步进电机使能,低电平有效
 * PA7 <=> 升降步进电机保护输出,高电平表示故障
 */
void ElevatorMotor::vInit(void)
{
	RCC->APB2ENR |= 0x04;
	
	GPIOA->CRL &= ~0xF0F000FF;
	GPIOA->CRL |= 0x80300033;
	GPIOA->BSRR = 0x80;
	vSetEnable(true);
}






