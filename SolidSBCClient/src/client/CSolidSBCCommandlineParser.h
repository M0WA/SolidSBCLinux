/*
 * CSolidSBCCommandlineParser.h
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCCOMMANDLINEPARSER_H_
#define CSOLIDSBCCOMMANDLINEPARSER_H_

#include <string>
#include <sstream>


using namespace std;

class CSolidSBCCommandlineParser
{
public:
	CSolidSBCCommandlineParser();

	bool ParseCommandline(const int argc, const char *argv[]);

	static void PrintUsage(void);

	std::string GetConfigServerHost() const {return m_sConfigServerHost;}
	short       GetConfigServerPort() const {return m_nConfigServerPort;}

	std::string GetResultServerHost() const {return m_sResultServerHost;}
	short       GetResultServerPort() const {return m_nResultServerPort;}

	std::string GetTestLibraryPath()  const {return m_sTestLibraryPath;}

	bool        GetAutoReconnect()    const {return m_bAutoReconnect;}
	std::string GetLogFile()		  const {return m_sLogFile;}
	std::string GetUuidFile()		  const {return m_sUuidFile;}

private:
	std::string m_sConfigServerHost;
	short       m_nConfigServerPort;

	std::string m_sResultServerHost;
	short       m_nResultServerPort;

	std::string m_sTestLibraryPath;

	bool        m_bAutoReconnect;
	std::string m_sLogFile;
	std::string m_sUuidFile;

	template<class Tvalue>
	bool GetCmdLineParam( const std::string& strKey, Tvalue& value, const int argc, const char** argv ) const
	{
		std::string sValue;
		if ( GetCmdLineParamString(strKey, sValue, argc, argv) )
		{
			std::stringstream in;
			in << std::skipws;
			in << sValue;
			in >> value;
			return !in.bad();
		}

		return false;
	}

	bool GetCmdLineParamString(const std::string& strKey, string& strValue, const int argc, const char** argv) const
	{
		for (int i = 0; i < argc; i++)
		{
			string strTest = strKey;
			if ( ( argv[i] == strTest ) )
			{
				strValue = argv[i+1];
				return true;
			}
		}
		return false;
	}
};

#endif /* CSOLIDSBCCOMMANDLINEPARSER_H_ */
