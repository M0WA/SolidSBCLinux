/*
 * CSolidSBCPacketXml.h
 *
 *  Created on: 17.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCPACKETXML_H_
#define CSOLIDSBCPACKETXML_H_

#include "CSolidSBCPacket.h"

class CSolidSBCPacketXml : public CSolidSBCPacket
{
public:
	CSolidSBCPacketXml(const CSolidSBCPacket::SSBC_PACKET_TYPE nType);
	virtual ~CSolidSBCPacketXml();

protected:
	bool ParseXml(const std::string sXmlString);

private:
	std::string m_sXmlString;
};

#endif /* CSOLIDSBCPACKETXML_H_ */
