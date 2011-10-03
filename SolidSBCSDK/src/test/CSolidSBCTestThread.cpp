/*
 * CSolidSBCTestThread.cpp
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCTestThread.h"

CSolidSBCTestThread::CSolidSBCTestThread(CSolidSBCThread::ThreadFunction pThreadFunc, CSolidSBCTestConfig* pTestConfig)
: CSolidSBCThread(pThreadFunc,pTestConfig,false)
{
}

CSolidSBCTestThread::~CSolidSBCTestThread()
{
}
