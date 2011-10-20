/*
 * CSolidSBCTestResultMemory.h
 *
 *  Created on: 18.10.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTRESULTMEMORY_H_
#define CSOLIDSBCTESTRESULTMEMORY_H_

#include "../../../../SolidSBCSDK/src/test/CSolidSBCTestResult.h"

class CSolidSBCTestResultMemory : public CSolidSBCTestResult
{
public:
	CSolidSBCTestResultMemory() : CSolidSBCTestResult("testLib_MemoryResults") {};
	virtual ~CSolidSBCTestResultMemory() {};

	double GetMallocZeroDuration(void);
	inline void SetMallocZeroDuration(double dMallocZeroDuration) { SetKeyValue( "malloczeroduration", dMallocZeroDuration); };

	unsigned long  GetByteCount(void);
	inline void SetByteCount(unsigned long ulBytes) { SetKeyValue( "bytes", ulBytes); };
};

#endif /* CSOLIDSBCTESTRESULTMEMORY_H_ */
