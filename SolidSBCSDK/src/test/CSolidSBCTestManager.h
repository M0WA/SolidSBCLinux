/*
 * CSolidSBCTestManager.h
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTMANAGER_H_
#define CSOLIDSBCTESTMANAGER_H_

#include <map>
#include <string>
#include <vector>

#include "CSolidSBCTestThread.h"
#include "CSolidSBCTestConfig.h"

class CSolidSBCTestManager
{
public:
	typedef CSolidSBCTestManager* (*PTESTMANAGER_INSTANCEGETTER_FUNC)(void);

protected:
	CSolidSBCTestManager();

public:
	virtual ~CSolidSBCTestManager();

	void GetTestNames(std::vector<std::string>& vecTestNames) const;
	bool HasTest(const std::string& sTestName) const;
	bool StartTestByName(const std::string& sTestName, const std::string& sConfigXml);

protected:
	void RegisterTest(CSolidSBCThread::ThreadFunction pThreadFunc, CSolidSBCTestConfig* pTestConfig);

private:
	bool GetTestConfigByName(const std::string& sTestName, std::pair<std::string,CSolidSBCTestConfig*>& pairTestNameConfig) const;
	bool GetTestThreadByName(const std::string& sTestName, std::pair<std::string,CSolidSBCThread::ThreadFunction>& pairTestNameThreadFunc) const;

	std::map<std::string,CSolidSBCThread::ThreadFunction> m_mapTestNamesThreadFunc;
	std::map<std::string,CSolidSBCTestConfig*>            m_mapTestNamesConfigs;
	std::vector<CSolidSBCTestThread*>                     m_vecSolidSBCRunningTestThreads;
};

#endif /* CSOLIDSBCTESTMANAGER_H_ */
