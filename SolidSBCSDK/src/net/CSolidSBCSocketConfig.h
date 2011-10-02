/*
 * CSolidSBCSocketConfig.h
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCSOCKETCONFIG_H_
#define CSOLIDSBCSOCKETCONFIG_H_

#include "CSolidSBCSocket.h"

class CSolidSBCSocketConfig: public CSolidSBCSocket
{
public:
	CSolidSBCSocketConfig();
	virtual ~CSolidSBCSocketConfig();
	void GetConfigsFromServer(const std::string& sClientName, const std::string& sUuid);

	static void* OnConnect(const CSolidSBCSocket::_SSBC_SOCKET_CONNECT_STATE nState, CSolidSBCSocket::_PSSBC_SOCKET_PARAM pConnectParams);

private:
	static void  ReadHeaderCallback(const _SSBC_SOCKET_READ_STATE nState, const _PSSBC_READ_SOCKET_PARAM pReadParams);
	static void  ReadPacketCallback(const _SSBC_SOCKET_READ_STATE nState, const _PSSBC_READ_SOCKET_PARAM pReadParams);

	std::string m_sClientName;
	std::string m_sUuid;

	volatile bool m_bFinished;
};

#endif /* CSOLIDSBCSOCKETCONFIG_H_ */
