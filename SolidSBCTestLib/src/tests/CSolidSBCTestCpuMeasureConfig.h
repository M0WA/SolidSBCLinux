/*
 * CSolidSBCTestCpuMeasureConfig.h
 *
 *  Created on: 09.10.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTCPUMEASURECONFIG_H_
#define CSOLIDSBCTESTCPUMEASURECONFIG_H_

#include "../../../SolidSBCSDK/src/test/CSolidSBCTestConfig.h"

class CSolidSBCTestCpuMeasureConfig : CSolidSBCTestConfig
{
public:
	CSolidSBCTestCpuMeasureConfig(const std::string& sXmlString = "");
	virtual ~CSolidSBCTestCpuMeasureConfig();

	unsigned int GetDivisionCnt(void);
	unsigned int GetAdditionCnt(void);
	bool         GetTransmitData(void);
	unsigned int GetAutoFixMultiplier(void);
	double       GetFixMultiplierTreshold(void);

protected:
	void RegisterAttributes(void);
};

#endif /* CSOLIDSBCTESTCPUMEASURECONFIG_H_ */
