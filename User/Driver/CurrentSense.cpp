#include "Driver/CurrentSense.h"


uint16_t CurrentSense::CurrentValue = 0;

/**
 * @brief
 * PC5 <=> ADC1_IN5 <=> DMA1_Channel1
 */
void CurrentSense::vStartCheck(void)
{
	RCC->APB2ENR |= 0x10; // GPIOC Enable
	RCC->APB2ENR |= 0x200; // Enable ADC1
	RCC->AHBENR |= 0x01; // Enable DMA1
	
	GPIOC->CRL &= ~0xF00000;

	RCC->CFGR &= ~(0x03 << 14);
	RCC->CFGR |= (0x02 << 14);
	
	ADC1->CR1 = 0x00;
	ADC1->CR2 = (0x07 << 17) + (0x01 << 20) + 0x02 + 0x8;
	ADC1->SQR1 = 0x00;
	ADC1->SMPR2 |= (7 << 15);
	ADC1->CR2 |= 0x01 + 0x08;
	while (ADC1->CR2 & 0x08);
	ADC1->CR2 |= 0x04;
	while (ADC1->CR2 & 0x04);
	
	DMA1->IFCR = 0x0F;
	DMA1_Channel1->CCR = 0x00;
	DMA1_Channel1->CMAR = (uint32_t) &CurrentValue;
	DMA1_Channel1->CPAR = (uint32_t) &ADC1->DR;
	DMA1_Channel1->CNDTR = 1;
	DMA1_Channel1->CCR = 0x0521;
	
	ADC1->SQR3 = 0x05;
	ADC1->CR2 = 0x01 << 22;
}










