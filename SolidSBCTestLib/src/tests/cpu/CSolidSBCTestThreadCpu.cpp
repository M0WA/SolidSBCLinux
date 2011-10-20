/*
 * CSolidSBCTestThreadCpu.cpp
 *
 *  Created on: 20.10.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCTestThreadCpu.h"
#include "CSolidSBCTestConfigCpu.h"
#include "../../../../SolidSBCSDK/src/thread/CSolidSBCThread.h"


#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>


//TODO: disable optimizations
//#pragma optimize( "", off )

long timevaldiff(const struct timeval& starttime, const struct timeval& finishtime)
{
  long msec;
  msec =(finishtime.tv_sec-starttime.tv_sec)  *1000.0f;
  msec+=(finishtime.tv_usec-starttime.tv_usec)/1000.0f;
  return msec;
}

CSolidSBCTestThreadCpu::CSolidSBCTestThreadCpu()
{
}

CSolidSBCTestThreadCpu::~CSolidSBCTestThreadCpu()
{
}

void* CSolidSBCTestThreadCpu::ThreadFunc(void* pParam)
{
	CSolidSBCThread::PSSBC_THREAD_PARAM pThreadParam = reinterpret_cast<CSolidSBCThread::PSSBC_THREAD_PARAM>(pParam);
	CSolidSBCTestConfigCpu*             pTestConfig  = reinterpret_cast<CSolidSBCTestConfigCpu*>(pThreadParam->pParam);
	CSolidSBCThread*                    pThread      = reinterpret_cast<CSolidSBCThread*>(pThreadParam->pInstance);

	//randomize cpu usage
	if (pTestConfig->GetRandomize()){
		unsigned int number = 0, nRandomNumber = 0;

		while(!pThread->ShallEnd())
		{
			//how long should the pause interval last?
			number = rand( );
			nRandomNumber = number % (pTestConfig->GetMaxRand()+1);

			//make some pause before using cpu power, check for exit every second
			for ( unsigned int i = 0; i < nRandomNumber; i++ ){
				usleep(950 * 1000);
				if ( pThread->ShallEnd() )
					break;
			}

			struct timeval starttime;
			memset(&starttime,0,sizeof(timeval));
			gettimeofday(&starttime,0);

			//how long shall cpu-intensive interval last?;
			number = rand( );
			nRandomNumber = number % (pTestConfig->GetMaxRand()+1);
			nRandomNumber *= 1000;

			//use some cpu power
			while ( 1 ){
				struct timeval curtime;
				memset(&curtime,0,sizeof(timeval));
				gettimeofday(&curtime,0);

				if ( pThread->ShallEnd() )
					break;
				if ( timevaldiff( starttime, curtime ) >= (long)nRandomNumber )
					break;
			}
		}
	}
	// static cpu usage
	else {
		struct timeval waitstruct;

		waitstruct.tv_sec  = (long) pTestConfig->GetSleepMS()/1000;
		waitstruct.tv_usec = (long) (((long)pTestConfig->GetSleepMS()%1000)*1000);

		while(!pThread->ShallEnd()){
			//we do not need to check for an interval >1s here,
			//because this would be insanely high...
			select( NULL, NULL, NULL, NULL, &waitstruct);
		}
	}

	return 0;
}

//#pragma optimize( "", on )
