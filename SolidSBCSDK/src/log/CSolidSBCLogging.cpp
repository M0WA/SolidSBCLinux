/*
 * CSolidSBCLogging.cpp
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#include <iostream>

#include <time.h>
#include <string.h>

#include "CSolidSBCLogging.h"
CSolidSBCLogging g_cLogging;

CSolidSBCLogging::CSolidSBCLogging(const _SSBC_LOG_LEVEL nLogLevel)
: m_sLogFile("")
, m_pFile(0)
, m_bLogStdOut(true)
, m_nLogLevel(nLogLevel)
{
}

CSolidSBCLogging::CSolidSBCLogging(const std::string& sLogFile, const _SSBC_LOG_LEVEL nLogLevel, const bool bLogStdOut)
: m_sLogFile(sLogFile)
, m_pFile(0)
, m_bLogStdOut(bLogStdOut)
, m_nLogLevel(nLogLevel)
{
	m_pFile = new std::ofstream(m_sLogFile.c_str());
	if ( !m_pFile )
		m_bLogStdOut = true;
}

CSolidSBCLogging::~CSolidSBCLogging()
{
	if (m_pFile)
		m_pFile->close();
	delete m_pFile;
	m_pFile = NULL;
}

void CSolidSBCLogging::Log(const _SSBC_LOG_LEVEL nLevel, const std::string& sLog) const
{
	m_cMutex.Lock();

	//filter out not needed log levels
	if (nLevel > m_nLogLevel)
		return;

	//getting log entry
	std::string sEntry = AssembleLogEntry(nLevel, sLog, true);

	if( m_pFile && !m_sLogFile.empty() ) {
		m_pFile->write(sEntry.c_str(),sEntry.length());
	}

	if(m_bLogStdOut || !m_pFile) {
		//print to std out
		std::cout << sEntry << std::endl;
	}

	m_cMutex.Unlock();
}

std::string CSolidSBCLogging::AssembleLogEntry(const _SSBC_LOG_LEVEL nLevel, const std::string& sLog, const bool bLogTime) const
{
	std::string sEntry;

	//add time if needed
	if(bLogTime)
	{
		//assemble timestring
		time_t rawtime;
		struct tm * timeinfo;
		char buffer [256];
		memset(buffer,0,256);
		time ( &rawtime );
		timeinfo = localtime ( &rawtime );
		strftime (buffer,256,"[%d/%m/%y-%H:%M]",timeinfo);

		//append timestring
		sEntry += buffer;
	}

	//assemble prefix for log level
	switch(nLevel)
	{
	case _SSBC_LOG_ERROR:
		sEntry += "[ERROR]";
		break;
	case _SSBC_LOG_WARN:
		sEntry += "[WARN] ";
		break;
	case _SSBC_LOG_INFO:
		sEntry += "[INFO] ";
		break;
	case _SSBC_LOG_DEBUG:
		sEntry += "[DEBUG]";
		break;
	default:
		sEntry += "[NOTAV]";
		break;
	}
	sEntry += "\t";

	//add log message
	sEntry += sLog;
	return sEntry;
}
