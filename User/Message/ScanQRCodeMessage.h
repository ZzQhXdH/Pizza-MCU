#ifndef		__SCAN_QR_CODE_MESSAGE_H
#define		__SCAN_QR_CODE_MESSAGE_H

#include "Message/BaseMessage.h"

class ScanQRCodeMessage : public BaseMessage
{
	public:
		ScanQRCodeMessage(void *msg, uint32_t size) : BaseMessage(msg, size) {}
			
		ScanQRCodeMessage(void) : BaseMessage(nullptr, 0) {}
};





#endif
