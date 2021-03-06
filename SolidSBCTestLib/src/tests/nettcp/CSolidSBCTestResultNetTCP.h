/*
 * CSolidSBCTestResultNetTCP.h
 *
 *  Created on: 13.11.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTRESULTNETTCP_H_
#define CSOLIDSBCTESTRESULTNETTCP_H_

#include "../../../../SolidSBCSDK/src/test/CSolidSBCTestResult.h"

class CSolidSBCTestResultNetTCP : public CSolidSBCTestResult
{
public:
	CSolidSBCTestResultNetTCP() : CSolidSBCTestResult("testlib_NetTCPResults") {}
	virtual ~CSolidSBCTestResultNetTCP() {}

	double GetHandshakeDuration(void);
	inline void SetHandshakeDuration(double dHandshakeDuration) { SetKeyValue( "handshake_duration", dHandshakeDuration); }
};

#endif /* CSOLIDSBCTESTRESULTNETTCP_H_ */
