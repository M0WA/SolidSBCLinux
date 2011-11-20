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
}
