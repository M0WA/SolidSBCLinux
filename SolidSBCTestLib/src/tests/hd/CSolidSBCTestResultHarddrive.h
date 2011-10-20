/*
 * CSolidSBCTestResultHarddrive.h
 *
 *  Created on: 20.10.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTRESULTHARDDRIVE_H_
#define CSOLIDSBCTESTRESULTHARDDRIVE_H_

#include "../../../../SolidSBCSDK/src/test/CSolidSBCTestResult.h"

class CSolidSBCTestResultHarddrive : public CSolidSBCTestResult
{
public:
	typedef enum SSBC_TEST_HARDDRIVE_RESULT_TYPE {
		SSBC_TEST_HARDDRIVE_RESULT_TYPE_READ	    = 0,
		SSBC_TEST_HARDDRIVE_RESULT_TYPE_WRITE	    = 1,
		SSBC_TEST_HARDDRIVE_RESULT_TYPE_READ_INIT   = 2
	} *PSSBC_TEST_HARDDRIVE_RESULT_TYPE;

	CSolidSBCTestResultHarddrive() : CSolidSBCTestResult("testLib_hdResults") {}
	virtual ~CSolidSBCTestResultHarddrive() {}

	double GetDuration(void);
	inline void SetDuration(double dDuration) { SetKeyValue( "duration", dDuration); }

	unsigned long GetByteCount(void);
	inline void SetByteCount(unsigned long ulBytes) { SetKeyValue( "amountbytes", ulBytes); };

	unsigned long GetWaitCount(void);
	inline void SetWaitCount(unsigned long ulBytes) { SetKeyValue( "wait", ulBytes); };

	SSBC_TEST_HARDDRIVE_RESULT_TYPE GetResultType(void);
	inline void SetResultType(SSBC_TEST_HARDDRIVE_RESULT_TYPE nType) { SetKeyValue( "resulttype", (int)nType); };
};

#endif /* CSOLIDSBCTESTRESULTHARDDRIVE_H_ */
