/*
 * CSolidSBCXmlFile.cpp
 *
 *  Created on: 13.09.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCXmlFile.h"
#include "../thread/CSolidSBCAutoMutex.h"

#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

CSolidSBCMutex g_cXmlMutex;


CSolidSBCXmlFile::CSolidSBCXmlFile(const std::string& sXmlString)
: m_sXmlString(sXmlString)
, m_pXml(0)
{
	xmlInitParser();
	Init();
}

CSolidSBCXmlFile::~CSolidSBCXmlFile()
{
	Cleanup();
	xmlCleanupParser();
}

void CSolidSBCXmlFile::Init()
{
	Cleanup();

	CSolidSBCAutoMutex autoMutex(g_cXmlMutex);
	m_pXml = xmlParseMemory(m_sXmlString.c_str(), m_sXmlString.size());
}

void CSolidSBCXmlFile::Cleanup()
{
	CSolidSBCAutoMutex autoMutex(g_cXmlMutex);
	if (m_pXml)
	{
		xmlFreeDoc(m_pXml);
		m_pXml = 0;
	}
}

void CSolidSBCXmlFile::SetXmlString(const std::string& sXml)
{
	m_sXmlString = sXml;
	Init();
}

bool CSolidSBCXmlFile::GetNodeString(const std::string& sXPath, std::string& value)
{
	CSolidSBCAutoMutex autoMutex(g_cXmlMutex);

    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;

    xpathCtx = xmlXPathNewContext(m_pXml);
    if(xpathCtx == 0) {
        xmlFreeDoc(m_pXml);
        return true;
    }

    /* Register namespaces from list (if any) */
    /*
    if((nsList != 0) && (register_namespaces(xpathCtx, nsList) < 0)) {
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(m_pXml);
        return "";
    }
    */

    xpathObj = xmlXPathEvalExpression((xmlChar*)sXPath.c_str(), xpathCtx);
    if(xpathObj == 0) {
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(m_pXml);
        return true;
    }

    xmlNodeSetPtr nodes = xpathObj->nodesetval;
    int size = (nodes) ? nodes->nodeNr : 0;
    for(int i = 0; i < size; ++i)
    {
    	if(nodes->nodeTab[i]->type == XML_ELEMENT_NODE && nodes->nodeTab[i]->children && nodes->nodeTab[i]->children->content )
    	{
    		//value = (char*)nodes->nodeTab[i]->name;
    		value = (char*)nodes->nodeTab[i]->children->content;
    	}
    }

    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);

	return !(size > 0);
}
