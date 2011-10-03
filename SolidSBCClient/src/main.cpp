//============================================================================
// Name        : SolidSBCCLient.cpp
// Author      : Moritz Wagner
// Version     :
// Copyright   : Copyright Moritz Wagner
//============================================================================

#include <iostream>
#include <signal.h>

#include "defines.h"
#include "client/CSolidSBCClient.h"
#include "../../SolidSBCSDK/src/log/CSolidSBCLogging.h"
#ifdef _DEBUG
	#include "../../SolidSBCSDK/src/debug/CSolidSBCDebugging.h"
#endif

using namespace std;

volatile bool g_bEnd = false;

void SigHandler(int nSignal)
{
	switch(nSignal)
	{
	case SIGTERM:
		g_cLogging.Log(_SSBC_LOG_INFO,_SSBC_INFO_SHUTDOWN);
		CSolidSBCClient::GetInstance()->OnShutdown();
		break;

	case SIGSEGV:
	case SIGILL:
	case SIGABRT:
		g_cLogging.Log(_SSBC_LOG_ERROR,_SSBC_ERR_FATAL_ERROR);

#ifdef _DEBUG
		{
			std::string sBacktrace = CSolidSBCDebugging::GetBacktrace();
			g_cLogging.Log(_SSBC_LOG_DEBUG,"Backtrace:\n" + sBacktrace);
		}
#endif

		g_cLogging.Log(_SSBC_LOG_INFO,_SSBC_INFO_SHUTDOWN);
		CSolidSBCClient::GetInstance()->OnShutdown();
		break;

	case SIGKILL:
		g_cLogging.Log(_SSBC_LOG_ERROR,_SSBC_ERR_UNGRACEFUL_SHUTDOWN);

#ifdef _DEBUG
		{
			std::string sBacktrace = CSolidSBCDebugging::GetBacktrace();
			g_cLogging.Log(_SSBC_LOG_DEBUG,"Backtrace:\n" + sBacktrace);
		}
#endif
		break;

	default:
		break;
	}

	g_bEnd = true;

	//re-raise signal to trigger
	//default signal handler
	raise(nSignal);
}

int main(int argc, char** argv)
{
	if(!argc)
		CSolidSBCCommandlineParser::PrintUsage();
	else
	{
		struct sigaction action;
		action.sa_handler = SigHandler;
		sigemptyset (&action.sa_mask);
		action.sa_flags = 0;
		sigaction(SIGTERM,  NULL, &action);
		sigaction(SIGSEGV,  NULL, &action);
		sigaction(SIGILL,   NULL, &action);

		std::stringstream ssStream;
		ssStream << _SSBC_INFO_STARTING << " (version " << MAJOR_VERSION << "." << MINOR_VERSION << ")";
		g_cLogging.Log(_SSBC_LOG_INFO,ssStream.str());

		CSolidSBCClient client(argc,(const char**)argv);
		if ( !client.Start() )
		{
			//TODO: give an error message here or restart if autoreconnect...
			if(client.GetAutoReconnect())
			{
			}
			else
			{
				return 1;
			}
		}
		while(!g_bEnd)
			sleep(3);
	}

	return 0;
}
