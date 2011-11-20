/*
 * CSolidSBCTestConfigNetTCP.cpp
 *
 *  Created on: 13.11.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCTestConfigNetTCP.h"
#include "../testnames.h"

CSolidSBCTestConfigNetTCP::CSolidSBCTestConfigNetTCP(const std::string& sXmlString)
: CSolidSBCTestConfig(SSBC_NETTCP_TEST_NAME, sXmlString)
{
	RegisterAttributes();
}

CSolidSBCTestConfigNetTCP::~CSolidSBCTestConfigNetTCP()
{
}

void CSolidSBCTestConfigNetTCP::RegisterAttributes(void)
{
	RegisterAttribute("Host", "127.0.0.1");
	RegisterAttribute("Interval", "60000");
	RegisterAttribute("Port", "80");
	RegisterAttribute("TTL", "1000");
	RegisterAttribute("TransmitData", "1");
}

unsigned int CSolidSBCTestConfigNetTCP::GetInterval(void)
{
	unsigned int nInterval = false;
	GetAttributeByName<unsigned int>("Interval", nInterval);
	return nInterval;
}

std::string CSolidSBCTestConfigNetTCP::GetHost(void)
{
	std::string strHost;
	GetAttributeByName<std::string>("Host", strHost);
	return strHost.c_str();
}

unsigned short CSolidSBCTestConfigNetTCP::GetPort(void)
{
	unsigned short nPort = 0;
	GetAttributeByName<unsigned short>("Port", nPort);
	return nPort;
}

unsigned int CSolidSBCTestConfigNetTCP::GetTTL(void)
{
	unsigned int nTTL = false;
	GetAttributeByName<unsigned int>("TTL", nTTL);
	return nTTL;
}

bool CSolidSBCTestConfigNetTCP::GetTransmitData(void)
{
	bool bTransmitData = false;
	GetAttributeByName<bool>("TransmitData", bTransmitData);
	return bTransmitData;
}
