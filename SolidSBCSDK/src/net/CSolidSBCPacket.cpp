/*
 * CSolidSBCPacket.cpp
 *
 *  Created on: 14.09.2011
 *      Author: Moritz Wagner
 */

#include <string.h>

#include "../helper/CSolidSBCStringConverter.h"

#include "CSolidSBCPacket.h"
#include "CSolidSBCSocket.h"

CSolidSBCPacket::CSolidSBCPacket(const CSolidSBCPacket::SSBC_PACKET_HEADER& header, unsigned char* pcPacket)
: m_Header(header)
, m_pcPacket(pcPacket)
{
}

CSolidSBCPacket::CSolidSBCPacket()
{
}

CSolidSBCPacket::~CSolidSBCPacket()
{
	delete [] m_pcPacket;
	m_pcPacket = 0;
}

std::string CSolidSBCPacket::ToString(void) const
{
	if (!m_pcPacket)
		return "";

	std::string  sPacketUTF8;
	if ( !CSolidSBCStringConverter::GetInstance()->ConvertToUTF8((char*)m_pcPacket, m_Header.nPacketSize - sizeof(CSolidSBCPacket::SSBC_PACKET_HEADER),sPacketUTF8) )
		return "";
	return sPacketUTF8;
}

CSolidSBCPacket* CSolidSBCPacket::ReadPacket(const CSolidSBCPacket::SSBC_PACKET_HEADER& header,CSolidSBCSocket* pSocket)
{
	int nPacketSize = static_cast<int>(header.nPacketSize)- sizeof(CSolidSBCPacket::SSBC_PACKET_HEADER);
	CSolidSBCSocket::_SSBC_READ_SOCKET_PARAM readPacketParam;
	readPacketParam.nReadBytes = nPacketSize;
	readPacketParam.pCallback = 0;
	readPacketParam.pBuffer   = 0;
	readPacketParam.pcSocket  = pSocket;
	readPacketParam.timeout.tv_sec  = 3;
	readPacketParam.timeout.tv_usec = 0;

	CSolidSBCSocket::_SSBC_SOCKET_READ_STATE nState = CSolidSBCSocket::Read(&readPacketParam);
	if ((nState == CSolidSBCSocket::SSBC_SOCKET_READ_STATE_WAIT)
	 || (nState == CSolidSBCSocket::SSBC_SOCKET_READ_STATE_FAILED)
	 || (readPacketParam.nReadBytes != nPacketSize)
	   )
		return 0;

	return new CSolidSBCPacket(header,readPacketParam.pBuffer);
}

bool CSolidSBCPacket::SendPacket(CSolidSBCSocket* pSocket)
{
	int nHeaderSize       = sizeof(CSolidSBCPacket::SSBC_PACKET_HEADER);
	m_Header.nPacketSize += nHeaderSize;

	unsigned char* pcPacket = new unsigned char[m_Header.nPacketSize];
	memset(pcPacket,0,m_Header.nPacketSize);
	memcpy(pcPacket,&m_Header,nHeaderSize);
	memcpy(&pcPacket[nHeaderSize],m_pcPacket,m_Header.nPacketSize - nHeaderSize);

	pSocket->SetBlockingMode(true);
	int nSent = pSocket->Send(pcPacket,m_Header.nPacketSize);
	pSocket->SetBlockingMode(false);
	delete pcPacket;

	return (nSent == (int)m_Header.nPacketSize) ? true : false;
}
