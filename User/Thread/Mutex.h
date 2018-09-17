#ifndef		__MUTEX_H
#define		__MUTEX_H

#include <rtx_os.h>

class Mutex
{
	public:
		Mutex(const char *name);
	
		inline osStatus_t acquire(void)
		{
			return osMutexAcquire(mId, osWaitForever);
		}
		
		inline osStatus_t release(void)
		{
			return osMutexRelease(mId);
		}
		
	private:
		osMutexId_t mId;
		osMutexAttr_t mAttr;
		uint64_t mMutexCbMem[ (osRtxMutexCbSize + 7) / 8 ];
};



#endif
