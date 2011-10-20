/*
 * CSolidSBCTestThreadMemory.h
 *
 *  Created on: 08.10.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTTHREADMEMORY_H_
#define CSOLIDSBCTESTTHREADMEMORY_H_

class CSolidSBCTestThreadMemory
{
public:
	CSolidSBCTestThreadMemory();
	virtual ~CSolidSBCTestThreadMemory();

	static void* ThreadFunc(void*);
};

#endif /* CSOLIDSBCTESTTHREADMEMORY_H_ */
