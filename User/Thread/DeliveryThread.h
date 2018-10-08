#ifndef		__DELIVERY_THREAD_H
#define		__DELIVERY_THREAD_H

#include "Thread/Thread.h"
#include "Thread/MessageQueue.h"
#include "Message/BaseMessage.h"

#define DELIVERY_MSG_SIZE		sizeof (BaseMessage)
#define DELIVERY_MSG_COUNT		10
#define DELIVERT_MQ_SIZE		osRtxMessageQueueMemSize(DELIVERY_MSG_COUNT, DELIVERY_MSG_SIZE)

class DeliveryThread : public Thread, public MessageQueue
{
	public:
		static DeliveryThread &getInstance(void)
		{
			static DeliveryThread thread;
			return thread;
		}
		
	protected:
		virtual void run(void);
		
	private:
		DeliveryThread(void);
		
	private:
		uint64_t mStack[1024 / 8];
		uint64_t mMessageQueueMem[ (DELIVERT_MQ_SIZE + 7) / 8 ];
};



#endif
