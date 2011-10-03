/*
 * CSolidSBCThread.h
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTHREAD_H_
#define CSOLIDSBCTHREAD_H_

#include <pthread.h>

typedef struct {
	bool* pbShallEnd;
	void* pParam;
} _SSBC_THREAD_PARAM, *_PSSBC_THREAD_PARAM;

class CSolidSBCThread
{
public:
	typedef void* (*ThreadFunction)(void*);

	CSolidSBCThread(ThreadFunction pFunction, void* param, bool bAutoDelete = true);
	virtual ~CSolidSBCThread();

	bool StartThread(void);
	bool StopThread(bool bOnlyStop = true);

private:
	ThreadFunction  m_pFunction;
	void*           m_pParam;
	bool            m_bAutoDelete;
	bool   			m_bShallEnd;

	pthread_t 	    m_tThread;
	pthread_attr_t  m_tThreadAttr;
};

#endif /* CSOLIDSBCTHREAD_H_ */
