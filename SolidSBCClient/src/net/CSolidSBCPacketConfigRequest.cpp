/*
 * CSolidSBCPacketConfigRequest.cpp
 *
 *  Created on: 17.09.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCPacketConfigRequest.h"
#include <sstream>

CSolidSBCPacketConfigRequest::CSolidSBCPacketConfigRequest(const std::string& sClientName, const std::string& sUuid)
: CSolidSBCPacketXml(CSolidSBCPacket::SSBC_PACKET_TYPE_CONFIG_REQUEST)
, m_sClientName(sClientName)
, m_sUuid(sUuid)
{
	std::stringstream ssStream;
	ssStream << "<ConfigRequest>"  << std::endl;
	ssStream << "\t<ClientUUID>"   << std::endl;
	ssStream << "\t\t" << m_sUuid  << std::endl;
	ssStream << "\t</ClientUUID>"  << std::endl;
	ssStream << "\t<ComputerName>" << std::endl;
	ssStream << "\t\t" << m_sClientName << std::endl;
	ssStream << "\t</ComputerName>" << std::endl;
	ssStream << "</ConfigRequest>";
	ParseXml(ssStream.str());
}

CSolidSBCPacketConfigRequest::~CSolidSBCPacketConfigRequest()
{
}
