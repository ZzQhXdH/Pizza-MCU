#ifndef		__PC_UART_H
#define		__PC_UART_H

#include "Custom/BaseFormat.h"
#include "Custom/BaseOutput.h"
#include "Message/PCMessage.h"
#include "Thread/MessageQueue.h"

#define PC_MSG_COUNT	10
#define PC_MSG_SIZE		sizeof (PCMessage)
#define PC_QUEUE_SIZE	osRtxMessageQueueMemSize(PC_MSG_COUNT, PC_MSG_SIZE)

class PCUart : public BaseFormat, public BaseOutput, public MessageQueue
{
	public:
		static PCUart& getInstance(void)
		{
			static PCUart uart;
			return uart;
		}
		
		virtual void write(const uint8_t *buffer, uint32_t size);
		
		inline osStatus_t recv(PCMessage *msg, uint32_t timeOut = osWaitForever) { return MessageQueue::recv(msg, timeOut); }
		
		void onMessageReceiver(uint8_t *buffer, uint32_t size);
		
	private:
		PCUart(void);
		
	private:
		uint8_t mOutputBuffer[100];
		uint64_t mMessageQueueBuffer[ (PC_QUEUE_SIZE + 7) / 8 ];
};



#endif
