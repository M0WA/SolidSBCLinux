/*
 * CSolidSBCTestConfig.cpp
 *
 *  Created on: 13.09.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCTestConfig.h"

#include <sstream>

CSolidSBCTestConfig::CSolidSBCTestConfig(const std::string& sTestName,const std::string& sXmlString)
: m_pXmlFile(NULL)
, m_sTestname(sTestName)
, m_sXmlString(sXmlString)
{
	//add standard attributes
	RegisterAttribute("TestName",m_sTestname);
}

CSolidSBCTestConfig::~CSolidSBCTestConfig()
{
	delete m_pXmlFile;
	m_pXmlFile = NULL;
}

std::string CSolidSBCTestConfig::GetTestNameFromXML(const std::string& strXml)
{
	CSolidSBCXmlFile cXML(strXml);
	std::string sTestname = "";
	if ( !cXML.GetNodeValue<std::string>("/Test/TestName[1]", sTestname) )
		return "";
	return sTestname;
}

void CSolidSBCTestConfig::Init(void)
{
	if(m_pXmlFile)
		delete m_pXmlFile;

	if ( !m_sXmlString.empty() ) {
		m_pXmlFile = new CSolidSBCXmlFile(m_sXmlString); }
	else {
		m_pXmlFile = new CSolidSBCXmlFile(GenerateXML()); }
}

void CSolidSBCTestConfig::RegisterAttribute(const std::string& sAttributeName, const std::string& sAttributeDefault)
{
	RegisterXPathByAttributeName(sAttributeName);
	RegisterDefaultValueByAttributeName(sAttributeName, sAttributeDefault);
}

void CSolidSBCTestConfig::RegisterXPathByAttributeName(const std::string& sAttributeName)
{
	std::string sXPath = "/Test/" + sAttributeName +"[1]";
	m_mapAttributeXPaths[sAttributeName] = sXPath;
}

void CSolidSBCTestConfig::RegisterDefaultValueByAttributeName(const std::string& sAttributeName, const std::string& sAttributeDefault)
{
	m_mapAttributeDefaults[sAttributeName] = sAttributeDefault;
}

void CSolidSBCTestConfig::SetXml(const std::string& sXml)
{
	m_sXmlString = sXml;
	m_pXmlFile->SetXmlString(sXml);
}

std::string CSolidSBCTestConfig::GenerateXML(void)
{
	std::string sAttributesXML;
	std::map<std::string,std::string>::iterator iIter = m_mapAttributeXPaths.begin();
	for(;iIter != m_mapAttributeXPaths.end(); iIter++)
	{
		std::string sAttributeDefaultValue = m_mapAttributeDefaults[(*iIter).first];
		std::stringstream ssSingleAttribute;
		ssSingleAttribute << std::endl << "\t<" << (*iIter).first << ">" << std::endl;
		ssSingleAttribute << "\t\t" << sAttributeDefaultValue << std::endl;
		ssSingleAttribute << "\t</" << (*iIter).first << ">"  << std::endl;
		sAttributesXML += ssSingleAttribute.str();
	}

	std::stringstream ssGeneratedXML;
	ssGeneratedXML << "<Test>" << std::endl;
	ssGeneratedXML << sAttributesXML << std::endl;
	ssGeneratedXML << "</Test>";
	return ssGeneratedXML.str();
}
