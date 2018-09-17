#ifndef		__MESSAGE_QUEUE_H
#define		__MESSAGE_QUEUE_H

#include <rtx_os.h>
#include "Message/BaseMessage.h"

class MessageQueue
{
	public:
		MessageQueue(const char *name, uint64_t *mq_mem, uint32_t msg_count, uint32_t msg_size);
		
		inline osStatus_t post(void *env) 
		{
			return osMessageQueuePut(mId, env, 0, 0);
		}
		
		inline osStatus_t recv(void *env, uint32_t timeOut = osWaitForever) 
		{
			return osMessageQueueGet(mId, env, NULL, timeOut);
		}
	
	private:
		osMessageQueueAttr_t mAttr;
		osMessageQueueId_t mId;
		uint64_t mMqCbMem[ (osRtxMessageQueueCbSize + 7) / 8 ];
};







#endif
