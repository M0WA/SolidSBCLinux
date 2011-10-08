/*
 * CSolidSBCTestManagerImpl.cpp
 *
 *  Created on: 20.09.2011
 *      Author: Moritz Wagner
 */
#include "CSolidSBCTestManagerImpl.h"

#include "../tests/testnames.h"

#include "../tests/CSolidSBCTestConfigMemory.h"
#include "../tests/CSolidSBCTestThreadMemory.h"

CSolidSBCTestManagerImpl::CSolidSBCTestManagerImpl()
: CSolidSBCTestManager()
{
	RegisterTest(CSolidSBCTestThreadMemory::ThreadFunc,new CSolidSBCTestConfigMemory(""));
}

CSolidSBCTestManagerImpl::~CSolidSBCTestManagerImpl()
{
}
