/*
 * CSolidSBCTestLibraryManager.cpp
 *
 *  Created on: 20.09.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCTestLibraryManager.h"
#include "../log/CSolidSBCLogging.h"

#include <dirent.h>
#include <dlfcn.h>
#include <vector>

CSolidSBCTestLibraryManager* g_pTestLibraryManagerInstance = 0;

CSolidSBCTestLibraryManager::CSolidSBCTestLibraryManager(const std::string& sLibraryPath)
: m_sLibraryPath(sLibraryPath)
{
	g_pTestLibraryManagerInstance = this;
	LoadAllLibraries();
}

CSolidSBCTestLibraryManager::~CSolidSBCTestLibraryManager()
{
	UnloadAllLibraries();
	g_pTestLibraryManagerInstance = 0;
}

void CSolidSBCTestLibraryManager::UnloadAllLibraries(void)
{
	std::map<CSolidSBCTestManager*,void*>::iterator iIter =	m_mapTestManagerLibHandle.begin();
	for(;iIter != m_mapTestManagerLibHandle.end(); iIter++)
	{
		//TODO: stop all test before unloading of library
		//iIter->first->StopAllTest();
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
