/*
 * CSolidSBCTestConfigNetPing.cpp
 *
 *  Created on: 13.11.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCTestConfigNetPing.h"
#include "../testnames.h"

CSolidSBCTestConfigNetPing::CSolidSBCTestConfigNetPing(const std::string& sXmlString)
: CSolidSBCTestConfig(SSBC_NETPING_TEST_NAME, sXmlString)
{
	RegisterAttributes();
}

CSolidSBCTestConfigNetPing::~CSolidSBCTestConfigNetPing()
{
}
void CSolidSBCTestConfigNetPing::RegisterAttributes(void)
{
	RegisterAttribute("Host"        , "127.0.0.1");
	RegisterAttribute("Interval"    , "60000"    );
	RegisterAttribute("TTL"         , "1000"     );
	RegisterAttribute("PayloadSize" , "32"       );
	RegisterAttribute("TransmitData", "1"        );
}

unsigned int CSolidSBCTestConfigNetPing::GetInterval(void)
{
	unsigned int nInterval = 0;
	GetAttributeByName<unsigned int>("Interval", nInterval);
	return nInterval;
}

std::string CSolidSBCTestConfigNetPing::GetHost(void)
{
	std::string strHost;
	GetAttributeByName<std::string>("Host", strHost);
	return strHost;
}

unsigned int CSolidSBCTestConfigNetPing::GetTTL(void)
{
	unsigned int nTTL = 0;
	GetAttributeByName<unsigned int>("TTL", nTTL);
	return nTTL;
}

unsigned int CSolidSBCTestConfigNetPing::GetPayloadSize(void)
{
	unsigned int nPayloadSize = 0;
	GetAttributeByName<unsigned int>("PayloadSize", nPayloadSize);
	return nPayloadSize;
}

bool CSolidSBCTestConfigNetPing::GetTransmitData(void)
{
	bool bTransmitData = false;
	GetAttributeByName<bool>("TransmitData", bTransmitData);
	return bTransmitData;
}

