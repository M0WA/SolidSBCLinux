/*
 * CSolidSBCPacketTestResult.cpp
 *
 *  Created on: 20.10.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCPacketTestResult.h"

#include <string>

CSolidSBCPacketTestResult::CSolidSBCPacketTestResult(CSolidSBCTestResult* pResult)
: CSolidSBCPacketXml(SSBC_PACKET_TYPE_RESULT)
{
	std::string sXmlPacket =
		"<TestResult>\n"
		"\t" + pResult->ToSQL() +
		"</TestResult>";
	ParseXml(sXmlPacket);

}

CSolidSBCPacketTestResult::~CSolidSBCPacketTestResult()
{
}
