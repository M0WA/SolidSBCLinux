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
#define _SSBC_ERR_FATAL_ERROR					"a fatal error occured. trying to shut down gracefully."
#define _SSBC_ERR_UNGRACEFUL_SHUTDOWN			"received SIGKILL, not shutting down gracefully."

//warnings
#define _SSBC_WARN_SOCKET_STILL_CONNECTED     	"socket already connected, closing previous connection"

//info
#define _SSBC_INFO_SHUTDOWN						"shutting down gracefully."
#define _SSBC_INFO_STARTING						"SolidSBCClient Linux is starting"

#endif /* SOLIDSBCLANGENGLISH_H_ */
