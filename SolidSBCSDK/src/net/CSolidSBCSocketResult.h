/*
 * CSolidSBCSocketResult.h
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCSOCKETRESULT_H_
#define CSOLIDSBCSOCKETRESULT_H_

#include "CSolidSBCSocket.h"

class CSolidSBCSocketResult: public CSolidSBCSocket
{
public:
	CSolidSBCSocketResult();
	virtual ~CSolidSBCSocketResult();

	virtual _SSBC_SOCKET_CONNECT_STATE Connect(const std::string& sHost, const short nPort, const std::string& sClientName, const std::string& sUuid, OnConnectCallback pCallback = 0);
	bool IsInitialized(void) const {return m_bInitialized;}

	static void* OnConnect(const CSolidSBCSocket::_SSBC_SOCKET_CONNECT_STATE nState, CSolidSBCSocket::_PSSBC_SOCKET_PARAM pConnectParams);

private:
	std::string   m_sClientName;
	std::string   m_sUuid;

	volatile bool m_bInitialized;
};

#endif /* CSOLIDSBCSOCKETRESULT_H_ */
