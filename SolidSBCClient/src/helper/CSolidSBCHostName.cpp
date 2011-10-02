/*
 * CSolidSBCHostName.cpp
 *
 *  Created on: 19.09.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCHostName.h"

#include <unistd.h>
#include <string.h>

CSolidSBCHostName::CSolidSBCHostName()
{
}

CSolidSBCHostName::~CSolidSBCHostName()
{
}

std::string CSolidSBCHostName::GetHostName(void)
{
	char pszHostName[1024];
	memset(pszHostName,0,1024);
	return !gethostname(pszHostName,1024) ? pszHostName : "";
}
