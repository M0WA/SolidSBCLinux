/*
 * CSolidSBCDebugging.cpp
 *
 *  Created on: 20.09.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCDebugging.h"

#include <execinfo.h>
#include <cxxabi.h>
#include <unistd.h>
#include <stdlib.h>
#include <sstream>

CSolidSBCDebugging::CSolidSBCDebugging()
{
}

CSolidSBCDebugging::~CSolidSBCDebugging()
{
}

std::string CSolidSBCDebugging::GetBacktrace()
{
	std::string sBacktrace = "\n========== BACKTRACE BEGIN ========== \n";

	// storage array for stack trace address data
	unsigned int max_frames = 63;
	void* addrlist[max_frames+1];

	// retrieve current stack addresses
	int addrlen = backtrace(addrlist, sizeof(addrlist) / sizeof(void*));

	if (!addrlen) {
		sBacktrace += "NA\n\n";
		return sBacktrace;
	}

	// resolve addresses into strings containing "filename(function+address)",
	// this array must be free()-ed
	char** symbollist = backtrace_symbols(addrlist, addrlen);

	// allocate string which will be filled with the demangled function name
	size_t funcnamesize = 256;
	char* funcname = (char*)malloc(funcnamesize);

	// iterate over the returned symbol lines. skip the first, it is the
	// address of this function.
	for (int i = addrlen - 1; i >= 1; i--)
	{
		char *begin_name = 0, *begin_offset = 0, *end_offset = 0;

		// find parentheses and +address offset surrounding the mangled name:
		// ./module(function+0x15c) [0x8048a6d]
		for (char *p = symbollist[i]; *p; ++p)
		{
			if (*p == '(')
				begin_name = p;
			else if (*p == '+')
				begin_offset = p;
			else if (*p == ')' && begin_offset) {
				end_offset = p;
				break; }
		}

		if (begin_name && begin_offset && end_offset
			&& begin_name < begin_offset)
		{
			*begin_name++ = '\0';
			*begin_offset++ = '\0';
			*end_offset = '\0';

			std::string sFunctionName = begin_name;
			// mangled name is now in [begin_name, begin_offset) and caller
			// offset in [begin_offset, end_offset). now apply
			// __cxa_demangle():
			int status;
			char* ret = abi::__cxa_demangle(begin_name,
										  funcname, &funcnamesize, &status);
			if (status == 0) {
				funcname = ret; // use possibly realloc()-ed string
				sFunctionName = funcname;}

			//TODO: add addr2line support for backtrace
			//std::string sAddr2LineCmd    = bs_helper::BsHelper::GetFormatedString("/usr/bin/addr2line -C -e %s %p", symbollist[i], addrlist[i]);
			//std::string sAddr2LineOutput = bs_helper::BsHelper::ExecCommand(sAddr2LineCmd.c_str(), false);
			//sBacktrace += bs_helper::BsHelper::GetFormatedString("in function %s at %s (%s)", sFunctionName.c_str(), sAddr2LineOutput.c_str(), symbollist[i] );

			std::stringstream ssBacktraceEntry;
			ssBacktraceEntry << "in function " << sFunctionName << " at " << symbollist[i];
			sBacktrace += ssBacktraceEntry.str();
		}
		else
		{
			std::stringstream ssBacktraceEntry;
			ssBacktraceEntry << "in file " << symbollist[i];
			// couldn't parse the line? print the whole line.
			sBacktrace += ssBacktraceEntry.str();
		}
	}

	free(funcname);
	free(symbollist);

	sBacktrace += "\n========== BACKTRACE END ==========\n";
	return sBacktrace;
}
