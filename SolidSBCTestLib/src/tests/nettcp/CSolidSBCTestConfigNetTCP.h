/*
 * CSolidSBCTestConfigNetTCP.h
 *
 *  Created on: 13.11.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTCONFIGNETTCP_H_
#define CSOLIDSBCTESTCONFIGNETTCP_H_

#include "../../../../SolidSBCSDK/src/test/CSolidSBCTestConfig.h"

class CSolidSBCTestConfigNetTCP : public CSolidSBCTestConfig
{
public:
	CSolidSBCTestConfigNetTCP(const std::string& sXmlString = "");
	virtual ~CSolidSBCTestConfigNetTCP();

	//getter
	unsigned int    GetInterval(void);
	std::string     GetHost(void);
	unsigned short  GetPort(void);
	unsigned int    GetTTL(void);
	bool            GetTransmitData(void);

	//setter
	inline bool SetInterval(const unsigned int& nInterval)
		{ return SetAttributeByName<unsigned int>("Interval", nInterval); }

	/*
	std::string strHost;
	*/

	inline bool SetPort(const unsigned short& nPort)
		{ return SetAttributeByName<unsigned short>("Port", nPort); }

	inline bool SetTTL(const unsigned int& nTTL)
		{ return SetAttributeByName<unsigned int>("TTL", nTTL); }

	inline bool SetTransmitData(const bool& bTransmitData)
		{ return SetAttributeByName<bool>("TransmitData", bTransmitData); }

protected:
	void RegisterAttributes(void);
};

#endif /* CSOLIDSBCTESTCONFIGNETTCP_H_ */
