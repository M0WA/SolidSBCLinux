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

#include "../../../SolidSBCSDK/src/net/CSolidSBCSocketResult.h"
#include "../../../SolidSBCSDK/src/test/CSolidSBCTestManager.h"

class CSolidSBCTestLibraryManager
{
public:
	CSolidSBCTestLibraryManager(const std::string& sLibraryPath);
	virtual ~CSolidSBCTestLibraryManager();

	void SetResultConnection(CSolidSBCSocketResult* pResultSocket) {m_pResultSocket = pResultSocket;}

	void UnloadAllLibraries (void);
	void LoadAllLibraries   (void);
	bool StartTestFromConfig(const std::string& sConfigXml);
	void StopAllTests(void);

	static CSolidSBCTestLibraryManager* GetInstance(void);

private:
	static void* ResultThread(void* param);

	bool TryLoadLibrary(const std::string& sLibraryFileName);

	std::map<CSolidSBCTestManager*,void*> m_mapTestManagerLibHandle;
	std::string                           m_sLibraryPath;

	CSolidSBCThread*             m_pResultThread;

	//TODO: make m_pResultSocket thread safe
	CSolidSBCSocketResult*       m_pResultSocket;
};

#endif /* CSOLIDSBCTESTLIBRARYMANAGER_H_ */
