/*
 * defines.h
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#ifndef DEFINES_H_
#define DEFINES_H_

#define MAJOR_VERSION 1
#define MINOR_VERSION 5

//default values

#define SSBC_DEFAULT_CONFIG_PORT 52410
#define SSBC_DEFAULT_RESULT_PORT 52411

#ifdef _DEBUG
	#define SSBC_DEFAULT_LIBRARY_PATH "/home/momo/SolidSBCLinux/SolidSBCTestLib/Debug/"
#else
	#define SSBC_DEFAULT_LIBRARY_PATH "libs/"
#endif
#define SSBC_DEFAULT_UUID_FILE    "ssbc.uuid"

#define SSBC_DEFAULT_CONFIG_TIMEOUT 15 //in seconds
#define SSBC_DEFAULT_RESULT_TIMEOUT 15 //in seconds


#define SSBC_RETRY_RESTART_COUNT_MAX 3

#endif /* DEFINES_H_ */
