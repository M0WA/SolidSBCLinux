/*
 * CSolidSBCThread.cpp
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCThread.h"

CSolidSBCThread::CSolidSBCThread(ThreadFunction pFunction, void* param, bool bAutoDelete)
: m_pFunction(pFunction)
, m_pParam(param)
, m_bAutoDelete(bAutoDelete)
, m_bShallEnd(false)
, m_tThread(0)
{
}

CSolidSBCThread::~CSolidSBCThread()
{
	StopThread(true);
}

bool CSolidSBCThread::StartThread(void)
{
	StopThread();

	m_bShallEnd = false;

	PSSBC_THREAD_PARAM pThreadParam = new SSBC_THREAD_PARAM;
	pThreadParam->pbShallEnd = &m_bShallEnd;
	pThreadParam->pParam     = m_pParam;
	pThreadParam->pInstance  = this;

	pthread_attr_init(&m_tThreadAttr);
	pthread_attr_setdetachstate(&m_tThreadAttr, PTHREAD_CREATE_JOINABLE);

	if ( pthread_create( &m_tThread, &m_tThreadAttr, m_pFunction, pThreadParam ) == -1 )
	{
		m_tThread = 0;
		if(m_bAutoDelete)
			delete this;
		return false;
	}
	else
	{
		return true;
	}
}

bool CSolidSBCThread::StopThread(bool bOnlyStop)
{
	m_bShallEnd = true;

	if(m_tThread)
	{
		pthread_join(m_tThread,NULL);
		m_tThread = 0;
		pthread_attr_destroy(&m_tThreadAttr);
	}

	if(!bOnlyStop && m_bAutoDelete)
	{
		delete this;
	}

	m_tThread = 0;
	return false;
}
