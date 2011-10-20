/*
 * CSolidSBCPacketTestResult.h
 *
 *  Created on: 20.10.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCPacketXml.h"
#include "../test/CSolidSBCTestResult.h"

#ifndef CSOLIDSBCPACKETTESTRESULT_H_
#define CSOLIDSBCPACKETTESTRESULT_H_

class CSolidSBCPacketTestResult : public CSolidSBCPacketXml
{
public:
	CSolidSBCPacketTestResult(CSolidSBCTestResult* pResult);
	virtual ~CSolidSBCPacketTestResult();
};

#endif /* CSOLIDSBCPACKETTESTRESULT_H_ */
