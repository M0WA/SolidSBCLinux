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

protected:
	void RegisterAttributes(void);
};

#endif /* CSOLIDSBCTESTCONFIGNETTCP_H_ */
