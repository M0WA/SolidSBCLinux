/*
 * CSolidSBCTestThread.h
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTTHREAD_H_
#define CSOLIDSBCTESTTHREAD_H_

#include "../thread/CSolidSBCThread.h"
#include "CSolidSBCTestConfig.h"

class CSolidSBCTestThread : public CSolidSBCThread
{
public:
	CSolidSBCTestThread(CSolidSBCThread::ThreadFunction pThreadFunc, CSolidSBCTestConfig* pTestConfig);
	virtual ~CSolidSBCTestThread();
};

#endif /* CSOLIDSBCTESTTHREAD_H_ */
