#ifndef		__THREAD_H
#define		__THREAD_H

#include <rtx_os.h>

class Thread 
{
	public:
		Thread(const char *name, uint64_t *stack, uint32_t stackSize, osPriority_t priority = osPriorityHigh);
		
		void start(void);
	
		void terminate(void);
	
		inline void suspend(void) {
			osThreadSuspend(mId);
		}
		
		inline void resume(void) {
			osThreadResume(mId);
		}
	
	protected:
		virtual void run(void) = 0;
	
	private:
		osThreadId_t mId;
		osThreadAttr_t mAttr;
		uint64_t mCbMemory[ (osRtxThreadCbSize + 7) / 8 ];
	
		static void ThreadStartFuncation(void *arg);
};






#endif
