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

protected:
	void RegisterAttributes(void);
};

#endif /* CSOLIDSBCTESTCONFIGNETPING_H_ */
