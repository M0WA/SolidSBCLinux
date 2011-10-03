/*
 * CSolidSBCTestManagerImpl.cpp
 *
 *  Created on: 20.09.2011
 *      Author: Moritz Wagner
 */
#include "CSolidSBCTestManagerImpl.h"

#include "../tests/testnames.h"
#include "../tests/CSolidSBCTestConfigMemory.h"

CSolidSBCTestManagerImpl::CSolidSBCTestManagerImpl()
: CSolidSBCTestManager()
{
	RegisterTest(0,new CSolidSBCTestConfigMemory(""));
}

CSolidSBCTestManagerImpl::~CSolidSBCTestManagerImpl()
{
}
