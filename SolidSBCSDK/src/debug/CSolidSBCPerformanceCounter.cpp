/*
 * CSolidSBCPerformanceCounter.cpp
 *
 *  Created on: 20.09.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCPerformanceCounter.h"

CSolidSBCPerformanceCounter::CSolidSBCPerformanceCounter()
{
}

CSolidSBCPerformanceCounter::~CSolidSBCPerformanceCounter()
{
}

void CSolidSBCPerformanceCounter::Start(void)
{
	gettimeofday(&startval, 0);
}

double CSolidSBCPerformanceCounter::Stop(void)
{
	gettimeofday(&endval, 0);

	double dSec          = static_cast<double>( endval.tv_sec - startval.tv_sec );
	double dMicroseconds = static_cast<double>( endval.tv_usec - startval.tv_usec );
	return ( dSec + ((dMicroseconds / 1000.0f) / 1000.0f) );
}
