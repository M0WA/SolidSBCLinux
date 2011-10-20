/*
 * CSolidSBCTestThreadHarddrive.h
 *
 *  Created on: 20.10.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTTHREADHARDDRIVE_H_
#define CSOLIDSBCTESTTHREADHARDDRIVE_H_

class CSolidSBCTestThreadHarddrive
{
public:
	CSolidSBCTestThreadHarddrive();
	virtual ~CSolidSBCTestThreadHarddrive();

	static void* ThreadFunc(void*);

private:
	static void* ReaderThread(void* pParam);
	static void* WriterThread(void* pParam);
};

#endif /* CSOLIDSBCTESTTHREADHARDDRIVE_H_ */
