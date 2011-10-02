/*
 * CSolidSBCSocket.cpp
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCSocket.h"

#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

extern int errno;

#include "../helper/CSolidSBCLogging.h"

#define SOCKET_READ_BUFFER_SIZE 255

CSolidSBCSocket::CSolidSBCSocket(int nSocketFamily, int nSocketType)
: m_nSocketFamily(nSocketFamily)
, m_nSocketType(nSocketType)
, m_hSocket(-1)
{
}

CSolidSBCSocket::~CSolidSBCSocket()
{
	Close();
}

CSolidSBCSocket::_SSBC_SOCKET_CONNECT_STATE CSolidSBCSocket::Connect(const std::string& sHost, const short nPort, OnConnectCallback pCallback)
{
	//check if socket is already connected
	if (m_hSocket != -1){
		g_cLogging.Log(_SSBC_LOG_WARN, _SSBC_WARN_SOCKET_STILL_CONNECTED);
		Close();}

	//check if we are using a supported family
	switch(m_nSocketFamily)
	{
	case AF_INET:
		break;

	case AF_INET6:
		g_cLogging.Log(_SSBC_LOG_ERROR, _SSBC_ERR_SOCKET_FAMILY_NOT_SUPPORTED);
		return SSBC_SOCKET_CONNECT_STATE_FAILED;

	default:
		g_cLogging.Log(_SSBC_LOG_ERROR, _SSBC_ERR_SOCKET_FAMILY_NOT_SUPPORTED);
		return SSBC_SOCKET_CONNECT_STATE_FAILED;
	}

	//check if we are using a supported type
	switch(m_nSocketType)
	{
	case SOCK_STREAM:
		break;

	default:
		g_cLogging.Log(_SSBC_LOG_ERROR, _SSBC_ERR_SOCKET_TYPE_NOT_SUPPORTED);
		return SSBC_SOCKET_CONNECT_STATE_FAILED;
	}

	//create socket
	m_hSocket = socket(m_nSocketFamily, m_nSocketType, 0);
	if ( m_hSocket == -1 ){
		g_cLogging.Log(_SSBC_LOG_ERROR, _SSBC_ERR_NO_CREATE_SOCKET_STRING );
		return SSBC_SOCKET_CONNECT_STATE_FAILED;}

	//finding host ip
	struct sockaddr_in target;
	hostent * targetHost = gethostbyname(sHost.c_str());
	if(targetHost)
	{
		//is a hostname
		target.sin_addr = *(struct in_addr*)targetHost->h_addr;
	}
	else
	{
		//try to interpret string as an ip address
		target.sin_addr.s_addr = inet_addr(sHost.c_str());
		if (target.sin_addr.s_addr == INADDR_NONE)	{
			g_cLogging.Log(_SSBC_LOG_ERROR, _SSBC_ERR_NO_VALID_SERVER_SPECIFIED );
			return SSBC_SOCKET_CONNECT_STATE_FAILED;}
	}

	//assemble sockaddr for target
	target.sin_family = m_nSocketFamily;
	target.sin_port   = htons(nPort);

	//switch to non blocking mode if a callback function is specified
	if (pCallback)
		SetBlockingMode(false);

	//trying to connect
	int nConnect = connect(m_hSocket,(struct sockaddr*)&target, sizeof(target));
	if (pCallback)
	{
		//non blocking connect
		if (errno == EINPROGRESS)
		{
			//connect pending
			RegisterConnectCallback(pCallback);
			return SSBC_SOCKET_CONNECT_STATE_WAIT;
		}
		else if(nConnect == 0)
		{
			//connect was successful
			return SSBC_SOCKET_CONNECT_STATE_SUCCESS;
		}
		else
		{
			//connect was not successful
			return SSBC_SOCKET_CONNECT_STATE_FAILED;
		}
	}
	else if ( nConnect != 0 )
	{
		//connect was not successful
		return SSBC_SOCKET_CONNECT_STATE_FAILED;
	}
	else
	{
		//blocking connect was successful
		return SSBC_SOCKET_CONNECT_STATE_SUCCESS;
	}
}

void CSolidSBCSocket::Close(void)
{
	if (m_hSocket != -1) {
		close(m_hSocket);
		m_hSocket = -1;	}
}

bool CSolidSBCSocket::IsWritable(timeval* timeout)
{
	fd_set fdWrite;
	FD_ZERO(&fdWrite);
	FD_SET(m_hSocket,&fdWrite);

	if( select(m_hSocket+1, 0, &fdWrite, 0, timeout) )
	{
		if ( FD_ISSET(m_hSocket,&fdWrite) )
		{
			return true;
		}
		else
		{
			//timed out
			return false;
		}
	}
	return false;
}

bool CSolidSBCSocket::IsWritable(const bool bBlocking)
{
	struct timeval  timeout;

	struct timeval* ptimeOut = 0;
	if (!bBlocking)
	{
		//zero timeout - means returns immediately
		timeout.tv_sec  = 0;
		timeout.tv_usec = 0;
		ptimeOut = &timeout;
	}
	else
	{
		ptimeOut = 0;
	}

	return IsWritable(ptimeOut);
}

bool CSolidSBCSocket::IsReadable(timeval* timeout)
{
	fd_set fdRead;
	FD_ZERO(&fdRead);
	FD_SET(m_hSocket,&fdRead);

	if( select(m_hSocket+1, &fdRead, 0, 0, timeout) )
	{
		if ( FD_ISSET(m_hSocket,&fdRead) )
		{
			return true;
		}
		else
		{
			//timed out
			return false;
		}
	}
	return false;
}

bool CSolidSBCSocket::IsReadable(const bool bBlocking)
{
	struct timeval  timeout;

	struct timeval* ptimeOut = 0;
	if (!bBlocking)
	{
		//zero timeout - means returns immediately
		timeout.tv_sec  = 0;
		timeout.tv_usec = 0;
		ptimeOut = &timeout;
	}
	else
	{
		ptimeOut = 0;
	}

	return IsReadable(ptimeOut);
}

void CSolidSBCSocket::Read(OnReadCallback pCallback, int nReadBytes)
{
	RegisterReadCallback(pCallback, nReadBytes);
}

CSolidSBCSocket::_SSBC_SOCKET_READ_STATE CSolidSBCSocket::Read(_PSSBC_READ_SOCKET_PARAM pParam)
{
	bool bReadAll = !(pParam->nReadBytes);
	int nBufferSize = pParam->nReadBytes ? pParam->nReadBytes : SOCKET_READ_BUFFER_SIZE;

	pParam->pBuffer = (unsigned char*)malloc(nBufferSize);

	int hSocket = pParam->pcSocket->m_hSocket;

	fd_set fdRead;
	FD_ZERO(&fdRead);
	FD_SET(hSocket,&fdRead);

	if ( ( select(hSocket+1, &fdRead, 0, 0, &pParam->timeout) <= 0 )
	  || !FD_ISSET(hSocket,&fdRead) )
	{
		pParam->nReadBytes = 0;

		free(pParam->pBuffer);
		pParam->pBuffer    = 0;

		return SSBC_SOCKET_READ_STATE_FAILED;
	}

	pParam->pcSocket->SetBlockingMode( true );
	int nRead = recv(hSocket, pParam->pBuffer, nBufferSize, 0);
	pParam->pcSocket->SetBlockingMode( false );

	pParam->nReadBytes = nRead ? nRead : 0;
	if (nRead <= 0)
	{
		free(pParam->pBuffer);
		pParam->pBuffer = 0;

		return SSBC_SOCKET_READ_STATE_FAILED;
	}
	else if (nRead == nBufferSize)
	{
		if(bReadAll)
		{
			while(1)
			{
				pParam->pBuffer = (unsigned char*)realloc(pParam->pBuffer,pParam->nReadBytes + SOCKET_READ_BUFFER_SIZE);
				memset(&pParam->pBuffer[pParam->nReadBytes],0,SOCKET_READ_BUFFER_SIZE);

				pParam->pcSocket->SetBlockingMode( true );
				int nSubRead = recv(hSocket, pParam->pBuffer, nBufferSize, 0);
				pParam->pcSocket->SetBlockingMode( false );
				if (nSubRead <= 0)
				{
					break;
				}
				else
				{
					pParam->nReadBytes += nSubRead;

					if(nSubRead == nBufferSize)
					{
						break;
					}
				}
			}
		}

		return SSBC_SOCKET_READ_STATE_SUCCESS;
	}
	else
	{
		return SSBC_SOCKET_READ_STATE_SUCCESS;
	}
}

void CSolidSBCSocket::SetBlockingMode( const bool bIsBlocking )
{
	if ( bIsBlocking ){
		//set to blocking io
		int flags = fcntl(m_hSocket, F_GETFL);
		fcntl(m_hSocket, F_SETFL, flags & ~O_NONBLOCK);
	} else {
		//set to non-blocking io
		int flags = fcntl(m_hSocket, F_GETFL);
		fcntl(m_hSocket, F_SETFL, flags | O_NONBLOCK);
	}
}

void CSolidSBCSocket::RegisterCallback(ThreadFunction pFunction, _PSSBC_SOCKET_PARAM pParam, bool bAutoDelete)
{
	CSolidSBCThread* pThread = new CSolidSBCThread(pFunction, pParam, bAutoDelete);
	pThread->StartThread();
}

void CSolidSBCSocket::RegisterConnectCallback(OnConnectCallback pCallback)
{
	_PSSBC_SOCKET_PARAM pConnectParam = new _SSBC_SOCKET_PARAM;
	pConnectParam->pcSocket  = this;
	pConnectParam->pCallback = (void*)pCallback;

	//set connect timeout to 5 seconds
	pConnectParam->timeout.tv_sec  = 5;
	pConnectParam->timeout.tv_usec = 0;

	RegisterCallback((ThreadFunction)&WaitForConnectThread, pConnectParam, true);
}

void CSolidSBCSocket::RegisterReadCallback(OnReadCallback pCallback, int nReadBytes)
{
	_PSSBC_READ_SOCKET_PARAM pReadParam = new _SSBC_READ_SOCKET_PARAM;
	pReadParam->pcSocket   = this;
	pReadParam->pCallback  = (void*)pCallback;
	pReadParam->nReadBytes = nReadBytes;

	//set connect timeout to 5 seconds
	pReadParam->timeout.tv_sec  = 5;
	pReadParam->timeout.tv_usec = 0;

	RegisterCallback((ThreadFunction)&WaitForReadThread, pReadParam, true);
}

void* CSolidSBCSocket::WaitForConnectThread(_PSSBC_THREAD_PARAM param)
{
	_PSSBC_SOCKET_PARAM pConnectParam = (_PSSBC_SOCKET_PARAM)param->pParam;

	//TODO: make this thread safe
	_SSBC_SOCKET_CONNECT_STATE nState = SSBC_SOCKET_CONNECT_STATE_FAILED;
	if( pConnectParam->pcSocket->IsWritable() )
	{
		nState = SSBC_SOCKET_CONNECT_STATE_SUCCESS;
	}
	else
	{
		//timed out
		nState = SSBC_SOCKET_CONNECT_STATE_FAILED;
	}

	//invoke callback function with new connect state
	if (pConnectParam->pCallback)
		((OnConnectCallback)pConnectParam->pCallback)(nState,pConnectParam);

	delete pConnectParam;
	return 0;
}

void* CSolidSBCSocket::WaitForReadThread(_PSSBC_THREAD_PARAM param)
{
	_PSSBC_READ_SOCKET_PARAM pReadParam = reinterpret_cast<_PSSBC_READ_SOCKET_PARAM>(param->pParam);
	_SSBC_SOCKET_READ_STATE nState = Read(pReadParam);

	//invoke callback function with new read state
	if (pReadParam->pCallback)
		((OnReadCallback)pReadParam->pCallback)(nState,pReadParam);

	delete pReadParam;
	return 0;
}

int CSolidSBCSocket::Send(unsigned char* pcPacket, int nSendBytes)
{
	return send(m_hSocket,pcPacket,nSendBytes,0);
}
