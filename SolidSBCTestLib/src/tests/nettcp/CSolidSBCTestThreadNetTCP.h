/*
 * CSolidSBCTestThreadNetTCP.h
 *
 *  Created on: 13.11.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTTHREADNETTCP_H_
#define CSOLIDSBCTESTTHREADNETTCP_H_

class CSolidSBCTestThreadNetTCP
{
public:
	CSolidSBCTestThreadNetTCP() {}
	virtual ~CSolidSBCTestThreadNetTCP() {}

	static void* ThreadFunc(void*);
};

#endif /* CSOLIDSBCTESTTHREADNETTCP_H_ */
