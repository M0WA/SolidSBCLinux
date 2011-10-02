/*
 * CSolidSBCMutex.h
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCMUTEX_H_
#define CSOLIDSBCMUTEX_H_

#include <pthread.h>

class CSolidSBCMutex
{
public:
	CSolidSBCMutex(void);
	virtual ~CSolidSBCMutex(void);

	bool Lock(void);
	bool Unlock(void);

	bool IsLocked(void) const;

private:
	volatile bool m_bIsLocked;
	pthread_mutex_t m_tMutex;
};

#endif /* CSOLIDSBCMUTEX_H_ */
