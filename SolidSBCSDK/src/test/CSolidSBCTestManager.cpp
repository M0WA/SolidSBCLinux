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
}

CSolidSBCTestManager::~CSolidSBCTestManager()
{
	StopAllTests();

	std::map<std::string,CSolidSBCTestConfig*>::iterator iIter = m_mapTestNamesConfigs.begin();
	for(;iIter != m_mapTestNamesConfigs.end(); iIter++)
		if(iIter->second)
			delete iIter->second;
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

int CSolidSBCTestManager::FetchResults(std::vector<CSolidSBCTestResult*>& vecTestResults)
{
	CSolidSBCAutoMutex lockResults(m_cResultMutex);
	vecTestResults = m_vecTestResults;
	m_vecTestResults.clear();
	return vecTestResults.size();
}
