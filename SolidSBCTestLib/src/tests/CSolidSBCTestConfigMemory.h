/*
 * CSolidSBCMemoryTestConfig.h
 *
 *  Created on: 20.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCMEMORYTESTCONFIG_H_
#define CSOLIDSBCMEMORYTESTCONFIG_H_

#include "../../../SolidSBCSDK/src/test/CSolidSBCTestConfig.h"

class CSolidSBCTestConfigMemory : public CSolidSBCTestConfig
{
public:
	CSolidSBCTestConfigMemory(const std::string& sXmlString = "");
	~CSolidSBCTestConfigMemory();

	//getter
	bool         GetRandomize(void);
	unsigned int GetMinMem(void);
	unsigned int GetMaxMem(void);
	bool         GetTransmitData(void);

	//setter
	inline bool SetRandomize(const bool& bRandomize)
		{ return SetAttributeByName<bool>("Randomize", bRandomize); }

	inline bool SetMinMem(const unsigned int& nMinMem)
		{ return SetAttributeByName<unsigned int>("MinMem", nMinMem); }

	inline bool SetMaxMem(const unsigned int& nMaxMem)
		{ return SetAttributeByName<unsigned int>("MaxMem", nMaxMem); }

	inline bool SetTransmitData(const bool& bTransmitData)
		{ return SetAttributeByName<bool>("TransmitData", bTransmitData); }

protected:
	void RegisterAttributes(void);
};

#endif /* CSOLIDSBCMEMORYTESTCONFIG_H_ */
