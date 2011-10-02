/*
 * CSolidSBCTestConfig.h
 *
 *  Created on: 13.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCTESTCONFIG_H_
#define CSOLIDSBCTESTCONFIG_H_

#include <string>
#include <map>

#include "../helper/CSolidSBCXmlFile.h"

class CSolidSBCTestConfig
{
protected:
	CSolidSBCTestConfig(const std::string& sTestName,const std::string& sXmlString);

public:
	~CSolidSBCTestConfig();

	template<class T> bool GetAttributeByName(const std::string& sAttributeName, T& value)
	{
		return m_pXmlFile->GetNodeValue<T>( m_mapAttributeXPaths[sAttributeName], value );
	}

	template<class T> bool SetAttributeByName(const std::string& sAttributeName, const T& value)
	{
		//return m_pXmlFile->SetNodeValue<T>( m_mapAttributeXPaths[sAttributeName], value );
		return false;
	}

	std::string GetTestName(void) const { return m_sTestname; };
	std::string GenerateXML(void);

	//TODO: need to implement IsValid...
	bool IsValid(void) { return true; }

	static std::string GetTestNameFromXML(const std::string& strXml);
protected:
	//register your attributes
	//by calling RegisterXPathByAttributeName for each attribute
	void RegisterAttribute(const std::string& sAttributeName, const std::string& sAttributeDefault = "0");
	void Init(void);

private:
	void RegisterXPathByAttributeName(const std::string& sAttributeName);
	void RegisterDefaultValueByAttributeName(const std::string& sAttributeName, const std::string& sAttributeDefault);

	CSolidSBCXmlFile* m_pXmlFile;
	std::string       m_sTestname;
	std::string       m_sXmlString;

	std::map<std::string, std::string> m_mapAttributeXPaths;
	std::map<std::string, std::string> m_mapAttributeDefaults;
};

#endif /* CSOLIDSBCTESTCONFIG_H_ */
