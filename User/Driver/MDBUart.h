#ifndef		__MDB_UART_H
#define		__MDB_UART_H

#include "Custom/BaseOutput.h"
#include "Custom/BaseFormat.h"
#include "Thread/MessageQueue.h"
#include "Message/MDBMessage.h"

#define MDB_MSG_COUNT		10
#define MDB_MSG_SIZE		sizeof (MDBMessage)
#define MDB_QUEUE_SIZE		osRtxMessageQueueMemSize(MDB_MSG_COUNT, MDB_MSG_SIZE)

class MDBUart : public BaseOutput, public BaseFormat, public MessageQueue
{
	public:
		static MDBUart &getInstance(void)
		{
			static MDBUart uart;
			return uart;
		}
		
		virtual void write(const uint8_t *pData, uint32_t size) ;
		
		void onMessageReceiver(void *buffer, uint32_t size);
		
	private:
		MDBUart(void);
	
	private:
		uint8_t mOutputBuffer[100];
		uint64_t mQueueBuffer[ (MDB_QUEUE_SIZE + 7) / 8 ]; 
};






#endif
