/*
 * CSolidSBCTestCpuMeasureConfig.cpp
 *
 *  Created on: 09.10.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCTestConfigCpuMeasure.h"
#include "testnames.h"

CSolidSBCTestConfigCpuMeasure::CSolidSBCTestConfigCpuMeasure(const std::string& sXmlString)
: CSolidSBCTestConfig(SSBC_CPUMEASURE_TEST_NAME,sXmlString)
{
	RegisterAttributes();
	Init();
}

CSolidSBCTestConfigCpuMeasure::~CSolidSBCTestConfigCpuMeasure()
{
}

void CSolidSBCTestConfigCpuMeasure::RegisterAttributes(void)
{
	RegisterAttribute( "DivisionCnt"          , "1000");
	RegisterAttribute( "AdditionCnt"          , "1000");
	RegisterAttribute( "AutoFixMultiplier"    , "3"   );
	RegisterAttribute( "FixMultiplierTreshold", "0.5" );
	RegisterAttribute( "TransmitData"         , "1"   );
}

unsigned int CSolidSBCTestConfigCpuMeasure::GetDivisionCnt(void)
{
	unsigned int nDivisionCnt = 0;
	GetAttributeByName<unsigned int>("DivisionCnt", nDivisionCnt);
	return nDivisionCnt;
}

unsigned int CSolidSBCTestConfigCpuMeasure::GetAdditionCnt(void)
{
	unsigned int nAdditionCnt = 0;
	GetAttributeByName<unsigned int>("AdditionCnt", nAdditionCnt);
	return nAdditionCnt;
}

bool CSolidSBCTestConfigCpuMeasure::GetTransmitData(void)
{
	bool bTransmitData = false;
	GetAttributeByName<bool>("TransmitData", bTransmitData);
	return bTransmitData;
}

unsigned int CSolidSBCTestConfigCpuMeasure::GetAutoFixMultiplier(void)
{
	unsigned int nAutoFixMultiplier = 0;
	GetAttributeByName<unsigned int>("AutoFixMultiplier", nAutoFixMultiplier);
	return nAutoFixMultiplier;
}

double CSolidSBCTestConfigCpuMeasure::GetFixMultiplierTreshold(void)
{
	double dFixMultiplierTreshold = 0.0;
	GetAttributeByName<double>("FixMultiplierTreshold", dFixMultiplierTreshold);
	return dFixMultiplierTreshold;
}
