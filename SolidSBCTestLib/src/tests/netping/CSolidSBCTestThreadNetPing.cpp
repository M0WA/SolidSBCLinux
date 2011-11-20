/*
 * CSolidSBCTestThreadNetPing.cpp
 *
 *  Created on: 13.11.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCTestThreadNetPing.h"
#include "CSolidSBCTestConfigNetPing.h"
#include "CSolidSBCTestResultNetPing.h"

#include "../../../../SolidSBCSDK/src/thread/CSolidSBCThread.h"

void* CSolidSBCTestThreadNetPing::ThreadFunc(void* pParam)
{
	CSolidSBCThread::PSSBC_THREAD_PARAM pThreadParam = reinterpret_cast<CSolidSBCThread::PSSBC_THREAD_PARAM>(pParam);
	CSolidSBCTestConfigNetPing*         pTestConfig  = reinterpret_cast<CSolidSBCTestConfigNetPing*>(pThreadParam->pParam);
	CSolidSBCThread*                    pThread      = reinterpret_cast<CSolidSBCThread*>(pThreadParam->pInstance);
	return 0;
}
