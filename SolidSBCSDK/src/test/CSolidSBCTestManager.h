/*
 * CSolidSBCTestManager.h
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTMANAGER_H_
#define CSOLIDSBCTESTMANAGER_H_

#include <vector>
#include <string>

class CSolidSBCTestManager
{
public:
	typedef CSolidSBCTestManager* (*PTESTMANAGER_INSTANCEGETTER_FUNC)(void);

	CSolidSBCTestManager();
	virtual ~CSolidSBCTestManager();

	void GetTestNames(std::vector<std::string>& vecTestNames);
};

#endif /* CSOLIDSBCTESTMANAGER_H_ */
