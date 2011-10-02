/*
 * CSolidSBCSocket.h
 *
 *  Created on: 05.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCSOCKET_H_
#define CSOLIDSBCSOCKET_H_

#include <string>
#include <vector>
#include <sys/socket.h>

#include "../../../SolidSBCSDK/src/thread/CSolidSBCThread.h"

//forward declarations
class CSolidSBCPacket;
class CSolidSBCSocket;

class CSolidSBCSocket
{
	//typedefs
public:

	///////////////////////////////////////////
	//callback specific typedefs
	///////////////////////////////////////////

	typedef struct _SSBC_SOCKET_PARAM {
		_SSBC_SOCKET_PARAM()
		: pcSocket(0)
		, pCallback(0)
		{

		}

		CSolidSBCSocket*   pcSocket;
		timeval            timeout;
		void*              pCallback;
	} *_PSSBC_SOCKET_PARAM;

	///////////////////////////////////////////
	//connect specific typedefs
	///////////////////////////////////////////

	typedef enum
	{
		SSBC_SOCKET_CONNECT_STATE_SUCCESS,
		SSBC_SOCKET_CONNECT_STATE_FAILED,
		SSBC_SOCKET_CONNECT_STATE_WAIT,
	} _SSBC_SOCKET_CONNECT_STATE, *_PSSBC_SOCKET_CONNECT_STATE;

	typedef void (*OnConnectCallback)(const _SSBC_SOCKET_CONNECT_STATE nState, _PSSBC_SOCKET_PARAM pConnectParams);

	///////////////////////////////////////////
	//read specific typedefs
	///////////////////////////////////////////

	typedef enum
	{
		SSBC_SOCKET_READ_STATE_SUCCESS,
		SSBC_SOCKET_READ_STATE_FAILED,
		SSBC_SOCKET_READ_STATE_WAIT,
	} _SSBC_SOCKET_READ_STATE, *_PSSBC_SOCKET_READ_STATE;

	typedef struct _SSBC_READ_SOCKET_PARAM : CSolidSBCSocket::_SSBC_SOCKET_PARAM {

		_SSBC_READ_SOCKET_PARAM()
		: CSolidSBCSocket::_SSBC_SOCKET_PARAM()
		, nReadBytes(-1)
		, pBuffer(0)
		{
		}

		int nReadBytes;
		unsigned char* pBuffer;
	} *_PSSBC_READ_SOCKET_PARAM;

	typedef void (*OnReadCallback)(const _SSBC_SOCKET_READ_STATE nState, const _PSSBC_READ_SOCKET_PARAM pReadParams);

	///////////////////////////////////////////
	//write specific typedefs
	///////////////////////////////////////////

	typedef enum
	{
		SSBC_SOCKET_WRITE_STATE_SUCCESS,
		SSBC_SOCKET_WRITE_STATE_FAILED,
		SSBC_SOCKET_WRITE_STATE_INCOMPLETE,
	} _SSBC_SOCKET_WRITE_STATE, *_PSSBC_SOCKET_WRITE_STATE;

	///////////////////////////////////////////
	//friend classes
	///////////////////////////////////////////

	friend class CSolidSBCPacket;

protected:
	CSolidSBCSocket(const int nSocketFamily = AF_INET, const int nSocketType = SOCK_STREAM);

public:
	virtual ~CSolidSBCSocket();
	virtual void Close(void);

	virtual _SSBC_SOCKET_CONNECT_STATE Connect(const std::string& sHost, const short nPort, OnConnectCallback pCallback = 0);

protected:

	void Read(OnReadCallback pCallback, int nReadBytes = 0);
	int  Send(unsigned char* pcPacket,  int nSendBytes);

	bool IsWritable(timeval* timeout);
	bool IsWritable(const bool bBlocking = false);

	bool IsReadable(timeval* timeout);
	bool IsReadable(const bool bBlocking = false);

private:
	void SetBlockingMode( const bool bIsBlocking );

	void RegisterCallback       (ThreadFunction pFunction, _PSSBC_SOCKET_PARAM pParam, bool bAutoDelete = true);
	void RegisterConnectCallback(OnConnectCallback pCallback);
	void RegisterReadCallback   (OnReadCallback pCallback, int nReadBytes = 0);

	static void* WaitForConnectThread(_PSSBC_THREAD_PARAM param);
	static void* WaitForReadThread   (_PSSBC_THREAD_PARAM param);

	static _SSBC_SOCKET_READ_STATE Read(_PSSBC_READ_SOCKET_PARAM pParam);

	int m_nSocketFamily;
	int m_nSocketType;

	int m_hSocket;
};

#endif /* CSOLIDSBCSOCKET_H_ */
