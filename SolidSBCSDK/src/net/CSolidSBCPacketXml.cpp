/*
 * CSolidSBCPacketXml.cpp
 *
 *  Created on: 17.09.2011
 *      Author: Moritz Wagner
 */

#include <stdlib.h>
#include <string.h>

#include "CSolidSBCPacketXml.h"
#include "../string/CSolidSBCStringConverter.h"

CSolidSBCPacketXml::CSolidSBCPacketXml(const CSolidSBCPacket::SSBC_PACKET_TYPE nType)
: CSolidSBCPacket()
{
	m_Header.nType = nType;
}

CSolidSBCPacketXml::~CSolidSBCPacketXml()
{
}

bool CSolidSBCPacketXml::ParseXml(const std::string sXmlString)
{
	m_sXmlString = sXmlString;

	char* pszOutput = 0;
	int nOutputSize = 0;
	CSolidSBCStringConverter::GetInstance()->ConvertToUTF16LE(sXmlString,&pszOutput,&nOutputSize,"UTF8");

	m_Header.nPacketSize = nOutputSize;
	m_pcPacket = new unsigned char[m_Header.nPacketSize];
	memset(m_pcPacket, 0, m_Header.nPacketSize);
	memcpy(m_pcPacket, pszOutput, m_Header.nPacketSize);
	free(pszOutput);

	return true;
}
