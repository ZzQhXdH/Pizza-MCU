#include "Thread/DeliveryThread.h"




DeliveryThread::DeliveryThread(void) :
	Thread("delivery", mStack, sizeof(mStack), osPriorityHigh3),
	MessageQueue("delivery", mMessageQueueMem, DELIVERY_MSG_COUNT, DELIVERY_MSG_SIZE)
{
	
}

void DeliveryThread::run(void)
{
	
}





