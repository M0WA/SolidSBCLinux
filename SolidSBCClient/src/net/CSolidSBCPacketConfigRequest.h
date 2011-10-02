/*
 * CSolidSBCPacketConfigRequest.h
 *
 *  Created on: 17.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCPACKETCONFIGREQUEST_H_
#define CSOLIDSBPACKETCCONFIGREQUEST_H_

#include <string>

#include "CSolidSBCPacketXml.h"

class CSolidSBCPacketConfigRequest : public CSolidSBCPacketXml
{
public:
	CSolidSBCPacketConfigRequest(const std::string& sClientName, const std::string& sUuid);
	virtual ~CSolidSBCPacketConfigRequest();

	void GetClientUUID(std::string& sClientUUID)   { sClientUUID   = m_sUuid; }
	void GetClientName(std::string& sComputerName) { sComputerName = m_sClientName; }

private:
	std::string m_sClientName;
	std::string m_sUuid;
};

#endif /* CSOLIDSBCPACKETCONFIGREQUEST_H_ */
