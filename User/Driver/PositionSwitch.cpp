#include "Driver/PositionSwitch.h"
#include "stm32f10x.h"

/**
 * @brief 
 * PL <=> PB7
 * SCK <=> PB8
 * MISO <=> PB9
 *
 * 旋转步进电机零点 <=> PA4 0(非零点), 1(零点)
 * 内推货槽型开关 <=> PA6 0(无遮挡), 1(有遮挡)
 * 升降步进电机保护输出 <=> PA7 0(正常)
 * 光栅防夹手 <=> PA8 0(正常) 1(检测到物品)
 * 48V检测 <=> PB13 0(无48V) 1(有48V)
 * 检货红外接收 <=> PC0 0(无货) 1(有货)
 * 微波泄露检测 <=> PC2 0(有微波泄露) 1(无微波泄露)
 * 取货电机槽型开关 <=> PC3 0(未到推货托盘) 1(已经到了推货托盘)
 */
void PositionSwitch::vInit(void)
{
	RCC->APB2ENR |= 0x08 + 0x04 + 0x10; // Enable GPIOA, GPIOB, GPIOC
	
	GPIOB->CRL &= ~0xF0000000;
	GPIOB->CRL |= 0x30000000;
	GPIOB->CRH &= ~0xFF;
	GPIOB->CRH |= 0x83;
	GPIOB->ODR |= 0x200;
	
	GPIOA->CRL &= ~0xFF0F0000;
	GPIOA->CRL |= 0x88080000;
	GPIOA->CRH &= ~0x0F;
	GPIOA->CRH |= 0x08;
	GPIOA->BSRR = 0x1D0;
	
	GPIOB->CRH &= ~0xF00000;
	GPIOB->CRH |= 0x800000;
	GPIOB->BSRR = 0x2000;

	GPIOC->CRL &= ~0xFF0F;
	GPIOC->CRL |= 0x8808;
	GPIOC->BSRR = 0x0D;
}

#define PL_LOW()		GPIOB->BRR = 0x80
#define PL_HIGH()		GPIOB->BSRR = 0x80

#define SCK_LOW()		GPIOB->BRR = 0x100
#define SCK_HIGH()		GPIOB->BSRR = 0x100

#define MISO_READ()		(GPIOB->IDR & 0x200)

uint32_t PositionSwitch::xGetValue(void)
{
	uint32_t value = 0;
	
	PL_LOW();
	PL_HIGH();
	if (MISO_READ()) {
		value ++;
	}
	for (uint32_t i = 0; i < 23; i ++)
	{
		SCK_HIGH();
		value <<= 1;
		if (MISO_READ()) {
			value ++;
		}
		SCK_LOW();
	}
	return value;
}







