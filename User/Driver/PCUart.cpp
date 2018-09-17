#include "Driver/PCUart.h"
#include "stm32f10x.h"

static void InitDriver(void);
static void WriteByte(uint8_t byte);

static uint64_t PCReceiverBuffer[512 / 8];
static uint64_t PCReceiverBufferOnce[64 / 8];

PCUart::PCUart(void) :
	BaseFormat(mOutputBuffer),
	BaseOutput(mOutputBuffer),
	MessageQueue("pc", mMessageQueueBuffer, PC_MSG_COUNT, PC_MSG_SIZE)
{
	InitDriver();
}

void PCUart::write(const uint8_t *buffer, uint32_t size)
{
	while (size --)
	{
		WriteByte(*buffer ++);
	}
}

void PCUart::onMessageReceiver(uint8_t *buffer, uint32_t size)
{
	PCMessage msg(buffer, size);
	post(&msg);
}

/*****************************************************Driver*********************************************************/
/**
 * @USART2_TX <=> PA2 
 * @USART2_RX <=> PA3 <=> DMA1_Channel6
 */
static void InitDriver(void)
{
	RCC->APB2ENR |= 0x04; // Enable GpioA
	RCC->APB1ENR |= 0x20000; // Enable USART2
	
	GPIOA->CRL &= ~0xFF00;
	GPIOA->CRL |= 0x4B00;
	
	USART2->CR1 = 0x00;
	USART2->CR2 = 0x00;
	USART2->CR3 = 0x40;
	USART2->BRR = 36000000 / 9600;
	USART2->CR1 = 0x201C;
	
	RCC->AHBENR |= 0x01; // Enable DMA1
	DMA1->IFCR = 0xF00000;
	DMA1_Channel6->CCR = 0x00;
	DMA1_Channel6->CMAR = (uint32_t) &PCReceiverBuffer;
	DMA1_Channel6->CNDTR = sizeof (PCReceiverBuffer);
	DMA1_Channel6->CPAR = (uint32_t) &USART2->DR;
	DMA1_Channel6->CCR = 0xA1;
	
	NVIC_EnableIRQ(USART2_IRQn); // 开启中断
}

static void WriteByte(uint8_t byte)
{
	while (0 == (USART2->SR & 0x80));
	USART2->DR = byte;
}

static inline void BufferOver(uint32_t index, uint32_t lastIndex)
{
	uint32_t k = 0;
	uint8_t *p1 = (uint8_t *) PCReceiverBufferOnce;
	uint8_t *p2 = (uint8_t *) PCReceiverBuffer;
	for (uint32_t i = lastIndex; i < sizeof (PCReceiverBuffer); i ++, k ++) {
		p1[k] = p2[i];
	}
	for (uint32_t i = 0; i < index; i ++, k ++) {
		p1[k] = p2[i];
	}
	PCUart::getInstance().onMessageReceiver(p1, k);
}

extern "C" void USART2_IRQHandler(void)
{
	if (0x00 == (USART2->SR & 0x10)) {
		return;
	}
	static uint32_t lastIndex;
	uint32_t index = USART2->DR;
	index = sizeof (PCReceiverBuffer) - DMA1_Channel6->CNDTR;
	if (index > lastIndex) {
		PCUart::getInstance().onMessageReceiver(((uint8_t *) PCReceiverBuffer) + lastIndex, index - lastIndex );
	} else {
		BufferOver(index, lastIndex);
	}
	lastIndex = index;
}

