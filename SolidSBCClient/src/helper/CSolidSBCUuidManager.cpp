/*
 * CSolidSBCUuidManager.cpp
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCUuidManager.h"

#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../defines.h"

#define _SSBC_CLIENT_UUID_MAX_RAND		0xff

CSolidSBCUuidManager::CSolidSBCUuidManager(const std::string& sUuidFile)
: m_sUuidFile(sUuidFile)
{
	if (m_sUuidFile.empty())
		m_sUuidFile = SSBC_DEFAULT_UUID_FILE;

	srand( (unsigned int)time(NULL) );

	if (!LoadUuidFromFile())
	{
		CSolidSBCUuidManager::GenerateUUID(m_sUuid);
		SaveUuidToFile();
	}
}

CSolidSBCUuidManager::~CSolidSBCUuidManager()
{
}

bool CSolidSBCUuidManager::SaveUuidToFile()
{
	std::ofstream uuidFile(m_sUuidFile.c_str());
	uuidFile << m_sUuid;
	uuidFile.close();

	return true;
}

bool CSolidSBCUuidManager::LoadUuidFromFile()
{
	std::string sUuid;
	std::ifstream uuidFile(m_sUuidFile.c_str());

	uuidFile >> sUuid;
	uuidFile.close();

	if(!sUuid.empty())
	{
		m_sUuid = sUuid;
		return true;
	}
	else
		return false;
}

void CSolidSBCUuidManager::GenerateUUID(std::string& sUuid) const
{
	char pszUUID[260];
	memset(pszUUID,0x00,sizeof(260));

	//
	// UUID version 4, specified in RFC 4122
	//
	snprintf(pszUUID, 260, "%0x%0x-%0x-%0x-%0x-%0x%0x%0x",
		rand32(), rand32(),				// generate 64-bit random number
		rand32(),						// generate 32-bit random number
		((rand32() & 0x0fff) | 0x4000), // generate 32-bit random number, form 4xxx (4 indicates UUID version)
		rand32() % 0x3fff + 0x8000,     // generate 32-bit random number, range [0x8000, 0xbfff]
		rand32(), rand32(), rand32());	// generate 96-bit random number

	sUuid = pszUUID;
}

unsigned int CSolidSBCUuidManager::rand32(void) const
{
	unsigned char nRand1 = rand() % _SSBC_CLIENT_UUID_MAX_RAND + 1;
	unsigned char nRand2 = rand() % _SSBC_CLIENT_UUID_MAX_RAND + 1;
	unsigned char nRand3 = rand() % _SSBC_CLIENT_UUID_MAX_RAND + 1;
	unsigned char nRand4 = rand() % _SSBC_CLIENT_UUID_MAX_RAND + 1;

	unsigned int nReturn = 0;
	nReturn += (unsigned int)nRand1;
	nReturn  = nReturn << 8;
	nReturn += (unsigned int)nRand2;
	nReturn  = nReturn << 8;
	nReturn += (unsigned int)nRand3;
	nReturn  = nReturn << 8;
	nReturn += (unsigned int)nRand4;

	return nReturn;
}
