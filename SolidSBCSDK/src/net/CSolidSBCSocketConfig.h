/*
 * CSolidSBCSocketConfig.h
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCSOCKETCONFIG_H_
#define CSOLIDSBCSOCKETCONFIG_H_

#include <string>
#include <vector>

#include "CSolidSBCSocket.h"

class CSolidSBCSocketConfig: public CSolidSBCSocket
{
public:
	CSolidSBCSocketConfig();
	virtual ~CSolidSBCSocketConfig();
	virtual void Close(void);
	virtual _SSBC_SOCKET_CONNECT_STATE Connect(const std::string& sHost, const short nPort, const std::string& sClientName, const std::string& sUuid, OnConnectCallback pCallback = 0);

	void GetConfigsFromServer(void);

	std::vector<std::string> GetTestConfigStrings(void) const { return m_vecTestConfigs; }
	unsigned int             GetTestConfigErrors (void) const { return m_nErrorCount;    }

	bool IsInitialized(void) const { return m_bInitialized; }

	static void* OnConnect(const CSolidSBCSocket::_SSBC_SOCKET_CONNECT_STATE nState, CSolidSBCSocket::_PSSBC_SOCKET_PARAM pConnectParams);

private:

	static void ReadHeaderCallback(const _SSBC_SOCKET_READ_STATE nState, const _PSSBC_READ_SOCKET_PARAM pReadParams);
	static void ReadPacketCallback(const _SSBC_SOCKET_READ_STATE nState, const _PSSBC_READ_SOCKET_PARAM pReadParams);

	std::string m_sClientName;
	std::string m_sUuid;

	std::vector<std::string> m_vecTestConfigs;
	unsigned int  m_nErrorCount;

	volatile bool m_bInitialized;
};

#endif /* CSOLIDSBCSOCKETCONFIG_H_ */
