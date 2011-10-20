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

	m_pUuidManager        = new CSolidSBCUuidManager(GetUuidFile());
	m_pTestLibraryManager = new CSolidSBCTestLibraryManager(GetTestLibraryPath());
}

CSolidSBCClient::~CSolidSBCClient()
{
	delete m_pTestLibraryManager;
	m_pTestLibraryManager = 0;

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

	if(!StartConfigConnection())
		return false;

	if(!StartResultConnection())
		return false;

	if(!StartTests())
		return false;

	return true;
}

void CSolidSBCClient::Stop(void)
{
	CSolidSBCTestLibraryManager::GetInstance()->StopAllTests();
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
		if (!CSolidSBCTestLibraryManager::GetInstance()->StartTestFromConfig(*iIter))
		{
			std::string sTestName = CSolidSBCTestConfig::GetTestNameFromXML(*iIter);
			if(sTestName != "") {
				g_cLogging.Log(_SSBC_LOG_WARN, _SSBC_WARN_COULD_NOT_FIND_TEST + sTestName); }
			else {
				g_cLogging.Log(_SSBC_LOG_WARN, _SSBC_WARN_COULD_NOT_PARSE_TESTCONFIG + *iIter); }

			return false;
		}
	}
	return true;
}

bool CSolidSBCClient::StartConfigConnection(void)
{
	CSolidSBCSocket::_SSBC_SOCKET_CONNECT_STATE nState =
		CSolidSBCSocket::SSBC_SOCKET_CONNECT_STATE_FAILED;

	nState = m_configSocket.Connect(
					GetConfigServerHost(),
					GetConfigServerPort(),
					GetClientName(),
					GetUuid(),
					(CSolidSBCSocket::OnConnectCallback) &CSolidSBCSocketConfig::OnConnect);

	if (
		(nState == CSolidSBCSocket::SSBC_SOCKET_CONNECT_STATE_SUCCESS) ||
		(nState == CSolidSBCSocket::SSBC_SOCKET_CONNECT_STATE_WAIT)
	   )
	{
		int nTimeout = GetConfigConnectionTimeout();
		while (!m_configSocket.IsInitialized() && nTimeout) {
			sleep(1);
			nTimeout--;}

		if(m_configSocket.IsInitialized())
		{
			std::vector<std::string> vecTestConfigStrings =  m_configSocket.GetTestConfigStrings();
			if (vecTestConfigStrings.size()) {
				return true; }
		}
	}

	m_configSocket.Close();
	g_cLogging.Log(_SSBC_LOG_ERROR, _SSBC_ERR_SOCKET_CONNECT_FAILED);
	return false;
}

bool CSolidSBCClient::StartResultConnection(void)
{
	CSolidSBCSocket::_SSBC_SOCKET_CONNECT_STATE nState =
		CSolidSBCSocket::SSBC_SOCKET_CONNECT_STATE_FAILED;

	nState = m_resultSocket.Connect(
			GetResultServerHost(),
			GetResultServerPort(),
			GetClientName(),
			GetUuid(),
			(CSolidSBCSocket::OnConnectCallback) &CSolidSBCSocketResult::OnConnect);

	if (
		(nState == CSolidSBCSocket::SSBC_SOCKET_CONNECT_STATE_SUCCESS) ||
		(nState == CSolidSBCSocket::SSBC_SOCKET_CONNECT_STATE_WAIT)
	   )
	{
		int nTimeout = GetResultConnectionTimeout();
		while (!m_resultSocket.IsInitialized() && nTimeout) {
			sleep(1);
			nTimeout--;}

		if(m_resultSocket.IsInitialized()){
			return true;}

	}

	m_resultSocket.Close();
	g_cLogging.Log(_SSBC_LOG_ERROR, _SSBC_ERR_SOCKET_CONNECT_FAILED);
	return false;
}
