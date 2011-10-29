/*
 * CSolidSBCClient.h
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCCLIENT_H_
#define CSOLIDSBCCLIENT_H_

#include "../../../SolidSBCSDK/src/net/CSolidSBCSocketConfig.h"
#include "../../../SolidSBCSDK/src/net/CSolidSBCSocketResult.h"

#include "../../../SolidSBCSDK/src/test/CSolidSBCTestConfig.h"
#include "../../../SolidSBCSDK/src/test/CSolidSBCTestLibraryManager.h"

#include "../helper/CSolidSBCUuidManager.h"
#include "../helper/CSolidSBCHostName.h"

#include "CSolidSBCCommandlineParser.h"

//class CSolidSBCClient;
class CSolidSBCClient : public CSolidSBCCommandlineParser
{
public:
	CSolidSBCClient(int argc, const char** argv);
	virtual ~CSolidSBCClient();

	bool Start(void);
	void Stop(void);

	void OnShutdown(void);

	std::string GetClientName(void) const { return CSolidSBCHostName::GetHostName(); };
	std::string GetUuid(void)       const { return m_pUuidManager ? m_pUuidManager->GetUuid() : ""; };

	bool CheckConnection(void);

	static CSolidSBCClient* GetInstance(void);

private:
	bool StartConfigConnection(void);
	bool StartResultConnection(void);
	bool StartTests(void);

	CSolidSBCSocketConfig m_configSocket;
	CSolidSBCSocketResult m_resultSocket;

	CSolidSBCUuidManager*        m_pUuidManager;
	CSolidSBCTestLibraryManager* m_pTestLibraryManager;
};

#endif /* CSOLIDSBCCLIENT_H_ */
