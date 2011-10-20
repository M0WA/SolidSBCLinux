/*
 * CSolidSBCTestResultCpuMeasure.cpp
 *
 *  Created on: 20.10.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCTestResultCpuMeasure.h"

double CSolidSBCTestResultCpuMeasure::GetAddDuration(void)
{
	std::string sKey = "addduration";
	double dValue = 0.0;
	GetKeyValue( sKey, dValue, (double) 0.0 );
	return dValue;
}

double CSolidSBCTestResultCpuMeasure::GetDivDuration(void)
{
	std::string sKey = "divduration";
	double dValue = 0.0;
	GetKeyValue( sKey, dValue, (double) 0.0 );
	return dValue;
}

double CSolidSBCTestResultCpuMeasure::GetOverallDuration(void)
{
	std::string sKey = "overallduration";
	double dValue = 0.0;
	GetKeyValue( sKey, dValue, (double) 0.0 );
	return dValue;
}

unsigned long long CSolidSBCTestResultCpuMeasure::GetAddMultiplier(void)
{
	std::string sKey = "addmultiplier";
	unsigned long long ullValue = 0;
	GetKeyValue( sKey, ullValue, (unsigned long long) 0 );
	return ullValue;
}

unsigned long long CSolidSBCTestResultCpuMeasure::GetDivMultiplier(void)
{
	std::string sKey = "divmultiplier";
	unsigned long long ullValue = 0;
	GetKeyValue( sKey, ullValue, (unsigned long long) 0 );
	return ullValue;
}
