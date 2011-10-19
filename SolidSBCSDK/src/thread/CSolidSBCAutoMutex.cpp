/*
 * CSolidSBCAutoMutex.cpp
 *
 *  Created on: 18.10.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCAutoMutex.h"

CSolidSBCAutoMutex::CSolidSBCAutoMutex(CSolidSBCMutex& mutex)
: m_mutex(mutex)
{
	m_mutex.Lock();
}

CSolidSBCAutoMutex::~CSolidSBCAutoMutex()
{
	m_mutex.Unlock();
}
