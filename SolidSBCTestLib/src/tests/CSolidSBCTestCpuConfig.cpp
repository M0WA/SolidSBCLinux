/*
 * CSolidSBCTestCpuConfig.cpp
 *
 *  Created on: 09.10.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCTestCpuConfig.h"
#include "testnames.h"

CSolidSBCTestCpuConfig::CSolidSBCTestCpuConfig(const std::string& sXmlConfig)
: CSolidSBCTestConfig(SSBC_CPU_TEST_NAME,sXmlConfig)
{
}

CSolidSBCTestCpuConfig::~CSolidSBCTestCpuConfig()
{
}

void CSolidSBCTestCpuConfig::RegisterAttributes(void)
{
	RegisterAttribute("Randomize", "1");
	RegisterAttribute("MaxRand"  , "20");
	RegisterAttribute("SleepMS"  , "5.000000");
	RegisterAttribute("ThreadCnt", "2");
}

bool CSolidSBCTestCpuConfig::GetRandomize(void)
{
	bool bRandomize = false;
	GetAttributeByName<bool>("Randomize", bRandomize);
	return bRandomize;
}

unsigned int CSolidSBCTestCpuConfig::GetMaxRand(void)
{
	unsigned int nMaxRand = 0;
	GetAttributeByName<unsigned int>("MaxRand", nMaxRand);
	return nMaxRand;
}

double CSolidSBCTestCpuConfig::GetSleepMS(void)
{
	double dSleepMS = 0.0;
	GetAttributeByName<double>("SleepMS", dSleepMS);
	return dSleepMS;
}

unsigned int CSolidSBCTestCpuConfig::GetThreadCnt(void)
{
	unsigned int nThreadCnt = 0;
	GetAttributeByName<unsigned int>("ThreadCnt", nThreadCnt);
	return nThreadCnt;
}
