/*
 * CSolidSBCSocketResult.cpp
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCSocketResult.h"
#include "CSolidSBCPacketResultRequest.h"

CSolidSBCSocketResult::CSolidSBCSocketResult()
: m_bInitialized(false)
{
	SetNoSigPipe();
}

CSolidSBCSocketResult::~CSolidSBCSocketResult()
{
}

CSolidSBCSocket::_SSBC_SOCKET_CONNECT_STATE CSolidSBCSocketResult::Connect(const std::string& sHost, const short nPort, const std::string& sClientName, const std::string& sUuid, CSolidSBCSocket::OnConnectCallback pCallback)
{
	if(m_bInitialized)
		Close();

	m_bInitialized = false;
	m_sClientName  = sClientName;
	m_sUuid        = sUuid;

	return CSolidSBCSocket::Connect(sHost, nPort, pCallback);
}

void* CSolidSBCSocketResult::OnConnect(const CSolidSBCSocket::_SSBC_SOCKET_CONNECT_STATE nState, CSolidSBCSocket::_PSSBC_SOCKET_PARAM pConnectParams)
{
	CSolidSBCSocketResult* pResultSocket = reinterpret_cast<CSolidSBCSocketResult*>(pConnectParams->pcSocket);

	CSolidSBCPacketResultRequest request(pResultSocket->m_sClientName,pResultSocket->m_sUuid);
	if (
		 nState != CSolidSBCSocket::SSBC_SOCKET_CONNECT_STATE_SUCCESS ||
	     !request.SendPacket(pResultSocket)
	   )
	{
		pResultSocket->m_bInitialized = false;
		pResultSocket->Close();
	}
	else
	{
		//no need to wait for a response here, request is not replied by the server
		pResultSocket->m_bInitialized = true;
	}

	return 0;
}
