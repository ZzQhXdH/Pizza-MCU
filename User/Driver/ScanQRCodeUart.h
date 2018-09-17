#ifndef		__SCAN_QR_CODE_UART_H
#define 	__SCAN_QR_CODE_UART_H

#include "Custom/BaseOutput.h"
#include "Custom/BaseFormat.h"
#include "Thread/MessageQueue.h"
#include "Message/ScanQRCodeMessage.h"

#define QR_MSG_COUNT		10
#define QR_MSG_SIZE			sizeof (ScanQRCodeMessage)
#define QR_QUEUE_SIZE		osRtxMessageQueueMemSize(QR_MSG_COUNT, QR_MSG_SIZE)

class ScanQRCodeUart : public BaseOutput, public BaseFormat, public MessageQueue
{
	public:
		static ScanQRCodeUart& getInstance(void)
		{
			static ScanQRCodeUart INSTANCE;
			return INSTANCE;
		}
		
		virtual void write(const uint8_t *pData, uint32_t size);
		
		void onMessageReceiver(void *buffer, uint32_t size);
		
	private:
		ScanQRCodeUart(void);
	
	private:
		uint8_t mOutputBuffer[100];
		uint64_t mQueueMem[ (QR_QUEUE_SIZE + 7) / 8 ];
		
};



#endif
