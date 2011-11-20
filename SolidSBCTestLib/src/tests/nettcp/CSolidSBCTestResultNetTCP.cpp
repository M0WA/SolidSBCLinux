/*
 * CSolidSBCTestResultNetTCP.cpp
 *
 *  Created on: 13.11.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCTestResultNetTCP.h"

double CSolidSBCTestResultNetTCP::GetHandshakeDuration(void)
{
	std::string sKey = "handshake_duration";
	unsigned long ulValue = 0;
	GetKeyValue(sKey, ulValue, (unsigned long) 0);
	return ulValue;
}
