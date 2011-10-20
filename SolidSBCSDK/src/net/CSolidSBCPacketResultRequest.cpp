/*
 * CSolidSBCPacketResultRequest.cpp
 *
 *  Created on: 20.10.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCPacketResultRequest.h"

CSolidSBCPacketResultRequest::CSolidSBCPacketResultRequest(const std::string& strComputerName,const std::string& strClientUUID)
: CSolidSBCPacketXml(SSBC_PACKET_TYPE_RESULT_REQUEST)
, m_sClientUUID(strClientUUID)
, m_sComputerName(strComputerName)
{
	std::string sPacketXml;
	sPacketXml =
	"<ResultRequest>\n"
	"\t<ClientUUID>\n"
	"\t\t"+m_sClientUUID+"\n"
	"\t</ClientUUID>\n"
	"\t<ComputerName>\n"
	"\t\t"+m_sComputerName+"%s\n"
	"\t</ComputerName>\n"
	"</ResultRequest>";

	ParseXml(sPacketXml);
}

CSolidSBCPacketResultRequest::~CSolidSBCPacketResultRequest(void)
{
}
