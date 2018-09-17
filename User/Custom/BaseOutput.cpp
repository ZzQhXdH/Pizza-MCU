#include "Custom/BaseOutput.h"



uint32_t BaseOutput::build(uint8_t *buildBuffer)
{
	buildBuffer[0] = 0xE1;
	buildBuffer[1] = nIndex + 5;
	buildBuffer[2] = mAction;
	uint8_t check = 0;
	for (uint32_t i = 0; i < nIndex; i ++) {
		buildBuffer[3 + i] = pOutputBuffer[i];
		check ^= pOutputBuffer[i];
	}
	buildBuffer[3 + nIndex] = check;
	buildBuffer[4 + nIndex] = 0xEF;
	return nIndex + 5;
}


