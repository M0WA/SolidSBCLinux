/*
 * CSolidSBCTestThreadNetPing.h
 *
 *  Created on: 13.11.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTTHREADNETPING_H_
#define CSOLIDSBCTESTTHREADNETPING_H_

class CSolidSBCTestThreadNetPing {
public:
	CSolidSBCTestThreadNetPing() {}
	virtual ~CSolidSBCTestThreadNetPing() {}

	static void* ThreadFunc(void*);
};

#endif /* CSOLIDSBCTESTTHREADNETPING_H_ */
