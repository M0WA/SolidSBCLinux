/*
 * CSolidSBCSocketConfig.cpp
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#include "../client/CSolidSBCClient.h"
#include "../helper/CSolidSBCLogging.h"

#include "../../../SolidSBCSDK/src/test/CSolidSBCTestConfig.h"

#include "CSolidSBCSocketConfig.h"
#include "CSolidSBCPacket.h"
#include "CSolidSBCPacketConfigRequest.h"

CSolidSBCSocketConfig::CSolidSBCSocketConfig()
: CSolidSBCSocket()
, m_bFinished(true)
{
}

CSolidSBCSocketConfig::~CSolidSBCSocketConfig()
{
}

void CSolidSBCSocketConfig::GetConfigsFromServer(void)
{
	//check if we are already fetching configs
	if(!m_bFinished)
		return;

	//send config request
	CSolidSBCPacketConfigRequest configRequest(CSolidSBCClient::GetInstance()->GetClientName(),CSolidSBCClient::GetInstance()->GetUuid());
	configRequest.SendPacket(this);

	CSolidSBCSocket::Read((CSolidSBCSocket::OnReadCallback)&CSolidSBCSocketConfig::ReadHeaderCallback, sizeof(CSolidSBCPacket::SSBC_PACKET_HEADER));

	//wait for all config responses
	m_bFinished = false;
	while(!m_bFinished)
		sleep(1);
}

void* CSolidSBCSocketConfig::OnConnect(const CSolidSBCSocket::_SSBC_SOCKET_CONNECT_STATE nState, CSolidSBCSocket::_PSSBC_SOCKET_PARAM pConnectParams)
{
	CSolidSBCSocketConfig* pConfigSocket = reinterpret_cast<CSolidSBCSocketConfig*>(pConnectParams->pcSocket);

	if (nState != CSolidSBCSocket::SSBC_SOCKET_CONNECT_STATE_SUCCESS){
		pConfigSocket->Close();
		return 0;}

	pConfigSocket->GetConfigsFromServer();
	return 0;
}

void CSolidSBCSocketConfig::ReadHeaderCallback(const _SSBC_SOCKET_READ_STATE nState, const _PSSBC_READ_SOCKET_PARAM pReadParams)
{
	CSolidSBCSocketConfig* pConfigSocket         = reinterpret_cast<CSolidSBCSocketConfig*>(pReadParams->pcSocket);
	CSolidSBCPacket::PSSBC_PACKET_HEADER pHeader = (CSolidSBCPacket::PSSBC_PACKET_HEADER)(pReadParams->pBuffer);

	pConfigSocket->m_bFinished = true;

	//TODO: pass error messages to OnConfigError()
	switch(nState)
	{
	case SSBC_SOCKET_READ_STATE_SUCCESS:
		{
			CSolidSBCPacket* pPacket = CSolidSBCPacket::ReadPacket(*pHeader,pConfigSocket);
			if (!pPacket) {
				CSolidSBCClient::GetInstance()->OnConfigError();
				break; }
			else {
				std::string sConfigXml = pPacket->ToString();
				if (sConfigXml == ""){
					CSolidSBCClient::GetInstance()->OnConfigError();
					break;}

				CSolidSBCClient::GetInstance()->OnConfigSuccess(sConfigXml);
				pConfigSocket->Read((CSolidSBCSocket::OnReadCallback)&CSolidSBCSocketConfig::ReadHeaderCallback,sizeof(CSolidSBCPacket::SSBC_PACKET_HEADER));

#ifdef _DEBUG
				std::string sTestName  = CSolidSBCTestConfig::GetTestNameFromXML(sConfigXml);
				if (sTestName == ""){
					CSolidSBCClient::GetInstance()->OnConfigError();
					break;}

				g_cLogging.Log(_SSBC_LOG_DEBUG,"dumping config for \"" + sTestName +"\" reply:\n" + sConfigXml);
#endif
			}
		}
		break;

	case SSBC_SOCKET_READ_STATE_FAILED:
	case SSBC_SOCKET_READ_STATE_WAIT:
	default:
		CSolidSBCClient::GetInstance()->OnConfigError();
		break;
	}
}
