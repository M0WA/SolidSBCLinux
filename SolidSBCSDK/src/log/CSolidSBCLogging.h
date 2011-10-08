/*
 * CSolidSBCLogging.h
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCLOGGING_H_
#define CSOLIDSBCLOGGING_H_

#include <string>
#include <fstream>

#include "../../../SolidSBCClient/src/lang/SolidSBCLang.h"
#include "../thread/CSolidSBCMutex.h"

typedef enum
{
	_SSBC_LOG_ERROR,
	_SSBC_LOG_WARN,
	_SSBC_LOG_INFO,
#ifdef _DEBUG
	_SSBC_LOG_DEBUG,
#endif
} _SSBC_LOG_LEVEL;

class CSolidSBCLogging
{
public:
	CSolidSBCLogging( const _SSBC_LOG_LEVEL nLogLevel =
#ifdef _DEBUG
			_SSBC_LOG_DEBUG
#else
			_SSBC_LOG_WARN
#endif
			);

	CSolidSBCLogging(const std::string& sLogFile,
			const _SSBC_LOG_LEVEL nLogLevel =
#ifdef _DEBUG
			_SSBC_LOG_DEBUG,
#else
			_SSBC_LOG_WARN,
#endif
			const bool bLogStdOut = false);

	virtual ~CSolidSBCLogging();

	void Log(const _SSBC_LOG_LEVEL nLevel, const std::string& sLog) const;

	void SetLogFile (const std::string& sLogFile)     {m_cMutex.Lock(); m_sLogFile  = sLogFile;  m_cMutex.Unlock();}
	void SetLogLevel(const _SSBC_LOG_LEVEL nLogLevel) {m_cMutex.Lock(); m_nLogLevel = nLogLevel; m_cMutex.Unlock();}

private:
	std::string AssembleLogEntry(const _SSBC_LOG_LEVEL nLevel, const std::string& sLog, const bool bLogTime = true) const;

	std::string 	m_sLogFile;
	std::ofstream*  m_pFile;
	bool        	m_bLogStdOut;
	_SSBC_LOG_LEVEL m_nLogLevel;

	mutable CSolidSBCMutex m_cMutex;
};

extern CSolidSBCLogging g_cLogging;

#endif /* CSOLIDSBCLOGGING_H_ */

