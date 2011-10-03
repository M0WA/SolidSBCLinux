/*
 * CSolidSBCTestLibraryManager.cpp
 *
 *  Created on: 20.09.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCTestLibraryManager.h"

#include <dirent.h>
#include <dlfcn.h>

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
	m_mapTestNamesThreadFunc.clear();
}

void CSolidSBCTestLibraryManager::LoadAllLibraries(void)
{
	UnloadAllLibraries();

	int nLoadedLibraries = 0;

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
					if( !TryLoadLibrary(ent->d_name) ) {
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
        //TODO: cout << "Error opening directory" << endl;
    }
}

bool CSolidSBCTestLibraryManager::TryLoadLibrary(const std::string& sLibraryFileName)
{
	void *handle = dlopen (sLibraryFileName.c_str(), RTLD_NOW);
	if (!handle) {
		return false;
	}

	CSolidSBCTestManager::PTESTMANAGER_INSTANCEGETTER_FUNC GetSolidSBCTestManager = (CSolidSBCTestManager::PTESTMANAGER_INSTANCEGETTER_FUNC)dlsym(handle, "GetSolidSBCTestManager");
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

	//TODO: enumerate test names and thread functions to map
	//m_mapTestNamesThreadFunc.insert(mapSubTestNamesThreadFuncs.begin(),mapSubTestNamesThreadFuncs.end());
	return true;
}

bool CSolidSBCTestLibraryManager::StartTestFromConfig(const std::string& sConfigXml)
{
	//TODO: implement CSolidSBCTestLibraryManager::StartTestFromConfig
	return false;
}

CSolidSBCTestLibraryManager* CSolidSBCTestLibraryManager::GetInstance(void)
{
	return g_pTestLibraryManagerInstance;
}
