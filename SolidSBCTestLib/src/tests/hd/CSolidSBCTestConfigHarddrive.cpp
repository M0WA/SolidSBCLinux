/*
 * CSolidSBCTestConfigHarddrive.cpp
 *
 *  Created on: 20.10.2011
 *      Author: Moritz Wagner
 */

#include "../testnames.h"
#include "CSolidSBCTestConfigHarddrive.h"

CSolidSBCTestConfigHarddrive::CSolidSBCTestConfigHarddrive(const std::string& sXmlConfig)
: CSolidSBCTestConfig(SSBC_HARDDRIVE_TEST_NAME,sXmlConfig)
{
	RegisterAttributes();
	Init();
}

CSolidSBCTestConfigHarddrive::~CSolidSBCTestConfigHarddrive()
{
}

void CSolidSBCTestConfigHarddrive::RegisterAttributes(void)
{
	RegisterAttribute("RandomRead"    , "1"       );
	RegisterAttribute("RandomWrite"   , "1"       );
	RegisterAttribute("ReadMax"       , "10485760");
	RegisterAttribute("WriteMax"      , "10485760");
	RegisterAttribute("ReadWriteDelay", "20"      );
	RegisterAttribute("TransmitData"  , "1"       );
}

bool CSolidSBCTestConfigHarddrive::GetRandomRead(void)
{
	bool bRandomRead = false;
	GetAttributeByName<bool>("RandomRead", bRandomRead);
	return bRandomRead;
}

bool CSolidSBCTestConfigHarddrive::GetRandomWrite(void)
{
	bool bRandomWrite = false;
	GetAttributeByName<bool>("RandomWrite", bRandomWrite);
	return bRandomWrite;
}

unsigned long CSolidSBCTestConfigHarddrive::GetReadMax(void)
{
	unsigned long ulReadMax = 0;
	GetAttributeByName<unsigned long>("ReadMax", ulReadMax);
	return ulReadMax;
}

unsigned long CSolidSBCTestConfigHarddrive::GetWriteMax(void)
{
	unsigned long ulWriteMax = 0;
	GetAttributeByName<unsigned long>("WriteMax", ulWriteMax);
	return ulWriteMax;
}

unsigned int CSolidSBCTestConfigHarddrive::GetReadWriteDelay(void)
{
	unsigned int nReadWriteDelay = 0;
	GetAttributeByName<unsigned int>("ReadWriteDelay", nReadWriteDelay);
	return nReadWriteDelay;
}

bool CSolidSBCTestConfigHarddrive::GetTransmitData(void)
{
	bool bTransmitData = false;
	GetAttributeByName<bool>("TransmitData", bTransmitData);
	return bTransmitData;
}
