/*
 * CSolidSBCTestThreadNetPing.h
 *
 *  Created on: 13.11.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTTHREADNETPING_H_
#define CSOLIDSBCTESTTHREADNETPING_H_

#include <string>

class CPing
{
public:
	CPing(void);
	~CPing(void);
	bool Ping( std::string strHost, unsigned int nTTL, unsigned int nPayloadSize );

private:
	bool CatchReplyPacket(int nSock, unsigned int nTTL);
	unsigned short in_cksum(unsigned short *addr, int len);
};

class CSolidSBCTestThreadNetPing
{
public:
	CSolidSBCTestThreadNetPing() {}
	virtual ~CSolidSBCTestThreadNetPing() {}

	static void* ThreadFunc(void*);
};

#endif /* CSOLIDSBCTESTTHREADNETPING_H_ */
