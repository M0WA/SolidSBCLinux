/*
 * CSolidSBCMemoryTestConfig.cpp
 *
 *  Created on: 20.09.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCTestConfigMemory.h"
#include "testnames.h"

CSolidSBCTestConfigMemory::CSolidSBCTestConfigMemory(const std::string& sXmlString)
: CSolidSBCTestConfig(SSBC_MEMORY_TEST_NAME,sXmlString)
{
	RegisterAttributes();
	Init();
}

CSolidSBCTestConfigMemory::~CSolidSBCTestConfigMemory()
{
}

void CSolidSBCTestConfigMemory::RegisterAttributes(void)
{
	RegisterAttribute("Randomize"   , "1" );
	RegisterAttribute("MinMem"      , "1" );
	RegisterAttribute("MaxMem"      , "1048576" );
	RegisterAttribute("TransmitData", "1" );
}

bool CSolidSBCTestConfigMemory::GetRandomize(void)
{
	bool bRandomize = false;
	GetAttributeByName<bool>("Randomize", bRandomize);
	return bRandomize;
}

unsigned int CSolidSBCTestConfigMemory::GetMinMem(void)
{
	unsigned int nMinMem = 0;
	GetAttributeByName<unsigned int>("MinMem", nMinMem);
	return nMinMem;
}

unsigned int CSolidSBCTestConfigMemory::GetMaxMem(void)
{
	unsigned int nMaxMem = 0;
	GetAttributeByName<unsigned int>("MaxMem", nMaxMem);
	return nMaxMem;
}

bool CSolidSBCTestConfigMemory::GetTransmitData(void)
{
	bool bTransmitData = false;
	GetAttributeByName<bool>("TransmitData", bTransmitData);
	return bTransmitData;
}
