/*
 * CSolidSBCTestCpuMeasureConfig.h
 *
 *  Created on: 09.10.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTCONFIGCPUMEASURE_H_
#define CSOLIDSBCTESTCONFIGCPUMEASURE_H_

#include "../../../../SolidSBCSDK/src/test/CSolidSBCTestConfig.h"

class CSolidSBCTestConfigCpuMeasure : CSolidSBCTestConfig
{
public:
	CSolidSBCTestConfigCpuMeasure(const std::string& sXmlString = "");
	virtual ~CSolidSBCTestConfigCpuMeasure();

	unsigned int GetDivisionCnt(void);
	unsigned int GetAdditionCnt(void);
	bool         GetTransmitData(void);
	unsigned int GetAutoFixMultiplier(void);
	double       GetFixMultiplierTreshold(void);

protected:
	void RegisterAttributes(void);
};

#endif /* CSOLIDSBCTESTCONFIGCPUMEASURE_H_ */
