/*
 * CSolidSBCTestResultNetPing.h
 *
 *  Created on: 13.11.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTRESULTNETPING_H_
#define CSOLIDSBCTESTRESULTNETPING_H_

#include "../../../../SolidSBCSDK/src/test/CSolidSBCTestResult.h"

class CSolidSBCTestResultNetPing : public CSolidSBCTestResult
{
public:
	CSolidSBCTestResultNetPing() : CSolidSBCTestResult("testLib_NetPingResults") {}
	virtual ~CSolidSBCTestResultNetPing() {}
};

#endif /* CSOLIDSBCTESTRESULTNETPING_H_ */
