/*
 * CSolidSBCCommandlineParser.cpp
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#include "../defines.h"
#include "CSolidSBCCommandlineParser.h"
#include "../helper/CSolidSBCLogging.h"

#include <iostream>

CSolidSBCCommandlineParser::CSolidSBCCommandlineParser()
: m_sConfigServerHost("")
, m_nConfigServerPort(SSBC_DEFAULT_CONFIG_PORT)
, m_sResultServerHost("")
, m_nResultServerPort(SSBC_DEFAULT_RESULT_PORT)
, m_sTestLibraryPath(SSBC_DEFAULT_LIBRARY_PATH)
, m_bAutoReconnect(false)
, m_sLogFile("")
, m_sUuidFile(SSBC_DEFAULT_UUID_FILE)
{
}

void CSolidSBCCommandlineParser::PrintUsage(void)
{
	cout << "mo-sys SolidSBC client v" << MAJOR_VERSION << "." << MINOR_VERSION << endl;
	cout << "commandline options (required options are marked with *)" << endl;
	cout << "/remote: ip or hostname of solidsbc server (*)" << endl;
	cout << "/cfgport: port of configuration channel default: " << SSBC_DEFAULT_CONFIG_PORT << endl;
	cout << "/dtaport: port of data channel default: " << SSBC_DEFAULT_RESULT_PORT << endl;
	cout << "/libpath: path to test libraries default: " << SSBC_DEFAULT_LIBRARY_PATH << endl;
	cout << "/logfile: file to log default: log to STDOUT" << endl;
	cout << "/uuidfile: file with uuid for client default: " << SSBC_DEFAULT_UUID_FILE << endl;
	cout << "/autoreconnect: reconnect automatically on disconnect 0/1 default: 0" << endl;
}

bool CSolidSBCCommandlineParser::ParseCommandline(const int argc, const char *argv[])
{
	//server ip
	if ( !CSolidSBCCommandlineParser::GetCmdLineParamString( string("/remote"), m_sConfigServerHost, argc, argv ) ){
		g_cLogging.Log(_SSBC_LOG_ERROR, _SSBC_ERR_REMOTE_IP_MISSING_STRING );
		return true;
	}
	m_sResultServerHost = m_sConfigServerHost;

	//data port
	if ( CSolidSBCCommandlineParser::GetCmdLineParam<short>( string("/dtaport"), m_nResultServerPort, argc, argv ) ){
		m_nResultServerPort = SSBC_DEFAULT_RESULT_PORT;	}

	//config port
	if ( CSolidSBCCommandlineParser::GetCmdLineParam<short>( string("/cfgport"), m_nConfigServerPort, argc, argv ) ){
		m_nConfigServerPort = SSBC_DEFAULT_CONFIG_PORT; }

	//path to test libraries
	if ( CSolidSBCCommandlineParser::GetCmdLineParamString( string("/libpath"), m_sTestLibraryPath, argc, argv ) ){
		m_sTestLibraryPath = SSBC_DEFAULT_LIBRARY_PATH; }

	//autoreconnect
	if ( CSolidSBCCommandlineParser::GetCmdLineParam<bool>( string("/autoreconnect"), m_bAutoReconnect, argc, argv ) ){
		m_bAutoReconnect = false;}

	//logfile
	if ( CSolidSBCCommandlineParser::GetCmdLineParamString( string("/logfile"), m_sLogFile, argc, argv ) ){
		m_sLogFile = ""; }
	else {
		g_cLogging.SetLogFile(m_sLogFile); }

	//uuid file
	if ( CSolidSBCCommandlineParser::GetCmdLineParamString( string("/uuidfile"), m_sUuidFile, argc, argv ) ){
		m_sUuidFile = SSBC_DEFAULT_UUID_FILE; }

	return false;
}
