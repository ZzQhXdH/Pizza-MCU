#include "Thread/Mutex.h"


Mutex::Mutex(const char *name)
{
	mAttr.name = name;
	mAttr.attr_bits = osMutexRobust;
	mAttr.cb_mem = mMutexCbMem;
	mAttr.cb_size = osRtxMutexCbSize;
	
	mId = osMutexNew(&mAttr);
}








