/*
 * CSolidSBCTestThreadHarddrive.cpp
 *
 *  Created on: 20.10.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCTestThreadHarddrive.h"
#include "CSolidSBCTestConfigHarddrive.h"
#include "CSolidSBCTestResultHarddrive.h"

#include "../../../../SolidSBCSDK/src/thread/CSolidSBCThread.h"
#include "../../../../SolidSBCSDK/src/debug/CSolidSBCPerformanceCounter.h"

#include "../../interface/CSolidSBCTestManagerImpl.h"

#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

//TODO: disable optimizations
//#pragma optimize( "", off )

////////////////////////////////////////////////////////////////////////
//
//TODO: move these settings elsewhere, they should not be hardcoded
//
////////////////////////////////////////////////////////////////////////
//file-sizes for harddrive tests
#define SSBC_TEST_HARDDRIVE_THREAD_BLOCKSIZE_WRITE	1024 //4MB
#define SSBC_TEST_HARDDRIVE_THREAD_BLOCKSIZE_READ	1024 //4MB
//files for harddrive tests
#define SSBC_TEST_HARDDRIVE_TMP_WRITE_FILE	"/opt/SolidSBC/write.dat"
#define SSBC_TEST_HARDDRIVE_TMP_READ_FILE	"/opt/SolidSBC/read.dat"
////////////////////////////////////////////////////////////////////////

CSolidSBCTestThreadHarddrive::CSolidSBCTestThreadHarddrive()
{
}

CSolidSBCTestThreadHarddrive::~CSolidSBCTestThreadHarddrive()
{
}

void* CSolidSBCTestThreadHarddrive::ThreadFunc(void* pParam)
{
	CSolidSBCThread::PSSBC_THREAD_PARAM pThreadParam = reinterpret_cast<CSolidSBCThread::PSSBC_THREAD_PARAM>(pParam);
	CSolidSBCTestConfigHarddrive*       pTestConfig  = reinterpret_cast<CSolidSBCTestConfigHarddrive*>(pThreadParam->pParam);
	CSolidSBCThread*                    pThread      = reinterpret_cast<CSolidSBCThread*>(pThreadParam->pInstance);

	pthread_t		tHdReaderThread, tHdWriterThread;
	pthread_attr_t  HdReaderThreadAttr, HdWriterThreadAttr;

	//start reader thread
	if (pTestConfig->GetReadMax() > 0){
		pthread_attr_init(&HdReaderThreadAttr);
		pthread_attr_setdetachstate(&HdReaderThreadAttr, PTHREAD_CREATE_JOINABLE);
		pthread_create( &tHdReaderThread, &HdReaderThreadAttr, &CSolidSBCTestThreadHarddrive::ReaderThread, pThreadParam );
	}

	//start writer thread
	if (pTestConfig->GetWriteMax() > 0){
		pthread_attr_init(&HdWriterThreadAttr);
		pthread_attr_setdetachstate(&HdWriterThreadAttr, PTHREAD_CREATE_JOINABLE);
		pthread_create( &tHdWriterThread, &HdWriterThreadAttr, &CSolidSBCTestThreadHarddrive::WriterThread, pThreadParam );
	}

	//stay alive and check for end
	while (1){
		//end thread?
		if ( pThread->ShallEnd() )
			break;
		usleep(333 * 1000);
	}

	//wait for child threads
	if ( pTestConfig->GetReadMax() > 0 ){
		pthread_join (tHdReaderThread,NULL);
		pthread_attr_destroy(&HdReaderThreadAttr);}

	if ( pTestConfig->GetWriteMax() > 0 ){
		pthread_join (tHdWriterThread,NULL);
		pthread_attr_destroy(&HdWriterThreadAttr);}

	return 0;
}

void* CSolidSBCTestThreadHarddrive::ReaderThread(void* pParam)
{
	CSolidSBCThread::PSSBC_THREAD_PARAM pThreadParam = reinterpret_cast<CSolidSBCThread::PSSBC_THREAD_PARAM>(pParam);
	CSolidSBCTestConfigHarddrive*       pTestConfig  = reinterpret_cast<CSolidSBCTestConfigHarddrive*>(pThreadParam->pParam);
	CSolidSBCThread*                    pThread      = reinterpret_cast<CSolidSBCThread*>(pThreadParam->pInstance);

	unsigned long ulReadBytes = pTestConfig->GetReadMax();
	unsigned int number = 0;
	char pBytes[SSBC_TEST_HARDDRIVE_THREAD_BLOCKSIZE_READ] = {0};
	memset(pBytes,0xFE,SSBC_TEST_HARDDRIVE_THREAD_BLOCKSIZE_READ);

	bool bTransmitData           = pTestConfig->GetTransmitData();
	unsigned int nReadWriteDelay = pTestConfig->GetReadWriteDelay();
	unsigned long lReadMax       = pTestConfig->GetReadMax();
	bool bRandomRead             = pTestConfig->GetRandomRead();

	double dSeconds = 0.0f;
	CSolidSBCPerformanceCounter cntTime;

	//start measuring
	cntTime.Start();

	int hFile = open( SSBC_TEST_HARDDRIVE_TMP_READ_FILE, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH  );
	if ( hFile == -1 ) {
		//could not open file
		return (void*)1;}

	unsigned long ulBytesWritten = 0, ulWriteBytesStep = SSBC_TEST_HARDDRIVE_THREAD_BLOCKSIZE_READ;
	for (unsigned long i = 0; i <= ulReadBytes; i++){

		if ( (ulReadBytes - ulBytesWritten) < SSBC_TEST_HARDDRIVE_THREAD_BLOCKSIZE_READ ){
			ulWriteBytesStep = (ulReadBytes - ulBytesWritten);}

		write(hFile,pBytes,ulWriteBytesStep);
		ulBytesWritten += ulWriteBytesStep;}

	close(hFile);

	//stop measuring
	dSeconds = cntTime.Stop();

	//send result
	if ( bTransmitData )
	{
		CSolidSBCTestResultHarddrive* pResult = new CSolidSBCTestResultHarddrive();
		pResult->SetResultType(CSolidSBCTestResultHarddrive::SSBC_TEST_HARDDRIVE_RESULT_TYPE_READ_INIT);
		pResult->SetByteCount(ulReadBytes);
		pResult->SetWaitCount(nReadWriteDelay);
		pResult->SetDuration(dSeconds);
		CSolidSBCTestManagerImpl::GetInstance()->AddResult(pResult);
	}

	while ( !pThread->ShallEnd() )
	{
		double dSeconds = 0;
		CSolidSBCPerformanceCounter cntTime;

		if ( bRandomRead ) {
			rand_r( &number );
			ulReadBytes = number % (lReadMax+1);}

		//start measuring
		cntTime.Start();

		hFile = open( SSBC_TEST_HARDDRIVE_TMP_READ_FILE, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
		unsigned int nRead = 0;
		do {
			//read file
			nRead = read(hFile,pBytes,SSBC_TEST_HARDDRIVE_THREAD_BLOCKSIZE_READ);
		} while (nRead);

		close(hFile);

		//stop measuring
		dSeconds = cntTime.Stop();

		//send result
		if ( bTransmitData )
		{
			CSolidSBCTestResultHarddrive* pResult = new CSolidSBCTestResultHarddrive();
			pResult->SetResultType(CSolidSBCTestResultHarddrive::SSBC_TEST_HARDDRIVE_RESULT_TYPE_READ);
			pResult->SetByteCount(ulReadBytes);
			pResult->SetWaitCount(nReadWriteDelay);
			pResult->SetDuration(dSeconds);
			CSolidSBCTestManagerImpl::GetInstance()->AddResult(pResult);
		}

		//end thread?
		if ( pThread->ShallEnd() )
			break;

		//sleep for given interval and check every second if we should end...
		for (unsigned long i = 0; i < nReadWriteDelay; i++){
			usleep(950 * 1000);
			i++;
			if ( pThread->ShallEnd() )
				break;
		}

		//end thread?
		if ( pThread->ShallEnd() )
			break;
	}

	//delete tmp file
	remove(SSBC_TEST_HARDDRIVE_TMP_READ_FILE);
	return 0;
}

void* CSolidSBCTestThreadHarddrive::WriterThread(void* pParam)
{
	CSolidSBCThread::PSSBC_THREAD_PARAM pThreadParam = reinterpret_cast<CSolidSBCThread::PSSBC_THREAD_PARAM>(pParam);
	CSolidSBCTestConfigHarddrive*       pTestConfig  = reinterpret_cast<CSolidSBCTestConfigHarddrive*>(pThreadParam->pParam);
	CSolidSBCThread*                    pThread      = reinterpret_cast<CSolidSBCThread*>(pThreadParam->pInstance);

	unsigned long ulWriteBytes = pTestConfig->GetWriteMax();
	unsigned int number = 0;
	char pBytes[SSBC_TEST_HARDDRIVE_THREAD_BLOCKSIZE_WRITE];
	memset(pBytes,0xFE,SSBC_TEST_HARDDRIVE_THREAD_BLOCKSIZE_WRITE);

	bool bTransmitData           = pTestConfig->GetTransmitData();
	unsigned int nReadWriteDelay = pTestConfig->GetReadWriteDelay();
	bool bRandomWrite            = pTestConfig->GetRandomWrite();
	unsigned long lWriteMax      = pTestConfig->GetWriteMax();

	while ( !pThread->ShallEnd() )
	{
		if ( bRandomWrite ) {
			rand_r( &number );
			ulWriteBytes = number % (lWriteMax+1);}

		CSolidSBCPerformanceCounter cntTime;
		unsigned long ulBytesWritten = 0, ulWriteBytesStep = SSBC_TEST_HARDDRIVE_THREAD_BLOCKSIZE_WRITE;
		double dSeconds = 0;

		cntTime.Start();

		int hFile = open( SSBC_TEST_HARDDRIVE_TMP_WRITE_FILE, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
		if ( hFile == -1 ) {
			//could not open file
			return (void*)1;}

		//write file
		for (unsigned long i = 0; i <= ulWriteBytes; i++){

			// check if next step is > SSBC_TEST_HARDDRIVE_THREAD_BLOCKSIZE_WRITE
			if ( (ulWriteBytes - ulBytesWritten) < SSBC_TEST_HARDDRIVE_THREAD_BLOCKSIZE_WRITE ){
				ulWriteBytesStep = (ulWriteBytes - ulBytesWritten);}

			write(hFile,pBytes,ulWriteBytesStep);
			ulBytesWritten += ulWriteBytesStep;}

		close(hFile);

		//stop measuring
		dSeconds = cntTime.Stop();

		//send result
		if ( bTransmitData )
		{
			CSolidSBCTestResultHarddrive* pResult = new CSolidSBCTestResultHarddrive();
			pResult->SetResultType(CSolidSBCTestResultHarddrive::SSBC_TEST_HARDDRIVE_RESULT_TYPE_WRITE);
			pResult->SetByteCount(ulBytesWritten);
			pResult->SetWaitCount(nReadWriteDelay);
			pResult->SetDuration(dSeconds);
			CSolidSBCTestManagerImpl::GetInstance()->AddResult(pResult);
		}

		//end thread?
		if ( pThread->ShallEnd() )
			break;

		//sleep for given interval and check every second if we should end...
		for (unsigned long i = 0; i < nReadWriteDelay; i++){

			usleep(900 * 1000);
			i++;

			//end thread?
			if ( pThread->ShallEnd() )
				break;
		}

		//end thread?
		if ( pThread->ShallEnd() )
			break;
	}

	//delete tmp file
	remove(SSBC_TEST_HARDDRIVE_TMP_WRITE_FILE);
	return 0;
}

//#pragma optimize( "", on )
