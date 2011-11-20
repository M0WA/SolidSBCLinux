/*
 * CSolidSBCTestThreadNetTCP.cpp
 *
 *  Created on: 13.11.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCTestThreadNetTCP.h"
#include "CSolidSBCTestConfigNetTCP.h"
#include "CSolidSBCTestResultNetTCP.h"

#include "../../../../SolidSBCSDK/src/thread/CSolidSBCThread.h"

void* CSolidSBCTestThreadNetTCP::ThreadFunc(void* pParam)
{
	CSolidSBCThread::PSSBC_THREAD_PARAM pThreadParam = reinterpret_cast<CSolidSBCThread::PSSBC_THREAD_PARAM>(pParam);
	CSolidSBCTestConfigNetTCP*          pTestConfig  = reinterpret_cast<CSolidSBCTestConfigNetTCP*>(pThreadParam->pParam);
	CSolidSBCThread*                    pThread      = reinterpret_cast<CSolidSBCThread*>(pThreadParam->pInstance);
	return 0;
}
