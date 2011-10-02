/*
 * CSolidSBCUuidManager.h
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCUUIDMANAGER_H_
#define CSOLIDSBCUUIDMANAGER_H_

#include <string>

class CSolidSBCUuidManager
{
public:
	CSolidSBCUuidManager(const std::string& sUuidFile);
	virtual ~CSolidSBCUuidManager();

	std::string GetUuid(void) const { return m_sUuid; }

private:
	void GenerateUUID(std::string& sUuid) const;
	unsigned int rand32(void) const;

	bool LoadUuidFromFile();
	bool SaveUuidToFile();

	std::string m_sUuid;
	std::string m_sUuidFile;
};

#endif /* CSOLIDSBCUUIDMANAGER_H_ */
