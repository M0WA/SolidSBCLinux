/*
 * SolidSBCLangEnglish.h
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#ifndef SOLIDSBCLANGENGLISH_H_
#define SOLIDSBCLANGENGLISH_H_

// error descriptions
#define _SSBC_ERR_REMOTE_IP_MISSING_STRING	  	"missing required commandline argument: /remote <serverip>"
#define _SSBC_ERR_SOCKET_FAMILY_NOT_SUPPORTED 	"this socket family is not supported"
#define _SSBC_ERR_SOCKET_TYPE_NOT_SUPPORTED   	"this socket type is not supported"
#define _SSBC_ERR_NO_CREATE_SOCKET_STRING     	"could not create socket"
#define _SSBC_ERR_NO_VALID_SERVER_SPECIFIED		"could not find ip or hostname"
#define _SSBC_ERR_SOCKET_CONNECT_FAILED			"could not connect to server"
#define _SSBC_ERR_FATAL_ERROR					"a fatal error occurred. trying to shut down gracefully."
#define _SSBC_ERR_UNGRACEFUL_SHUTDOWN			"received SIGKILL, not shutting down gracefully."
#define _SSBC_ERR_INVALID_TESTLIB_DIR			"could not find test library directory"

//warnings
#define _SSBC_WARN_SOCKET_STILL_CONNECTED     	"socket already connected, closing previous connection"
#define _SSBC_WARN_COULD_NOT_FIND_TEST          "test not found: "
#define _SSBC_WARN_COULD_NOT_PARSE_TESTCONFIG   "could not parse test config xml\n"

//info
#define _SSBC_INFO_SHUTDOWN						"shutting down gracefully."
#define _SSBC_INFO_STARTING						"SolidSBCClient Linux is starting"

#endif /* SOLIDSBCLANGENGLISH_H_ */
