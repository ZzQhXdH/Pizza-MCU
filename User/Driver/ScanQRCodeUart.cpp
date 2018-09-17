#include "Driver/ScanQRCodeUart.h"
#include "stm32f10x.h"

static uint64_t ScanQRCodeReceiver[512 / 8];
static uint64_t ScanQRCodeMessageOnce[64 / 8];

static void WriteByte(uint8_t byte);
static void InitDriver(void);

ScanQRCodeUart::ScanQRCodeUart(void) :
	BaseOutput(mOutputBuffer),
	BaseFormat(mOutputBuffer),
	MessageQueue("scan", mQueueMem, QR_MSG_COUNT, QR_MSG_SIZE)
{
	InitDriver();
}

void ScanQRCodeUart::write(const uint8_t *pData, uint32_t size)
{
	while (size --)
	{
		WriteByte(*pData ++);
	}
}

void ScanQRCodeUart::onMessageReceiver(void *buffer, uint32_t size)
{
	ScanQRCodeMessage msg(buffer, size);
	post(&msg);
}

static void WriteByte(uint8_t byte)
{
	while (0 == (USART1->SR & 0x80));
	USART3->DR = byte;
}

/**
 * @USART3_TX <=> PB10
 * @USART3_RX <=> PB11 <=> DMA1_Channel3
 */
static void InitDriver(void)
{
	RCC->APB2ENR |= 0x08; // Enable GPIOB
	RCC->APB1ENR |= 0x40000; // Enable USART3
	RCC->AHBENR |= 0x01; // Enable DMA1
	
	GPIOB->CRH &= ~0xFF00;
	GPIOB->CRH |= 0x4B00;
	
	USART3->CR1 = 0x00;
	USART3->CR2 = 0x00;
	USART3->CR3 = 0x40;
	USART3->BRR = 36000000 / 9600;
	USART3->CR1 = 0x201C;
	
	DMA1->IFCR = 0xF00;
	DMA1_Channel3->CCR = 0x00;
	DMA1_Channel3->CMAR = (uint32_t) ScanQRCodeReceiver;
	DMA1_Channel3->CPAR = (uint32_t) &USART3->DR;
	DMA1_Channel3->CNDTR = sizeof (ScanQRCodeReceiver);
	DMA1_Channel3->CCR = 0xA1;
	
	NVIC_EnableIRQ(USART3_IRQn);
}

static inline void BufferOver(uint32_t index, uint32_t lastIndex)
{
	uint32_t k = 0;
	uint8_t *p1 = (uint8_t *) ScanQRCodeMessageOnce;
	uint8_t *p2 = (uint8_t *) ScanQRCodeReceiver;
	for (uint32_t i = lastIndex; i < sizeof (ScanQRCodeReceiver); i ++, k ++) {
		p1[k] = p2[i];
	}
	for (uint32_t i = 0; i < index; i ++, k ++) {
		p1[k] = p2[i];
	}
	ScanQRCodeUart::getInstance().onMessageReceiver(p1, k);
}


extern "C" void USART3_IRQHandler(void)
{
	if (0 == (USART3->SR & 0x10)) {
		return ;
	}
	static uint32_t lastIndex;
	uint32_t index = USART3->DR;
	index = sizeof (ScanQRCodeReceiver) - DMA1_Channel3->CNDTR;
	if (index > lastIndex) {
		ScanQRCodeUart::getInstance().onMessageReceiver(((uint8_t *) ScanQRCodeReceiver) + lastIndex, index - lastIndex );
	} else {
		BufferOver(index, lastIndex);
	}
	lastIndex = index;
}


