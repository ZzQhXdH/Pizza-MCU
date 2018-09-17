#include "Driver/DS18B20.h"

#define vSetDQ()		GPIOC->BSRR = 0x10
#define vClrDQ()		GPIOC->BRR = 0x10
#define xGetDQ()		(GPIOC->IDR & 0x10)

static void vTimer6Init(void)
{
	RCC->APB1ENR |= 0x10; // Enable Timer6
	
	TIM6->CR1 = 0x00;
	TIM6->CR2 = 0x00;
	TIM6->PSC = 72 - 1;
	TIM6->ARR = 1000 - 1;
	TIM6->CR1 = 0x01;
	TIM6->EGR = 0x01;
}

static void vTimer6Delay(uint32_t us)
{
	TIM6->CNT = 0x00;
	while (TIM6->CNT <= us);
}

/**
 * @brief PC4 <=> DQ
 */
void DS18B20::vInit(void)
{
	RCC->APB2ENR |= 0x10;
	
	GPIOC->CRL &= ~0xF0000;
	GPIOC->CRL |= 0x70000;
	
	vTimer6Init();
}

static bool IsChecked(void)
{
	vClrDQ();
	vTimer6Delay(720);
	vSetDQ();
	uint32_t count = 0;
	do {
		if (!xGetDQ()) { //ºÏ≤‚µΩ¡À¥Ê‘⁄¬ˆ≥Â
			break;
		}
		vTimer6Delay(10);
		count ++;
	} while (count < 50);

	if (count >= 50) {
		return false;
	}
	count = 0;
	do {
		if (xGetDQ()) { // ∂…π˝¥Ê‘⁄¬ˆ≥Â
			break;
		}
		vTimer6Delay(10);
		count ++;
	} while (count > 50);
	
	if (count >= 50) {
		return false;
	}
	
	return true;
}

static bool ReadBit(void)
{
	bool v;
	vClrDQ();
	vTimer6Delay(2);
	vSetDQ();
	vTimer6Delay(12);
	if (xGetDQ()) {
		v = true;
	} else {
		v = false;
	}
	vTimer6Delay(50);
	return v;
}

static void WriteByte(uint8_t data)
{
	for (uint32_t i = 0; i < 8; i ++)
	{
		if (data & 0x01)
		{
			vClrDQ();
			vTimer6Delay(2);
			vSetDQ();
			vTimer6Delay(90);
		}
		else
		{
			vClrDQ();
			vTimer6Delay(90);
			vSetDQ();
			vTimer6Delay(2);
		}
		data >>= 1;
	}
}

static uint8_t ReadByte(void)
{
	uint8_t byte = 0;
	for (uint32_t i = 0; i < 8; i ++)
	{
		byte >>= 1;
		if (ReadBit()) {
			byte |= 0x80;
		}
	}
	return byte;
}

bool DS18B20::xGetValue(uint32_t *pValue)
{
	uint8_t tempL, tempH;
	
	if (!IsChecked()) {
		return false;
	}
	WriteByte(0xCC);
	WriteByte(0xBE);
	tempL = ReadByte();
	tempH = ReadByte();
	*pValue = (tempH << 8) + tempL;
	return true;
}

