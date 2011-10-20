/*
 * CSolidSBCTestResultMemory.cpp
 *
 *  Created on: 18.10.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCTestResultMemory.h"

double CSolidSBCTestResultMemory::GetMallocZeroDuration(void)
{
	std::string sKey = "malloczeroduration";

	double dValue = 0.0;
	GetKeyValue(sKey, dValue, (double) 0.0);
	return dValue;
}

unsigned long CSolidSBCTestResultMemory::GetByteCount(void)
{
	std::string sKey = "bytes";

	unsigned long ulValue = 0;
	GetKeyValue(sKey, ulValue, (unsigned long) 0);
	return ulValue;
}
