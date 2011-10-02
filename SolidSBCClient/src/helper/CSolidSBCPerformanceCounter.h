/*
 * CSolidSBCPerformanceCounter.h
 *
 *  Created on: 20.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCPERFORMANCECOUNTER_H_
#define CSOLIDSBCPERFORMANCECOUNTER_H_

#include <string.h>
#include <iostream>
#include <sys/time.h>

class CSolidSBCPerformanceCounter
{
public:
	CSolidSBCPerformanceCounter();
	virtual ~CSolidSBCPerformanceCounter();

	void   Start(void);
	double Stop(void);

private:
	timeval startval;
	timeval endval;
};

#endif /* CSOLIDSBCPERFORMANCECOUNTER_H_ */
