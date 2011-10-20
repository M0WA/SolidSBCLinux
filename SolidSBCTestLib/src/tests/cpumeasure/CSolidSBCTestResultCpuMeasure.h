/*
 * CSolidSBCTestResultCpuMeasure.h
 *
 *  Created on: 20.10.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTRESULTCPUMEASURE_H_
#define CSOLIDSBCTESTRESULTCPUMEASURE_H_

#include "../../../../SolidSBCSDK/src/test/CSolidSBCTestResult.h"

class CSolidSBCTestResultCpuMeasure : public CSolidSBCTestResult
{
public:
	CSolidSBCTestResultCpuMeasure(void) : CSolidSBCTestResult("testLib_CPUMeasureResults") {};

	double GetAddDuration(void);
	inline void SetAddDuration(double dAddDuration) { SetKeyValue( "addduration", dAddDuration); }

	double GetDivDuration(void);
	inline void SetDivDuration(double dDivDuration) { SetKeyValue( "divduration", dDivDuration); }

	double GetOverallDuration(void);
	inline void SetOverallDuration(double dOverallDuration) { SetKeyValue( "overallduration", dOverallDuration); }

	unsigned long long GetAddMultiplier(void);
	inline void SetAddMultiplier(unsigned long long ullAddMultiplier) { SetKeyValue( "addmultiplier", ullAddMultiplier); }

	unsigned long long GetDivMultiplier(void);
	inline void SetDivMultiplier(unsigned long long ullDivMultiplier) { SetKeyValue( "divmultiplier", ullDivMultiplier); }
};

#endif /* CSOLIDSBCTESTRESULTCPUMEASURE_H_ */
