/*
 * CSolidSBCTestResultHarddrive.cpp
 *
 *  Created on: 20.10.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCTestResultHarddrive.h"

double CSolidSBCTestResultHarddrive::GetDuration(void)
{
	double dValue = 0.0;
	GetKeyValue( "duration", dValue , (double) 0.0 );
	return dValue;
}

unsigned long CSolidSBCTestResultHarddrive::GetByteCount(void)
{
	unsigned long ulValue = 0;
	GetKeyValue( "amountbytes", ulValue , (unsigned long) 0 );
	return ulValue;
}

unsigned long CSolidSBCTestResultHarddrive::GetWaitCount(void)
{
	unsigned long ulValue = 0;
	GetKeyValue( "wait", ulValue , (unsigned long) 0 );
	return ulValue;
}

CSolidSBCTestResultHarddrive::SSBC_TEST_HARDDRIVE_RESULT_TYPE CSolidSBCTestResultHarddrive::GetResultType(void)
{
	int nValue = 0;
	GetKeyValue( "resulttype", nValue , (int) 0 );
	return (SSBC_TEST_HARDDRIVE_RESULT_TYPE)nValue;
}
