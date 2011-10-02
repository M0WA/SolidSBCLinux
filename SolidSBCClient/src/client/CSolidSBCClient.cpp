/*
 * CSolidSBCClient.cpp
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCClient.h"
#include "../../../SolidSBCSDK/src/log/CSolidSBCLogging.h"

#include <string>
#include <vector>

CSolidSBCClient* g_pSolidSBCClientInstance = 0;

CSolidSBCClient::CSolidSBCClient(int argc, const char** argv)
: m_pUuidManager(0)
{
	g_pSolidSBCClientInstance = this;

	ParseCommandline(argc, argv);
	m_pUuidManager = new CSolidSBCUuidManager(GetUuidFile());
	m_pTestManager = new CSolidSBCTestManager(GetTestLibraryPath());
}

CSolidSBCClient::~CSolidSBCClient()
{
	delete m_pTestManager;
	m_pTestManager = 0;

	delete m_pUuidManager;
	m_pUuidManager = 0;

	g_pSolidSBCClientInstance = 0;
}

CSolidSBCClient* CSolidSBCClient::GetInstance(void)
{
	return g_pSolidSBCClientInstance;
}

bool CSolidSBCClient::Start(void)
{
	Stop();

	if(!InitTestConfigs())
		return false;

	if(!StartTests())
		return false;

	return true;
}

void CSolidSBCClient::Stop(void)
{
	//TODO: CSolidSBCTestManager::GetInstance()->StopAllTests();
}

void CSolidSBCClient::OnShutdown(void)
{
	//careful, called by sighandler...
	Stop();
}

bool CSolidSBCClient::StartTests(void)
{
	std::vector<std::string> vecTestConfigStrings = m_configSocket.GetTestConfigStrings();

	std::vector<std::string>::iterator iIter      = vecTestConfigStrings.begin();
	for(; iIter != vecTestConfigStrings.end(); iIter++)
	{
		if (!CSolidSBCTestManager::GetInstance()->StartTestFromConfig(*iIter))
		{
			//TODO:handle this error
		}
	}
	return false;
}

bool CSolidSBCClient::InitTestConfigs(void)
{
	CSolidSBCSocket::_SSBC_SOCKET_CONNECT_STATE nState =
		CSolidSBCSocket::SSBC_SOCKET_CONNECT_STATE_FAILED;

	nState = m_configSocket.Connect(
					GetConfigServerHost(),
					GetConfigServerPort(),
					(CSolidSBCSocket::OnConnectCallback) &CSolidSBCSocketConfig::OnConnect);

	if (
		(nState == CSolidSBCSocket::SSBC_SOCKET_CONNECT_STATE_SUCCESS) ||
		(nState == CSolidSBCSocket::SSBC_SOCKET_CONNECT_STATE_WAIT)
	   )
	{
		while (!m_configSocket.IsFinished())
			sleep(1);

		std::vector<std::string> vecTestConfigStrings =  m_configSocket.GetTestConfigStrings();
		if (!vecTestConfigStrings.size())
			return false;

		return true;
	}
	else
		return false;
}

/*
void CSolidSBCClient::OnConfigSuccess(const std::string& sConfigXml)
{
	if (!CSolidSBCTestManager::GetInstance()->StartTestFromConfig(sConfigXml))
	{
		//TODO:handle this error
	}
}

void CSolidSBCClient::OnConfigError(void) const
{
	//not an error if CSolidSBCClient::OnConfigSuccess
	//has at least been called once.
	//then at least one config has been fetched from the
	//server...

	//TODO: check if this is an error or not, implement more/specific information on connect error
	//if (!m_vecTestConfigs.size())
		g_cLogging.Log(_SSBC_LOG_ERROR, _SSBC_ERR_SOCKET_CONNECT_FAILED);
}
*/
