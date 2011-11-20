/*
 * CSolidSBCTestResultNetPing.cpp
 *
 *  Created on: 13.11.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCTestResultNetPing.h"

unsigned long CSolidSBCTestResultNetPing::GetICMPOpts(void)
{
	std::string sKey = "icmp_opts";

	unsigned long ulValue = 0;
	GetKeyValue(sKey, ulValue, (unsigned long) 0);
	return ulValue;
}

unsigned int CSolidSBCTestResultNetPing::GetRTTDurationDuration(void)
{
	std::string sKey = "rtt_duration";

	unsigned long ulValue = 0;
	GetKeyValue(sKey, ulValue, (unsigned long) 0);
	return ulValue;
}
