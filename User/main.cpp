#include "Thread/MainThread.h"




int main(void)
{
	osKernelInitialize();
	MainThread::getInstance().start();
	osKernelStart();
}

