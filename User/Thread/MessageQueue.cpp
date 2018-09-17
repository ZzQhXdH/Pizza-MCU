#include "Thread/MessageQueue.h"


MessageQueue::MessageQueue(const char *name, uint64_t *mq_mem, uint32_t msg_count, uint32_t msg_size)
{
	mAttr.name = name;
	mAttr.attr_bits = 0;
	mAttr.cb_mem = mMqCbMem;
	mAttr.cb_size = osRtxMessageQueueCbSize;
	mAttr.mq_mem = mq_mem;
	mAttr.mq_size = osRtxMessageQueueMemSize(msg_count, msg_size);
	
	mId = osMessageQueueNew(msg_count, msg_size, &mAttr);
}









