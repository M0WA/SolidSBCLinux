/*
 * CSolidSBCTestCpuConfig.h
 *
 *  Created on: 09.10.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTCPUCONFIG_H_
#define CSOLIDSBCTESTCPUCONFIG_H_

#include "../../../SolidSBCSDK/src/test/CSolidSBCTestConfig.h"

class CSolidSBCTestCpuConfig : CSolidSBCTestConfig
{
public:
	CSolidSBCTestCpuConfig(const std::string& sXmlConfig = "");
	virtual ~CSolidSBCTestCpuConfig();

	bool         GetRandomize(void);
	unsigned int GetMaxRand(void);
	double       GetSleepMS(void);
	unsigned int GetThreadCnt(void);

protected:
	void RegisterAttributes(void);
};

#endif /* CSOLIDSBCTESTCPUCONFIG_H_ */
