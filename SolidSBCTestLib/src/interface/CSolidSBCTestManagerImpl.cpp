/*
 * CSolidSBCTestManagerImpl.cpp
 *
 *  Created on: 20.09.2011
 *      Author: Moritz Wagner
 */
#include "CSolidSBCTestManagerImpl.h"

#include "../tests/testnames.h"

#include "../tests/cpu/CSolidSBCTestConfigCpu.h"
#include "../tests/cpu/CSolidSBCTestThreadCpu.h"

#include "../tests/cpumeasure/CSolidSBCTestConfigCpuMeasure.h"
#include "../tests/cpumeasure/CSolidSBCTestThreadCpuMeasure.h"

#include "../tests/hd/CSolidSBCTestConfigHarddrive.h"
#include "../tests/hd/CSolidSBCTestThreadHarddrive.h"

#include "../tests/mem/CSolidSBCTestConfigMemory.h"
#include "../tests/mem/CSolidSBCTestThreadMemory.h"

CSolidSBCTestManagerImpl g_cTestManagerImpl;

CSolidSBCTestManagerImpl::CSolidSBCTestManagerImpl()
: CSolidSBCTestManager()
{
	RegisterTest(CSolidSBCTestThreadCpu::ThreadFunc       , new CSolidSBCTestConfigCpu(""));
	RegisterTest(CSolidSBCTestThreadCpuMeasure::ThreadFunc, new CSolidSBCTestConfigCpuMeasure(""));
	RegisterTest(CSolidSBCTestThreadHarddrive::ThreadFunc , new CSolidSBCTestConfigHarddrive(""));
	RegisterTest(CSolidSBCTestThreadMemory::ThreadFunc    , new CSolidSBCTestConfigMemory(""));
}

CSolidSBCTestManagerImpl::~CSolidSBCTestManagerImpl()
{
}

CSolidSBCTestManagerImpl* CSolidSBCTestManagerImpl::GetInstance()
{
	return &g_cTestManagerImpl;
}
