/*
 * CSolidSBCPacketResultRequest.h
 *
 *  Created on: 20.10.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCPACKETRESULTREQUEST_H_
#define CSOLIDSBCPACKETRESULTREQUEST_H_

#include "../net/CSolidSBCPacketXml.h"
#include <string>

class CSolidSBCPacketResultRequest : public CSolidSBCPacketXml
{
public:
	CSolidSBCPacketResultRequest(const std::string& strComputerName,const std::string& strClientUUID);
	~CSolidSBCPacketResultRequest(void);

	void GetClientUUID(std::string& sClientUUID)   { sClientUUID   = m_sClientUUID;   }
	void GetClientName(std::string& sComputerName) { sComputerName = m_sComputerName; }

private:
	std::string m_sClientUUID;
	std::string m_sComputerName;

};

#endif /* CSOLIDSBCPACKETRESULTREQUEST_H_ */
