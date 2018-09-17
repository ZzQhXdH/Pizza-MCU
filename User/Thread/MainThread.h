#ifndef		__MAIN_THREAD_H
#define		__MAIN_THREAD_H

#include "Thread/Thread.h"
#include "Thread/MessageQueue.h"

#define MAIN_MESSAGE_COUNT			10
#define MAIN_MESSAGE_SIZE			4
#define MAIN_QUEUE_SIZE				osRtxMessageQueueMemSize(MAIN_MESSAGE_COUNT, MAIN_MESSAGE_SIZE)

class MainThread : public Thread, public MessageQueue
{
	public:
		static MainThread &getInstance(void)
		{
			static MainThread task;
			return task;
		}
	
	protected:
		virtual void run(void);
		
	private:
		MainThread(void);
	
	private:
		uint64_t mStack[512 / 8]; 
		uint64_t mMessageQueueMem[ (MAIN_QUEUE_SIZE + 7) / 8 ];
};




#endif
