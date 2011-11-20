/*
 * CSolidSBCTestConfigNetPing.h
 *
 *  Created on: 13.11.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTCONFIGNETPING_H_
#define CSOLIDSBCTESTCONFIGNETPING_H_

#include "../../../../SolidSBCSDK/src/test/CSolidSBCTestConfig.h"

class CSolidSBCTestConfigNetPing : public CSolidSBCTestConfig
{
public:
	CSolidSBCTestConfigNetPing(const std::string& sXmlString = "");
	virtual ~CSolidSBCTestConfigNetPing();

	//getter
	unsigned int GetInterval(void);
	std::string GetHost(void);
	unsigned int GetTTL(void);
	unsigned int GetPayloadSize(void);
	bool GetTransmitData(void);


	inline bool SetInterval(const unsigned int& nInterval)
		{ return SetAttributeByName<unsigned int>("Interval", nInterval); }

	/*
	std::string strHost;
	*/

	inline bool SetTTL(const unsigned int& nTTL)
		{ return SetAttributeByName<unsigned int>("TTL", nTTL); }

	inline bool SetPayloadSize(const unsigned int& nPayloadSize)
		{ return SetAttributeByName<unsigned int>("PayloadSize", nPayloadSize); }

	inline bool SetTransmitData(const bool& bTransmitData)
		{ return SetAttributeByName<bool>("TransmitData", bTransmitData); }

protected:
	void RegisterAttributes(void);
};

#endif /* CSOLIDSBCTESTCONFIGNETPING_H_ */
