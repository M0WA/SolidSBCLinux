/*
 * CSolidSBCMutex.cpp
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCMutex.h"

CSolidSBCMutex::CSolidSBCMutex(void)
: m_bIsLocked(false)
{
	pthread_mutex_init( &m_tMutex, NULL );
}

CSolidSBCMutex::~CSolidSBCMutex(void)
{
	if (m_bIsLocked)
		Unlock();

	pthread_mutex_destroy(&m_tMutex);
}

bool CSolidSBCMutex::Lock(void)
{
	pthread_mutex_lock( &m_tMutex );
	m_bIsLocked = true;

	return true;
}

bool CSolidSBCMutex::Unlock(void)
{
	pthread_mutex_unlock( &m_tMutex );
	m_bIsLocked = false;

	return true;
}

bool CSolidSBCMutex::IsLocked(void) const
{
	return m_bIsLocked;
}
