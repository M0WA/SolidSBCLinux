/*
 * CSolidSBCTestManagerImpl.cpp
 *
 *  Created on: 20.09.2011
 *      Author: Moritz Wagner
 */
#include "CSolidSBCTestManagerImpl.h"

#include "../tests/testnames.h"

#include "../tests/mem/CSolidSBCTestConfigMemory.h"
#include "../tests/mem/CSolidSBCTestThreadMemory.h"

CSolidSBCTestManagerImpl g_cTestManagerImpl;

CSolidSBCTestManagerImpl::CSolidSBCTestManagerImpl()
: CSolidSBCTestManager()
{
	RegisterTest(CSolidSBCTestThreadMemory::ThreadFunc, new CSolidSBCTestConfigMemory(""));
}

CSolidSBCTestManagerImpl::~CSolidSBCTestManagerImpl()
{
}

CSolidSBCTestManagerImpl* CSolidSBCTestManagerImpl::GetInstance()
{
	return &g_cTestManagerImpl;
}
