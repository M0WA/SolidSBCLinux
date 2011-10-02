/*
 * CSolidSBCPacket.h
 *
 *  Created on: 14.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCPACKET_H_
#define CSOLIDSBCPACKET_H_

#include "CSolidSBCSocket.h"
#include <string>

class CSolidSBCPacket
{
public:
	typedef enum SSBC_PACKET_TYPE {
		//not used
		SSBC_PACKET_TYPE_UNKNOWN          = 0,

		//config packets
		SSBC_PACKET_TYPE_CONFIG_REQUEST   = 1,
		SSBC_PACKET_TYPE_CONFIG_RESPONSE  = 2,
		SSBC_PACKET_TYPE_CONFIG           = 3,

		//result packets
		SSBC_PACKET_TYPE_RESULT_REQUEST   = 4,
		SSBC_PACKET_TYPE_RESULT_RESPONSE  = 5,
		SSBC_PACKET_TYPE_RESULT           = 6,

		//end marker for this typedef
		SSBC_PACKET_TYPE_MAX,
	} *PSSBC_PACKET_TYPE;

	typedef struct SSBC_PACKET_HEADER {
		unsigned int     nPacketSize;
		SSBC_PACKET_TYPE nType;
		unsigned int     nReserved;
		unsigned int     nCheckSum;
	}*PSSBC_PACKET_HEADER;

	~CSolidSBCPacket();

	bool SendPacket(CSolidSBCSocket* pSocket);

	std::string      ToString     (void) const;
	SSBC_PACKET_TYPE GetPacketType(void) const { return m_Header.nType; }

	static CSolidSBCPacket* ReadPacket(const CSolidSBCPacket::SSBC_PACKET_HEADER& header, CSolidSBCSocket* pSocket);

protected:
	CSolidSBCPacket();

	CSolidSBCPacket::SSBC_PACKET_HEADER m_Header;
	unsigned char*                      m_pcPacket;


private:
	CSolidSBCPacket(const CSolidSBCPacket::SSBC_PACKET_HEADER& header, unsigned char* pcPacket);
};

#endif /* CSOLIDSBCPACKET_H_ */
