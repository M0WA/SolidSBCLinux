/*
 * CSolidSBCTestConfigHarddrive.h
 *
 *  Created on: 20.10.2011
 *      Author: Moritz Wagner
 */

#include "../../../../SolidSBCSDK/src/test/CSolidSBCTestConfig.h"

#ifndef CSOLIDSBCTESTCONFIGHARDDRIVE_H_
#define CSOLIDSBCTESTCONFIGHARDDRIVE_H_

class CSolidSBCTestConfigHarddrive : CSolidSBCTestConfig
{
public:
	CSolidSBCTestConfigHarddrive(const std::string& sXmlConfig);
	virtual ~CSolidSBCTestConfigHarddrive();

	//getter
	bool  GetRandomRead(void);
	bool  GetRandomWrite(void);
	unsigned long GetReadMax(void);
	unsigned long GetWriteMax(void);
	unsigned int GetReadWriteDelay(void);
	bool  GetTransmitData(void);

	//setter
	inline bool SetRandomRead(const bool& bRandomRead)
		{ return SetAttributeByName<bool>("RandomRead", bRandomRead); }

	inline bool SetRandomWrite(const bool& bRandomWrite)
		{ return SetAttributeByName<bool>("RandomWrite", bRandomWrite); }

	inline bool SetReadMax(const unsigned long& nReadMax)
		{ return SetAttributeByName<unsigned long>("ReadMax", nReadMax); }

	inline bool SetWriteMax(const unsigned long& nWriteMax)
		{ return SetAttributeByName<unsigned long>("WriteMax", nWriteMax); }

	inline bool SetReadWriteDelay(const unsigned int& nReadWriteDelay)
		{ return SetAttributeByName<unsigned int>("ReadWriteDelay",nReadWriteDelay ); }

	inline bool SetTransmitData(const bool& bTransmitData)
		{ return SetAttributeByName<bool>("TransmitData", bTransmitData); }

protected:
	void RegisterAttributes(void);
};

#endif /* CSOLIDSBCTESTCONFIGHARDDRIVE_H_ */
