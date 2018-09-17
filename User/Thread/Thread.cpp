#include "Thread/Thread.h"

void Thread::ThreadStartFuncation(void *arg)
{
	Thread *task = (Thread *) arg;
	task->run();
	task->mId = nullptr;
	osThreadExit();
}

Thread::Thread(const char *name, uint64_t *stack, uint32_t stackSize, osPriority_t priority)
{
	mAttr.name = name;
	
	mAttr.attr_bits = osThreadDetached;
	mAttr.cb_mem = mCbMemory;
	mAttr.cb_size = osRtxThreadCbSize;
	mAttr.stack_mem = stack;
	mAttr.stack_size = stackSize;
	mAttr.priority = priority;
	mAttr.tz_module = 0;
	mAttr.reserved = 0;
	
	mId = nullptr;
}

void Thread::start(void)
{
	if (mId != nullptr) {
		terminate();
	}
	mId = osThreadNew(ThreadStartFuncation, this, &mAttr);
}

void Thread::terminate(void)
{
	if (mId == nullptr) {
		return;
	}
	osThreadTerminate(mId);
	mId = nullptr;
}





