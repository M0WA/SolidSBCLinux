/*
 * CSolidSBCHostName.h
 *
 *  Created on: 19.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCHOSTNAME_H_
#define CSOLIDSBCHOSTNAME_H_

#include <string>

class CSolidSBCHostName
{
public:
	CSolidSBCHostName();
	virtual ~CSolidSBCHostName();

	static std::string GetHostName(void);
};

#endif /* CSOLIDSBCHOSTNAME_H_ */
