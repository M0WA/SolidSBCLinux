/*
 * CSolidSBCTestThreadMemory.cpp
 *
 *  Created on: 08.10.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCTestThreadMemory.h"
#include "CSolidSBCTestConfigMemory.h"

#include "../../../../SolidSBCSDK/src/thread/CSolidSBCThread.h"
#include "../../../../SolidSBCSDK/src/debug/CSolidSBCPerformanceCounter.h"

#include "../../interface/CSolidSBCTestManagerImpl.h"
#include "CSolidSBCTestResultMemory.h"

#include "string.h"

//TODO: disabling optimizing
//#pragma optimize( "", off )

CSolidSBCTestThreadMemory::CSolidSBCTestThreadMemory()
{
}

CSolidSBCTestThreadMemory::~CSolidSBCTestThreadMemory()
{
}

void* CSolidSBCTestThreadMemory::ThreadFunc(void* pParam)
{
	CSolidSBCThread::PSSBC_THREAD_PARAM pThreadParam = reinterpret_cast<CSolidSBCThread::PSSBC_THREAD_PARAM>(pParam);
	CSolidSBCTestConfigMemory*          pTestConfig  = reinterpret_cast<CSolidSBCTestConfigMemory*>(pThreadParam->pParam);

	if(pTestConfig->GetRandomize())
	{
		unsigned int nMaxMemSize = pTestConfig->GetMaxMem();
		unsigned int nMinMemSize = pTestConfig->GetMinMem();
		unsigned int nDiff = nMaxMemSize - nMinMemSize;
		unsigned int number, nRandomNumber;

		while ( 1 )
		{
			rand_r( &number );
			nRandomNumber =  number % (nDiff + 1);
			nRandomNumber += nMinMemSize;

			CSolidSBCPerformanceCounter cMallocZeroCnt;
			unsigned long ulMallocZeroBytes = (unsigned long)nRandomNumber;
			cMallocZeroCnt.Start();
			char* pMem = new char[ulMallocZeroBytes];
			memset(pMem,0x00,ulMallocZeroBytes);
			double dMallocZeroDuration = cMallocZeroCnt.Stop();

			//send result
			//TODO: !!!!!!!!!!!!!!! limit msg/seconds !!!!!!!!!!!!!!!!
			if ( pTestConfig->GetTransmitData() )
			{
				CSolidSBCTestResultMemory* pMemResult = new CSolidSBCTestResultMemory();
				pMemResult->SetByteCount(ulMallocZeroBytes);
				pMemResult->SetMallocZeroDuration(dMallocZeroDuration);
				(CSolidSBCTestManagerImpl::GetInstance())->AddResult(pMemResult);
			}

			rand_r( &number );
			nRandomNumber =  number % (5000 + 1);

			//check every second if should exit
			double dSeconds = (double)nRandomNumber / 1000.0f;
			unsigned long  dwMilliSeconds = ((unsigned long)dSeconds) % (1000 + 1);
			for (unsigned long i = 0; i < (unsigned long)dSeconds; i++)
			{
				if ( pThreadParam->pInstance->ShallEnd() )
					break;
				usleep(970 * 1000);
			}
			usleep(dwMilliSeconds * 1000);
			delete pMem;

			if ( pThreadParam->pInstance->ShallEnd() )
				break;
		}
	}
	else
	{
		unsigned int nMaxMemSize = pTestConfig->GetMaxMem();
		char* pMem = new char[nMaxMemSize];

		while( !pThreadParam->pInstance->ShallEnd() )
		{
			memset(pMem,0x00,nMaxMemSize);
			usleep(100 * 1000);
		}

		delete [] pMem;
	}
	return 0;
}

//#pragma optimize( "", on )
