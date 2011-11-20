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
}
