/*
 * CSolidSBCTestLibraryManager.h
 *
 *  Created on: 20.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTLIBRARYMANAGER_H_
#define CSOLIDSBCTESTLIBRARYMANAGER_H_

#include <map>

#include "CSolidSBCTestThread.h"
#include "CSolidSBCTestConfig.h"

class CSolidSBCTestLibraryManager
{
public:
	CSolidSBCTestLibraryManager(const std::string& sLibraryPath);
	virtual ~CSolidSBCTestLibraryManager();

	void LoadTestLibraries(void);
	bool TryLoadLibrary(const std::string& sLibraryFileName, std::map<std::string,void*>& mapTestNamesThreadFuncs);

	bool StartTestFromConfig(const std::string& sConfigXml);

	static CSolidSBCTestLibraryManager* GetInstance(void);

private:
	std::map<std::string,void*> m_mapTestNamesThreadFunc;
	std::string m_sLibraryPath;
};

#endif /* CSOLIDSBCTESTLIBRARYMANAGER_H_ */
