#include "Driver/MDBUart.h"
#include "stm32f10x.h"

static uint64_t MDBReceiverBuffer[512 / 8];
static uint64_t MDBReceiverBufferOnce[64 / 8];
static void InitDriver(void);
static void WriteByte(uint8_t byte);

/**
 * @USART1_TX <=> PA9
 * @USART1_RX <=> PA10 <=> DMA1_Channel5
 */
MDBUart::MDBUart(void) :
	BaseOutput(mOutputBuffer),
	BaseFormat(mOutputBuffer),
	MessageQueue("mdb", mQueueBuffer, MDB_MSG_COUNT, MDB_MSG_SIZE)
{
	InitDriver();
}

void MDBUart::write(const uint8_t *pData, uint32_t size)
{
	while (size --)
	{
		WriteByte(*pData ++);
	}
}

void MDBUart::onMessageReceiver(void *buffer, uint32_t size)
{
	MDBMessage msg(buffer, size);
	post(&msg);
}

static void WriteByte(uint8_t byte)
{
	while (0 == (USART1->SR & 0x80));
	USART1->DR = byte;
}

static void InitDriver(void)
{
	RCC->APB2ENR |= 0x04; // Enable GPIOA
	RCC->APB2ENR |= 0x4000; // Enable USART2
	RCC->AHBENR |= 0x01; // Enable DMA1
	
	GPIOA->CRH &= ~0xFF0;
	GPIOA->CRH |= 0x4B0;
	
	USART1->CR1 = 0x00;
	USART1->CR2 = 0x00;
	USART1->CR3 = 0x40;
	USART1->BRR = 72000000 / 9600;
	USART1->CR1 = 0x201C;
	
	DMA1->IFCR = 0xF0000;
	DMA1_Channel5->CCR = 0x00;
	DMA1_Channel5->CMAR = (uint32_t) MDBReceiverBuffer;
	DMA1_Channel5->CPAR = (uint32_t) &USART1->DR;
	DMA1_Channel5->CNDTR = sizeof (MDBReceiverBuffer);
	DMA1_Channel5->CCR = 0xA1;
	
	NVIC_EnableIRQ(USART1_IRQn);
}

static inline void BufferOver(uint32_t index, uint32_t lastIndex)
{
	uint32_t k = 0;
	uint8_t *p1 = (uint8_t *) MDBReceiverBufferOnce;
	uint8_t *p2 = (uint8_t *) MDBReceiverBuffer;
	for (uint32_t i = lastIndex; i < sizeof (MDBReceiverBuffer); i ++, k ++) {
		p1[k] = p2[i];
	}
	for (uint32_t i = 0; i < index; i ++, k ++) {
		p1[k] = p2[i];
	}
	MDBUart::getInstance().onMessageReceiver(p1, k);
}

extern "C" void USART1_IRQHandler(void)
{
	if (0x00 == (USART1->SR & 0x10)) {
		return;
	}
	static uint32_t lastIndex;
	uint32_t index = USART1->DR;
	index = sizeof (MDBReceiverBuffer) - DMA1_Channel5->CNDTR;
	if (index > lastIndex) {
		MDBUart::getInstance().onMessageReceiver(((uint8_t *) MDBReceiverBuffer) + lastIndex, index - lastIndex );
	} else {
		BufferOver(index, lastIndex);
	}
	lastIndex = index;
}



