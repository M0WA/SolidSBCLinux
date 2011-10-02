/*
 * CSolidSBCXmlFile.h
 *
 *  Created on: 13.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCXMLFILE_H_
#define CSOLIDSBCXMLFILE_H_

#include <string>
#include <sstream>

#include <libxml/tree.h>

using namespace std;

class CSolidSBCXmlFile
{
public:
	CSolidSBCXmlFile(const std::string& sXmlString);
	~CSolidSBCXmlFile();

	template<class Tvalue> bool GetNodeValue(const std::string& sXPath, Tvalue& value) const
	{
		std::string sValue;
		bool bSuccess = !GetNodeString(sXPath, sValue);

		if(bSuccess)
		{
			std::stringstream in;
			in << std::skipws;
			in << sValue;
			in >> value;
			return !in.bad();
		}
		return bSuccess;
	}

	template<class string> bool GetNodeValue(const std::string& sXPath, std::string& value) const
	{
		return !GetNodeString(sXPath, value);
	}

private:
	bool GetNodeString(const std::string& sXPath, std::string& value) const;

	std::string  m_sXmlString;
	xmlDocPtr    m_pXml;
};

#endif /* CSOLIDSBCXMLFILE_H_ */
