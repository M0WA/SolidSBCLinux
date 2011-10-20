/*
 * CSolidSBCTestThreadCpuMeasure.h
 *
 *  Created on: 20.10.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTTHREADCPUMEASURE_H_
#define CSOLIDSBCTESTTHREADCPUMEASURE_H_

class CSolidSBCTestThreadCpuMeasure
{
public:
	CSolidSBCTestThreadCpuMeasure();
	virtual ~CSolidSBCTestThreadCpuMeasure();

	static void* ThreadFunc(void*);

private:
	static unsigned int FixMultipliers( double dCnt, unsigned int nStepCnt, unsigned long long* pullMtpl, double dFixMultiplierThreshold, unsigned int nMaxSecs );
};

#endif /* CSOLIDSBCTESTTHREADCPUMEASURE_H_ */
