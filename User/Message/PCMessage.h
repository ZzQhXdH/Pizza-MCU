#ifndef		__PC_MESSAGE_H
#define		__PC_MESSAGE_H


#include "Message/BaseMessage.h"
#include <stdio.h>

class PCMessage : public BaseMessage
{
	public:
		inline PCMessage(void) : BaseMessage(NULL, 0) {}
		
		inline PCMessage(void *msg, uint32_t size) : BaseMessage(msg, size) {}	
		
		inline PCMessage(const PCMessage &msg) : BaseMessage(msg.getData(), msg.getSize()) {}
			
		inline PCMessage& operator =(const PCMessage &msg) 
		{
			pData = msg.getData();
			nSize = msg.getSize();
			return *this;
		}
	
};





#endif
