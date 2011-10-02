/*
 * CSolidSBCDebugging.h
 *
 *  Created on: 20.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCDEBUGGING_H_
#define CSOLIDSBCDEBUGGING_H_

#include <string>

class CSolidSBCDebugging
{
public:
	CSolidSBCDebugging();
	~CSolidSBCDebugging();

	static std::string GetBacktrace();

	//not needed
	//static int         GetPID() {return getpid();}
};

#endif /* CSOLIDSBCDEBUGGING_H_ */
