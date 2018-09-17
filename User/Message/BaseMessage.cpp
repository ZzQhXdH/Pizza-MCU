#include "Message/BaseMessage.h"



BaseMessage::Error BaseMessage::isChecked(void)
{	
	if (pData[0] != 0xE1) {
		return HeaderError;
	}
	
	if (pData[nSize - 1] != 0xEF) {
		return EndError;
	}
	
	if ((pData[1] != nSize) || (nSize < 5)) {
		return LengthError;
	}
	uint32_t argEnd = nSize - 2;
	uint8_t check = 0;
	for (uint32_t i = 3; i < argEnd; i ++) { check ^= pData[i]; }
	
	if (pData[nSize - 2] != check) {
		return CheckError;
	}
	return Ok;
}






