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
#include "../../../../SolidSBCSDK/src/debug/CSolidSBCPerformanceCounter.h"

#include "../../interface/CSolidSBCTestManagerImpl.h"

#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>

void* CSolidSBCTestThreadNetTCP::ThreadFunc(void* pParam)
{
	CSolidSBCThread::PSSBC_THREAD_PARAM pThreadParam = reinterpret_cast<CSolidSBCThread::PSSBC_THREAD_PARAM>(pParam);
	CSolidSBCTestConfigNetTCP*          pTestConfig  = reinterpret_cast<CSolidSBCTestConfigNetTCP*>(pThreadParam->pParam);
	CSolidSBCThread*                    pThread      = reinterpret_cast<CSolidSBCThread*>(pThreadParam->pInstance);

	unsigned int nTTL = pTestConfig->GetTTL();

	CSolidSBCPerformanceCounter perfCounter;
	//get ip from hostname and assemble sockaddr_in...
	struct hostent* targetHost = gethostbyname(pTestConfig->GetHost().c_str());
	struct sockaddr_in target;
	memset(&target,0,sizeof(struct sockaddr_in));
	target.sin_family = AF_INET;
	target.sin_port   = htons(pTestConfig->GetPort());
	if ( targetHost
	&& ( targetHost->h_addrtype == 2 )
	&& ( targetHost->h_length   == 4 ))
		memcpy(targetHost->h_addr, &target.sin_addr.s_addr,targetHost->h_length);
	else
		target.sin_addr.s_addr = inet_addr(pTestConfig->GetHost().c_str());

	//convert ttl to timeval struct
	timeval selecttimeout;
	if ( nTTL > 1000 ) {
		selecttimeout.tv_sec  = static_cast<long>( ( static_cast<double>(nTTL) / static_cast<double>(1000.0f) ) );
		selecttimeout.tv_usec = static_cast<long>( ( nTTL - (selecttimeout.tv_sec * 1000) ) * 1000 );
	}
	else if ( nTTL == 1000 ) {
		selecttimeout.tv_sec  = 1;
		selecttimeout.tv_usec = 0;
	}
	else {
		selecttimeout.tv_sec  = 0;
		selecttimeout.tv_usec = static_cast<long>(nTTL * 1000); //milli -> micro
	}

	//do the tests...
	while ( !pThread->ShallEnd() )
	{
		//create nonblocking socket, prepare fd_sets,
		int sock  = socket(AF_INET,SOCK_STREAM,0);
		int flags = fcntl(sock, F_GETFL, 0);
		fcntl(sock, F_SETFL, flags | O_NONBLOCK);
		fd_set exceptfds, writefds;

		//try to connect
		double dDurationMS = perfCounter.Stop();
		perfCounter.Start();
		int nReturnConnect = connect(sock,(struct sockaddr*)&target,sizeof(struct sockaddr_in));

		//successful connect
		if (!nReturnConnect)
		{
			dDurationMS = perfCounter.Stop();
		}
		//connect pending
		else if (nReturnConnect == EINPROGRESS)
		{
			bool bExitSelectLoop = true;
			while ( bExitSelectLoop )
			{
				FD_ZERO(&exceptfds); FD_SET(sock,&exceptfds);
				FD_ZERO(&writefds);  FD_SET(sock,&writefds);
				if ( select(sock+1, 0, &writefds, &exceptfds,&selecttimeout) == 1 )
				{
					if ( FD_ISSET(sock, &writefds) )
					{
						dDurationMS = perfCounter.Stop();
						bExitSelectLoop = false;
					}
					else if ( FD_ISSET(sock, &exceptfds) )
					{
						dDurationMS = perfCounter.Stop();
						bExitSelectLoop = false;
					}
				}
				bExitSelectLoop = false;

				dDurationMS = perfCounter.Stop();
			}
		}
		//some fancy error occured...
		else
		{
			dDurationMS = perfCounter.Stop();
		}
		close(sock);

		if (pTestConfig->GetTransmitData())
		{
			CSolidSBCTestResultNetTCP* pResult = new CSolidSBCTestResultNetTCP();
			pResult->SetHandshakeDuration(dDurationMS);
			(CSolidSBCTestManagerImpl::GetInstance())->AddResult(pResult);
		}

		//check if we are faster than nTcpConnInterval
		unsigned int nInterval = pTestConfig->GetInterval();
		if (  (nInterval > 0)
		   && (nInterval > nTTL)
		   ) {
			unsigned int nDurationMS = static_cast<unsigned int>(dDurationMS);
			if ( nDurationMS < nInterval ) {
				unsigned int nSleepMS = nInterval - nDurationMS;
				//TODO: dont sleep too long here in once piece,
				//      recheck regularly (every 25-50ms) if thread should end
				//      hangs on shutdown if "nSleepMS" is set too long
				usleep(nSleepMS * 1000);
			}
		}
	}

	pthread_exit((void*)0);
}
