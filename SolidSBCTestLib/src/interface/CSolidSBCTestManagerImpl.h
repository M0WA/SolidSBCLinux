/*
 * CSolidSBCTestManagerImpl.h
 *
 *  Created on: 20.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTMANAGERIMPL_H_
#define CSOLIDSBCTESTMANAGERIMPL_H_

#include "../../../SolidSBCSDK/src/test/CSolidSBCTestManager.h"

class CSolidSBCTestManagerImpl : public CSolidSBCTestManager
{
public:
	CSolidSBCTestManagerImpl();
	virtual ~CSolidSBCTestManagerImpl();

	static CSolidSBCTestManagerImpl* GetInstance();
};

#endif /* CSOLIDSBCTESTMANAGERIMPL_H_ */
