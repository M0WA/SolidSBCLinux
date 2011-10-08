/*
 * CSolidSBCTestCpuMeasureConfig.cpp
 *
 *  Created on: 09.10.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCTestCpuMeasureConfig.h"
#include "testnames.h"

CSolidSBCTestCpuMeasureConfig::CSolidSBCTestCpuMeasureConfig(const std::string& sXmlString)
: CSolidSBCTestConfig(SSBC_CPUMEASURE_TEST_NAME,sXmlString)
{
	RegisterAttributes();
	Init();
}

CSolidSBCTestCpuMeasureConfig::~CSolidSBCTestCpuMeasureConfig()
{
}

void CSolidSBCTestCpuMeasureConfig::RegisterAttributes(void)
{
	RegisterAttribute( "DivisionCnt"          , "1000");
	RegisterAttribute( "AdditionCnt"          , "1000");
	RegisterAttribute( "AutoFixMultiplier"    , "3"   );
	RegisterAttribute( "FixMultiplierTreshold", "0.5" );
	RegisterAttribute( "TransmitData"         , "1"   );
}

unsigned int CSolidSBCTestCpuMeasureConfig::GetDivisionCnt(void)
{
	unsigned int nDivisionCnt = 0;
	GetAttributeByName<unsigned int>("DivisionCnt", nDivisionCnt);
	return nDivisionCnt;
}

unsigned int CSolidSBCTestCpuMeasureConfig::GetAdditionCnt(void)
{
	unsigned int nAdditionCnt = 0;
	GetAttributeByName<unsigned int>("AdditionCnt", nAdditionCnt);
	return nAdditionCnt;
}

bool CSolidSBCTestCpuMeasureConfig::GetTransmitData(void)
{
	bool bTransmitData = false;
	GetAttributeByName<bool>("TransmitData", bTransmitData);
	return bTransmitData;
}

unsigned int CSolidSBCTestCpuMeasureConfig::GetAutoFixMultiplier(void)
{
	unsigned int nAutoFixMultiplier = 0;
	GetAttributeByName<unsigned int>("AutoFixMultiplier", nAutoFixMultiplier);
	return nAutoFixMultiplier;
}

double CSolidSBCTestCpuMeasureConfig::GetFixMultiplierTreshold(void)
{
	double dFixMultiplierTreshold = 0.0;
	GetAttributeByName<double>("FixMultiplierTreshold", dFixMultiplierTreshold);
	return dFixMultiplierTreshold;
}
