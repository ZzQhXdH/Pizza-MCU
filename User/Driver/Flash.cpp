#include "Driver/Flash.h"
#include "Thread/Thread.h"

#define FLASH_KEY1               0X45670123
#define FLASH_KEY2               0XCDEF89AB

#define UnLock()				FLASH->KEYR = FLASH_KEY1;\
								FLASH->KEYR = FLASH_KEY2
#define Lock()					FLASH->CR |= 1 << 7

#define PageMinAddress(a)		(a & (~0x7FF))
#define IsMinAddress(a)			((a & 0x7FF) == 0x00)
#define PageNexMinAddress(a)	(IsMinAddress(a) ? (a + 0x800) : ((a + 0x7FF) & (~0x7FF)) )

static uint16_t FlashPageBuffer[1024]; // 2kByte

static inline Flash::Error getStatus(void)
{
	uint32_t ret = FLASH->SR;
	if (ret & (1 << 0)) return Flash::Busy; // 忙
	else if (ret & (1 << 2)) return Flash::ProgramError; // 编程错误
	else if (ret & (1 << 4)) return Flash::WriteProtectedError; // 写保护错误
	return Flash::Ok;
}

static Flash::Error WaitDone(uint16_t timeOut)
{
	Flash::Error ret;
	do {
		ret = getStatus();
		if (ret != 1) break;
		osDelay(1);
		timeOut --;
	} while (timeOut > 0);

	if (timeOut <= 0) ret = Flash::TimeOut;
	
	return ret;
}

static Flash::Error WriteHalfWord(uint32_t address, uint16_t data)
{
	Flash::Error e = WaitDone(0xFF);
	if (e == Flash::Ok)
	{
		FLASH->CR |= 1 << 0; // 编程使能
		*((volatile uint16_t *) address) = data;
		e = WaitDone(0xFF); // 等待操作完成
		if (e != Flash::Busy)
		{
			FLASH->CR &= ~(1 << 0);
		}
	}
	return e;
}

static Flash::Error WriteBuffer(uint32_t pageMin)
{
	Flash::Error e;
	for (uint16_t i = 0; i < 1024; i ++)
	{
		e = WriteHalfWord(pageMin, FlashPageBuffer[i]);
		if (e != Flash::Ok) {
			return e;
		}
		pageMin += 2;
	}
	return e;
}

static void ReadBuffer(uint32_t pageMin)
{
	for (uint16_t i = 0; i < 1024; i ++)
	{
		FlashPageBuffer[i] = *((volatile uint16_t *) (pageMin + i * 2));
	}
}

static void Copy(uint16_t offset, const void *pData, uint16_t count)
{
	const uint16_t *p = (const uint16_t *) pData;
	for (uint16_t i = 0; i < count; i ++)
	{
		FlashPageBuffer[offset] = *p;
		p ++;
		offset ++;
	}
}

static Flash::Error EarsePage(uint32_t address)
{
	Flash::Error ret = WaitDone(0x5FFF); 
	if (ret == 0x00)
	{
		FLASH->CR |= 1 << 1;
		FLASH->AR = address;
		FLASH->CR |= 1 << 6;
		ret = WaitDone(0x5FFF);
		if (ret != Flash::Busy)
		{
			FLASH->CR &= ~(1 << 1);
		}
	}
	return ret;
}

static Flash::Error WritePage(uint32_t address, const uint16_t *pData, uint16_t count)
{
	uint32_t pageMinAddr = PageMinAddress(address); // 获取当前扇区的最小地址
	uint32_t offset = address - pageMinAddr; // 数据偏移地址
	ReadBuffer(pageMinAddr); // 把扇区数据线保存至缓冲区
	Copy(offset / 2, pData, count); // 将数据拷贝至缓冲区
	Flash::Error e = EarsePage(address);
	if (e != Flash::Ok) {
		return e;
	}
	e = WriteBuffer(pageMinAddr); // 将缓冲区的数据写入FLASH
	return e;
}

void Flash::read(uint32_t address, void *pData, uint32_t size)
{
	uint16_t *p = (uint16_t *) pData;
	uint32_t count = size / 2;
	for (uint32_t i = 0; i < count; i ++)
	{
		*p = *((volatile uint16_t *) address);
		address += 2;
		p ++;
	}
}

Flash::Error Flash::write(uint32_t address, const void *pData, uint32_t size)
{
	uint16_t pageCount = size / FLASH_PAGE_SIZE;
	uint16_t pageMargin = size % FLASH_PAGE_SIZE;
	Flash::Error e;
	const uint16_t *p = (const uint16_t *) pData;
	for (uint16_t i = 0; i < pageCount; i ++)
	{
		e = WritePage(address, p, 1024);
		if (e != Ok) {
			return e;
		}
		address += FLASH_PAGE_SIZE;
		p += 1024;
	}
	if (pageMargin != 0) {
		e = WritePage(address, p, pageMargin / 2);
	}
	return e;
}







