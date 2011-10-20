/*
 * CSolidSBCTestResult.h
 *
 *  Created on: 18.10.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTRESULT_H_
#define CSOLIDSBCTESTRESULT_H_


#include <string>
#include <map>
#include <sstream>

class CSolidSBCTestResult
{
protected:
	CSolidSBCTestResult(const std::string& sTableName) : m_sTableName(sTableName) {};

public:
	virtual ~CSolidSBCTestResult(void) {};

	std::string ToSQL(void);

protected:
	//setter
	template <class Tvalue>
	void SetKeyValue(const std::string& sKey, const Tvalue& value)
	{
		std::stringstream sStream;
		sStream << std::fixed << value;
		m_mapColumnsValues[sKey] = sStream.str();
	}

	//getter
	template <class Tvalue>
	bool GetKeyValue(const std::string& sKey, Tvalue& Value, const Tvalue& DefaultValue)
	{
		Value = DefaultValue;

		if (!m_mapColumnsValues.count(sKey)) {
			return false; }

		std::istringstream in( m_mapColumnsValues[sKey]);
		return (in >> Value && in.eof());
	}

private:
	std::string                       m_sTableName;
	std::map<std::string,std::string> m_mapColumnsValues;
};

#endif /* CSOLIDSBCTESTRESULT_H_ */
