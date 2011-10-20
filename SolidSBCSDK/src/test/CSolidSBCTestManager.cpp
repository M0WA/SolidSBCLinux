/*
 * CSolidSBCTestManager.cpp
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCTestManager.h"

#include "../thread/CSolidSBCAutoMutex.h"

CSolidSBCTestManager::CSolidSBCTestManager()
{
	m_pResultThread = new CSolidSBCThread((CSolidSBCThread::ThreadFunction)&CSolidSBCTestManager::ResultThread, this, true);
}

CSolidSBCTestManager::~CSolidSBCTestManager()
{
	StopAllTests();

	std::map<std::string,CSolidSBCTestConfig*>::iterator iIter = m_mapTestNamesConfigs.begin();
	for(;iIter != m_mapTestNamesConfigs.end(); iIter++)
		if(iIter->second)
			delete iIter->second;

	m_pResultThread->StopThread();
}

void CSolidSBCTestManager::GetTestNames(std::vector<std::string>& vecTestNames) const
{
	std::map<std::string,CSolidSBCThread::ThreadFunction>::const_iterator iNameIter = m_mapTestNamesThreadFunc.begin();
		for(; iNameIter != m_mapTestNamesThreadFunc.end();iNameIter++)
			vecTestNames.push_back(iNameIter->first);
}

bool CSolidSBCTestManager::GetTestConfigByName(const std::string& sTestName, std::pair<std::string,CSolidSBCTestConfig*>& pairTestNameConfig) const
{
	std::map<std::string,CSolidSBCTestConfig*>::const_iterator iNameIter = m_mapTestNamesConfigs.find(sTestName);
	if(iNameIter == m_mapTestNamesConfigs.end())
		return false;
	else {
		pairTestNameConfig = *iNameIter;
		return true; }
}

bool CSolidSBCTestManager::GetTestThreadByName(const std::string& sTestName, std::pair<std::string,CSolidSBCThread::ThreadFunction>& pairTestNameThreadFunc) const
{
	std::map<std::string,CSolidSBCThread::ThreadFunction>::const_iterator iNameIter = m_mapTestNamesThreadFunc.find(sTestName);
	if(iNameIter == m_mapTestNamesThreadFunc.end())
		return false;
	else {
		pairTestNameThreadFunc = *iNameIter;
		return true; }
}

bool CSolidSBCTestManager::HasTest(const std::string& sTestName) const
{
	std::pair<std::string,CSolidSBCTestConfig*> pairTestNameConfig;
	return GetTestConfigByName(sTestName,pairTestNameConfig);
}

bool CSolidSBCTestManager::StartTestByName(const std::string& sTestName, const std::string& sConfigXml)
{
	std::pair<std::string,CSolidSBCTestConfig*> pairTestNameConfig;
	if(!GetTestConfigByName(sTestName,pairTestNameConfig))
		return false;
	pairTestNameConfig.second->SetXml(sConfigXml);

	std::pair<std::string,CSolidSBCThread::ThreadFunction> pairTestNameThreadFunc;
	if(!GetTestThreadByName(sTestName,pairTestNameThreadFunc))
		return false;

	CSolidSBCTestThread* pTestThread = new CSolidSBCTestThread(pairTestNameThreadFunc.second, pairTestNameConfig.second);
	if( !pTestThread->StartThread() )
		return false;

	m_vecRunningTestThreads.push_back(pTestThread);
	return true;
}

void CSolidSBCTestManager::RegisterTest(CSolidSBCThread::ThreadFunction pThreadFunc, CSolidSBCTestConfig* pTestConfig)
{
	std::string sTestName = pTestConfig->GetTestName();
	m_mapTestNamesThreadFunc[sTestName] = pThreadFunc;
	m_mapTestNamesConfigs   [sTestName] = pTestConfig;
}

void CSolidSBCTestManager::StopAllTests(void)
{
	std::vector<CSolidSBCTestThread*>::iterator i = m_vecRunningTestThreads.begin();
	for(;i != m_vecRunningTestThreads.end(); i++)
	{
		(*i)->StopThread();
		delete (*i);
	}
	m_vecRunningTestThreads.clear();
}

void CSolidSBCTestManager::AddResult(CSolidSBCTestResult* pResult)
{
	CSolidSBCAutoMutex lockResults(m_cResultMutex);
	m_vecTestResults.push_back(pResult);
}

void* CSolidSBCTestManager::ResultThread(void* param)
{
	CSolidSBCThread::PSSBC_THREAD_PARAM pParam   = reinterpret_cast<CSolidSBCThread::PSSBC_THREAD_PARAM>(param);
	CSolidSBCTestManager*               pManager = reinterpret_cast<CSolidSBCTestManager*>(pParam->pParam);
	CSolidSBCThread*                    pThread  = reinterpret_cast<CSolidSBCThread*>(pParam->pInstance);

	while(pThread && !pThread->ShallEnd())
	{
		std::vector<CSolidSBCTestResult*> vecResults;
		pManager->m_cResultMutex.Lock();
		vecResults = pManager->m_vecTestResults;
		pManager->m_vecTestResults.clear();
		pManager->m_cResultMutex.Unlock();

		std::vector<CSolidSBCTestResult*>::iterator i = vecResults.begin();
		for(; i != vecResults.end(); i++)
		{
			//TODO: send results to server
			delete (*i);
		}

		if(!vecResults.size())
			sleep(150);
	}
	return 0;
}
