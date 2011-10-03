/*
 * CSolidSBCTestManager.cpp
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCTestManager.h"

CSolidSBCTestManager::CSolidSBCTestManager()
{
}

CSolidSBCTestManager::~CSolidSBCTestManager()
{
	std::map<std::string,CSolidSBCTestConfig*>::iterator iIter = m_mapTestNamesConfigs.begin();
	for(;iIter != m_mapTestNamesConfigs.end(); iIter++)	{
		if(iIter->second)
			delete iIter->second;
	}
}

void CSolidSBCTestManager::GetTestNames(std::vector<std::string>& vecTestNames) const
{
	std::map<std::string,CSolidSBCThread::ThreadFunction>::const_iterator iNameIter = m_mapTestNamesThreadFunc.begin();
		for(; iNameIter != m_mapTestNamesThreadFunc.end();iNameIter++)
			vecTestNames.push_back(iNameIter->first);
}

bool CSolidSBCTestManager::GetTestByName(const std::string& sTestName, std::pair<std::string,CSolidSBCTestConfig*>& pairTestNameConfig) const
{
	std::map<std::string,CSolidSBCTestConfig*>::const_iterator iNameIter = m_mapTestNamesConfigs.begin();
	for(; iNameIter != m_mapTestNamesConfigs.end();iNameIter++)
		if(!iNameIter->first.compare(sTestName))
			return true;
	return false;
}

bool CSolidSBCTestManager::HasTest(const std::string& sTestName) const
{
	std::pair<std::string,CSolidSBCTestConfig*> pairTestNameConfig;
	return GetTestByName(sTestName,pairTestNameConfig);
}

bool CSolidSBCTestManager::StartTestByName(const std::string& sTestName, const std::string& sConfigXml)
{
	std::pair<std::string,CSolidSBCTestConfig*> pairTestNameConfig;
	if(!GetTestByName(sTestName,pairTestNameConfig))
		return false;

	pairTestNameConfig.second->SetXml(sConfigXml);

	//TODO: start test thread
	return false;
}

void CSolidSBCTestManager::RegisterTest(CSolidSBCThread::ThreadFunction pThreadFunc, CSolidSBCTestConfig* pTestConfig)
{
	std::string sTestName = pTestConfig->GetTestName();
	m_mapTestNamesThreadFunc[sTestName] = pThreadFunc;
	m_mapTestNamesConfigs   [sTestName] = pTestConfig;
}
