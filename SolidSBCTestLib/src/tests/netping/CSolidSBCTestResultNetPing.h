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

	unsigned int GetRTTDurationDuration(void);
	inline void SetRTTDurationDuration(unsigned int nRTTDurationDuration) { SetKeyValue( "rtt_duration", nRTTDurationDuration); }

	unsigned long GetICMPOpts(void);
	inline void SetICMPOpts(unsigned long ulICMPOpts) { SetKeyValue( "icmp_opts", ulICMPOpts); }
};

#endif /* CSOLIDSBCTESTRESULTNETPING_H_ */
