/*
 * CSolidSBCTestLibraryManager.cpp
 *
 *  Created on: 20.09.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCTestLibraryManager.h"
#include "../log/CSolidSBCLogging.h"
#include "../net/CSolidSBCPacketTestResult.h"

#include <dirent.h>
#include <dlfcn.h>
#include <vector>

CSolidSBCTestLibraryManager* g_pTestLibraryManagerInstance = 0;

CSolidSBCTestLibraryManager::CSolidSBCTestLibraryManager(const std::string& sLibraryPath)
: m_sLibraryPath(sLibraryPath)
, m_pResultSocket(0)
{
	m_pResultThread = new CSolidSBCThread((CSolidSBCThread::ThreadFunction)&CSolidSBCTestLibraryManager::ResultThread, this, true);
	m_pResultThread->StartThread();

	g_pTestLibraryManagerInstance = this;
	LoadAllLibraries();
}

CSolidSBCTestLibraryManager::~CSolidSBCTestLibraryManager()
{
	UnloadAllLibraries();
	g_pTestLibraryManagerInstance = 0;

	m_pResultThread->StopThread();
}

void CSolidSBCTestLibraryManager::UnloadAllLibraries(void)
{
	std::map<CSolidSBCTestManager*,void*>::iterator iIter =	m_mapTestManagerLibHandle.begin();
	for(;iIter != m_mapTestManagerLibHandle.end(); iIter++)
	{
		iIter->first->StopAllTests();
		dlclose(iIter->second);
	}
	m_mapTestManagerLibHandle.clear();
}

void CSolidSBCTestLibraryManager::LoadAllLibraries(void)
{
	UnloadAllLibraries();

	int nLoadedLibraries = 0;

	char pszPath[255];
	getcwd(pszPath,255);

    DIR *dir = opendir(m_sLibraryPath.c_str());
    if(dir)
    {
        struct dirent *ent;
        while((ent = readdir(dir)) != NULL)
        {
        	switch(ent->d_type)
        	{
        	case DT_REG: //is a file
				{
					std::string sLibraryFileNamePath = m_sLibraryPath + ent->d_name;
					if( TryLoadLibrary(sLibraryFileNamePath) ) {
						nLoadedLibraries++;}
				}
        		break;

        	default:
        		break;
        	}
        }

        (void)closedir(dir);
    }
    else
    {
    	g_cLogging.Log(_SSBC_LOG_ERROR,_SSBC_ERR_INVALID_TESTLIB_DIR);
    }
}

bool CSolidSBCTestLibraryManager::TryLoadLibrary(const std::string& sLibraryFileName)
{
	void *handle = dlopen (sLibraryFileName.c_str(), RTLD_NOW);
	if (!handle) {
		return false;
	}

	CSolidSBCTestManager::PTESTMANAGER_INSTANCEGETTER_FUNC GetSolidSBCTestManager =
			(CSolidSBCTestManager::PTESTMANAGER_INSTANCEGETTER_FUNC)dlsym(handle, "GetSolidSBCTestManager");

	char *error;
	if ( !GetSolidSBCTestManager || ((error = dlerror()) != NULL) ) {
		dlclose(handle);
		return false;
	}

	CSolidSBCTestManager* pTestManager = GetSolidSBCTestManager();
	if (!pTestManager){
		dlclose(handle);
		return false;
	}

	m_mapTestManagerLibHandle[pTestManager] = handle;
	return true;
}

bool CSolidSBCTestLibraryManager::StartTestFromConfig(const std::string& sConfigXml)
{
	std::string sTestName = CSolidSBCTestConfig::GetTestNameFromXML(sConfigXml);
	if(sTestName.empty())
		return false;

	std::map<CSolidSBCTestManager*,void*>::iterator iIter = m_mapTestManagerLibHandle.begin();
	for(; iIter != m_mapTestManagerLibHandle.end(); iIter++)
		if(iIter->first->HasTest(sTestName))
			return iIter->first->StartTestByName(sTestName, sConfigXml);

	return false;
}

CSolidSBCTestLibraryManager* CSolidSBCTestLibraryManager::GetInstance(void)
{
	return g_pTestLibraryManagerInstance;
}

void CSolidSBCTestLibraryManager::StopAllTests(void)
{
	std::map<CSolidSBCTestManager*,void*>::iterator iIter = m_mapTestManagerLibHandle.begin();
	for(; iIter != m_mapTestManagerLibHandle.end(); iIter++)
	{
		iIter->first->StopAllTests();
	}
}

void* CSolidSBCTestLibraryManager::ResultThread(void* param)
{
	CSolidSBCThread::PSSBC_THREAD_PARAM pParam   = reinterpret_cast<CSolidSBCThread::PSSBC_THREAD_PARAM>(param);
	CSolidSBCTestLibraryManager*        pManager = reinterpret_cast<CSolidSBCTestLibraryManager*>(pParam->pParam);
	CSolidSBCThread*                    pThread  = reinterpret_cast<CSolidSBCThread*>(pParam->pInstance);

	bool bError = false;
	while(pThread && !pThread->ShallEnd())
	{
		int nFetchedResults = 0;

		pManager->m_cResultSocketMutex.Lock();
		if(pManager->m_pResultSocket)
		{
			std::map<CSolidSBCTestManager*,void*>::iterator iIter = pManager->m_mapTestManagerLibHandle.begin();
			for(; iIter != pManager->m_mapTestManagerLibHandle.end(); iIter++)
			{
				std::vector<CSolidSBCTestResult*> vecResults;
				nFetchedResults += iIter->first->FetchResults(vecResults);

				std::vector<CSolidSBCTestResult*>::iterator i = vecResults.begin();
				for(; i != vecResults.end(); i++)
				{
					CSolidSBCTestResult* pResult = (*i);
					CSolidSBCPacketTestResult resultPacket(pResult);
					if ( !resultPacket.SendPacket(pManager->m_pResultSocket) )
					{
						pManager->m_pResultSocket->Close();
						pManager->StopAllTests();
						bError = true;
					}
					delete pResult;

					if (bError)
						break;
				}

				if (bError)
					break;
			}

			if (bError)
				break;
		}
		pManager->m_cResultSocketMutex.Unlock();

		if (bError)
			break;

		if(!nFetchedResults)
			usleep(150 * 1000);
	}
	return 0;
}
