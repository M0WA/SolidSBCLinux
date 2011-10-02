/*
 * CSolidSBCClient.h
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCCLIENT_H_
#define CSOLIDSBCCLIENT_H_

#include "../net/CSolidSBCSocketConfig.h"
#include "../net/CSolidSBCSocketResult.h"

#include "../test/CSolidSBCTestConfig.h"
#include "../test/CSolidSBCTestManager.h"

#include "../helper/CSolidSBCUuidManager.h"
#include "../helper/CSolidSBCHostName.h"

#include "CSolidSBCCommandlineParser.h"

class CSolidSBCClient;
class CSolidSBCClient : public CSolidSBCCommandlineParser
{
public:
	CSolidSBCClient(int argc, const char** argv);
	virtual ~CSolidSBCClient();

	bool Start(void);
	void Stop(void);

	void OnConfigSuccess(const std::string& sConfigXml);
	void OnConfigError(void) const;

	void OnShutdown(void);

	std::string GetClientName(void) const { return CSolidSBCHostName::GetHostName(); };
	std::string GetUuid(void)       const { return m_pUuidManager ? m_pUuidManager->GetUuid() : ""; };

	static CSolidSBCClient* GetInstance(void);

private:
	CSolidSBCSocketConfig m_configSocket;
	CSolidSBCSocketResult m_resultSocket;

	CSolidSBCUuidManager* m_pUuidManager;
	CSolidSBCTestManager* m_pTestManager;
};

#endif /* CSOLIDSBCCLIENT_H_ */
