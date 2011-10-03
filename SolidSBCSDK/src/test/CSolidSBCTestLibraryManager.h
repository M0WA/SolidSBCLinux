/*
 * CSolidSBCTestLibraryManager.h
 *
 *  Created on: 20.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTLIBRARYMANAGER_H_
#define CSOLIDSBCTESTLIBRARYMANAGER_H_

#include <map>
#include <string>

#include "CSolidSBCTestThread.h"
#include "CSolidSBCTestConfig.h"

#include "../../../SolidSBCSDK/src/test/CSolidSBCTestManager.h"

class CSolidSBCTestLibraryManager
{
public:
	CSolidSBCTestLibraryManager(const std::string& sLibraryPath);
	virtual ~CSolidSBCTestLibraryManager();

	void UnloadAllLibraries(void);

	void LoadAllLibraries(void);
	bool TryLoadLibrary(const std::string& sLibraryFileName);

	bool StartTestFromConfig(const std::string& sConfigXml);

	static CSolidSBCTestLibraryManager* GetInstance(void);

private:
	std::map<CSolidSBCTestManager*,void*> m_mapTestManagerLibHandle;
	std::map<std::string,void*>           m_mapTestNamesThreadFunc;
	std::string                           m_sLibraryPath;
};

#endif /* CSOLIDSBCTESTLIBRARYMANAGER_H_ */
