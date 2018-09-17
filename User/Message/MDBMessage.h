#ifndef		__MDB_MESSAGE_H
#define		__MDB_MESSAGE_H


#include "Message/BaseMessage.h"

class MDBMessage : public BaseMessage
{
	public:
		MDBMessage(void *msg, uint32_t size) : BaseMessage(msg, size) {}
		
		MDBMessage(void) : BaseMessage(nullptr, 0) {}
};



#endif
