/*
 * CSolidSBCTestLibraryManager.cpp
 *
 *  Created on: 20.09.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCTestLibraryManager.h"


#include <dirent.h>
#include <dlfcn.h>
#include <map>
#include <string>

typedef void* (*PGET_SOLIDSBC_TESTS_FUNC)(void);

CSolidSBCTestLibraryManager* g_pTestLibraryManagerInstance = 0;

CSolidSBCTestLibraryManager::CSolidSBCTestLibraryManager(const std::string& sLibraryPath)
: m_sLibraryPath(sLibraryPath)
{
	g_pTestLibraryManagerInstance = this;
	LoadTestLibraries();
}

CSolidSBCTestLibraryManager::~CSolidSBCTestLibraryManager()
{
	g_pTestLibraryManagerInstance = 0;
}

void CSolidSBCTestLibraryManager::LoadTestLibraries(void)
{
	m_mapTestNamesThreadFunc.clear();

	int nLoadedLibraries = 0;
	int nAvailableTests  = 0;

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
					std::map<std::string,void*> mapSubTestNamesThreadFuncs;
					if( !TryLoadLibrary(ent->d_name, mapSubTestNamesThreadFuncs) ) {
						m_mapTestNamesThreadFunc.insert(mapSubTestNamesThreadFuncs.begin(),mapSubTestNamesThreadFuncs.end());
						nAvailableTests += mapSubTestNamesThreadFuncs.size();
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

bool CSolidSBCTestLibraryManager::TryLoadLibrary(const std::string& sLibraryFileName, std::map<std::string,void*>& mapTestNamesThreadFuncs)
{
	void *handle = dlopen (sLibraryFileName.c_str(), RTLD_NOW);
	if (!handle) {
		return false;
	}

	PGET_SOLIDSBC_TESTS_FUNC GetSolidSBCTests = (PGET_SOLIDSBC_TESTS_FUNC)dlsym(handle, "GetSolidSBCTestManager");
	char *error;
	if ((error = dlerror()) != NULL)  {
		dlclose(handle);
		return false;
	}

	void* retFunc = GetSolidSBCTests();
	if (!retFunc){
		dlclose(handle);
		return false;
	}

	mapTestNamesThreadFuncs = *((std::map<std::string,void*>*)retFunc);
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
