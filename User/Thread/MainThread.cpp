#include "Thread/MainThread.h"
#include "Driver/PCUart.h"
#include "Driver/MDBUart.h"
#include "Driver/ScanQRCodeUart.h"

MainThread::MainThread(void) : 
	Thread("main", mStack, sizeof (mStack)),
	MessageQueue("main", mMessageQueueMem, MAIN_MESSAGE_COUNT, MAIN_MESSAGE_SIZE)
{
	
}

void MainThread::run(void)
{
	PCUart &pc = PCUart::getInstance();
	MDBUart mdb = MDBUart::getInstance();
	ScanQRCodeUart qr = ScanQRCodeUart::getInstance();
	
	PCMessage pc_msg;
	MDBMessage mdb_msg;
	ScanQRCodeMessage scan_msg;
	osStatus_t ret;

	while (true)
	{
		ret = pc.recv(&pc_msg, 100);
		if (ret == osOK) 
		{
			pc.write(pc_msg.getData(), pc_msg.getSize());
		}
		
		ret = mdb.recv(&mdb_msg, 100);
		if (ret == osOK)
		{
			mdb.write(mdb_msg.getData(), mdb_msg.getSize());
		}
		
		ret = qr.recv(&scan_msg, 100);
		if (ret == osOK)
		{
			qr.write(scan_msg.getData(), scan_msg.getSize());
		}
	}
}






