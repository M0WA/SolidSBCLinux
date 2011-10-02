/*
 * CSolidSBCTestManager.h
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTMANAGER_H_
#define CSOLIDSBCTESTMANAGER_H_

#include <map>

#include "CSolidSBCTestThread.h"
#include "CSolidSBCTestConfig.h"

class CSolidSBCTestManager
{
public:
	CSolidSBCTestManager(const std::string& sLibraryPath);
	virtual ~CSolidSBCTestManager();

	void LoadTestLibraries(void);
	bool TryLoadLibrary(const std::string& sLibraryFileName, std::map<std::string,void*>& mapTestNamesThreadFuncs);

	bool StartTestFromConfig(const std::string& sConfigXml);

	static CSolidSBCTestManager* GetInstance(void);

private:
	std::map<std::string,void*> m_mapTestNamesThreadFunc;
	std::string m_sLibraryPath;
};

#endif /* CSOLIDSBCTESTMANAGER_H_ */
