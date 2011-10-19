/*
 * CSolidSBCAutoMutex.h
 *
 *  Created on: 18.10.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCAUTOMUTEX_H_
#define CSOLIDSBCAUTOMUTEX_H_

#include "CSolidSBCMutex.h"

class CSolidSBCAutoMutex
{
public:
	CSolidSBCAutoMutex(CSolidSBCMutex& mutex);
	virtual ~CSolidSBCAutoMutex();

private:
	CSolidSBCMutex& m_mutex;
};

#endif /* CSOLIDSBCAUTOMUTEX_H_ */
