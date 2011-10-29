/*
 * CSolidSBCTestConfigCpu.h
 *
 *  Created on: 09.10.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTCONFIGCPU_H_
#define CSOLIDSBCTESTCONFIGCPU_H_

#include "../../../../SolidSBCSDK/src/test/CSolidSBCTestConfig.h"

class CSolidSBCTestConfigCpu : public CSolidSBCTestConfig
{
public:
	CSolidSBCTestConfigCpu(const std::string& sXmlConfig = "");
	virtual ~CSolidSBCTestConfigCpu();

	bool         GetRandomize(void);
	unsigned int GetMaxRand(void);
	double       GetSleepMS(void);
	unsigned int GetThreadCnt(void);

protected:
	void RegisterAttributes(void);
};

#endif /* CSOLIDSBCTESTCONFIGCPU_H_ */
