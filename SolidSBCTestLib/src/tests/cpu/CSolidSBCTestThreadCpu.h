/*
 * CSolidSBCTestThreadCpu.h
 *
 *  Created on: 20.10.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTTHREADCPU_H_
#define CSOLIDSBCTESTTHREADCPU_H_

class CSolidSBCTestThreadCpu
{
public:
	CSolidSBCTestThreadCpu();
	virtual ~CSolidSBCTestThreadCpu();

	static void* ThreadFunc(void*);
};

#endif /* CSOLIDSBCTESTTHREADCPU_H_ */
