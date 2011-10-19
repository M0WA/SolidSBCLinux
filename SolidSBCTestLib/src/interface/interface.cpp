/*
 * interface.cpp
 *
 *  Created on: 20.09.2011
 *      Author: Moritz Wagner
 */

#include "interface.h"
#include "CSolidSBCTestManagerImpl.h"

CSolidSBCTestManager* GetSolidSBCTestManager(void)
{
	return CSolidSBCTestManagerImpl::GetInstance();
}
