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
#include "../../../../SolidSBCSDK/src/debug/CSolidSBCPerformanceCounter.h"

#include "../../interface/CSolidSBCTestManagerImpl.h"

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <string.h>

CPing::CPing(void)
{
}

CPing::~CPing(void)
{
}

bool CPing::Ping( std::string strHost, unsigned int nTTL, unsigned int nPayloadSize )
{
	//prepare destination
	struct sockaddr_in to;
	memset(&to,0x00,sizeof(struct sockaddr_in));
	to.sin_family      = AF_INET;
	to.sin_addr.s_addr = inet_addr( strHost.c_str() );
	to.sin_port        = 0;

	//allocating space for packet
	int nPacketLength  = sizeof(struct icmphdr) + nPayloadSize;
	char* pPacket      = new char[nPacketLength];
	char* pPacketStart = pPacket;

	//prepare icmp header
	struct icmphdr icmphdr;
	memset(&icmphdr,0x00,sizeof(struct icmphdr));
	icmphdr.type       = ICMP_ECHO;
	icmphdr.code       = 0;
	icmphdr.un.echo.id = getpid();
	icmphdr.un.echo.sequence = 0;

	//copy icmp header to packet
	memcpy(pPacket, &icmphdr, sizeof(struct icmphdr) );
	pPacket += sizeof(struct icmphdr);

	//prepare payload
	memset(pPacket, 0xFE, nPayloadSize);
	pPacket += nPayloadSize;

	//compute checksum
	icmphdr.checksum = in_cksum((unsigned short*)pPacketStart, nPacketLength);

	//get protocol name, accuire socket
	struct protoent	*proto = getprotobyname("icmp");
	int nPingSocket = socket(AF_INET,SOCK_RAW, proto->p_proto);

	//send it and free packet space
	int bytes = sendto(nPingSocket, pPacketStart, nPacketLength, 0, (struct sockaddr*)&to, sizeof(struct sockaddr_in));
	delete [] pPacket; pPacket = NULL;

	return CatchReplyPacket(nPingSocket,nTTL);
}

bool CPing::CatchReplyPacket(int nSock, unsigned int nTTL)
{
	//TODO: receive reply packet
	return false;
}

u_short CPing::in_cksum(unsigned short *addr, int len)
{
	u_short i = 0, *word = addr;
	u_long acc = 0;

	while(i++ < len / 2)
		acc += *(word++);

	return ~(*(unsigned short *)&acc + *((unsigned short *)&acc + 1));
}

void* CSolidSBCTestThreadNetPing::ThreadFunc(void* pParam)
{
	CSolidSBCThread::PSSBC_THREAD_PARAM pThreadParam = reinterpret_cast<CSolidSBCThread::PSSBC_THREAD_PARAM>(pParam);
	CSolidSBCTestConfigNetPing*         pTestConfig  = reinterpret_cast<CSolidSBCTestConfigNetPing*>(pThreadParam->pParam);
	CSolidSBCThread*                    pThread      = reinterpret_cast<CSolidSBCThread*>(pThreadParam->pInstance);

	CPing cPing;
	CSolidSBCPerformanceCounter cPerf;
	while ( !pThread->ShallEnd() )
	{
		//ping host
		cPerf.Start();
		bool bReturn = cPing.Ping( pTestConfig->GetHost().c_str(), pTestConfig->GetTTL(), pTestConfig->GetPayloadSize() );
		double dDuration = cPerf.Stop();

		//transmit data if neccessary
		if ( pTestConfig->GetTransmitData() )
		{
			CSolidSBCTestResultNetPing* pResult = new CSolidSBCTestResultNetPing();
			//TODO: fill result packet
			(CSolidSBCTestManagerImpl::GetInstance())->AddResult(pResult);
		}

		//sleep 1sec
		//usleep( 1000 * 1000 );
	}
	pthread_exit((void*)0);
}
