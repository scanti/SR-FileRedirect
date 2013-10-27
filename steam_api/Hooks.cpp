#include "Hooks.h"
#include "FileLogger.h"
#include "Shlwapi.h"

#pragma comment(lib,"Shlwapi.lib")

char LooseDirectory[MAX_PATH];
char MainDirectory[MAX_PATH];

bool WinMainCalled=false;

void SetMainDirectory(char *filepath)
{
	if(filepath)
	{
		strcpy_s(MainDirectory,MAX_PATH,filepath);
		if(strlen(MainDirectory)>0 && MainDirectory[strlen(MainDirectory)-1]!='\\')
			strcat_s(MainDirectory,MAX_PATH,"\\");
	}
	else
		MainDirectory[0]=0;
}

char *GetMainDirectory()
{
	return(MainDirectory);
}

void SetLooseDirectory(char *filepath)
{
	if(filepath)
	{
		strcpy_s(LooseDirectory,MAX_PATH,filepath);
		if(strlen(LooseDirectory)>0 && LooseDirectory[strlen(LooseDirectory)-1]!='\\')
			strcat_s(LooseDirectory,MAX_PATH,"\\");
	}
	else
		LooseDirectory[0]=0;
}

char *GetLooseDirectory()
{
	return(LooseDirectory);
}

HANDLE WINAPI Vanilla_CreateFileA(LPCSTR lpFileName,DWORD dwDesiredAccess,DWORD dwShareMode,
						 LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition,
						 DWORD dwFlagsAndAttributes,HANDLE hTemplateFile)

{
	if ((_strnicmp(lpFileName,"packfiles",9)!=0) && (_strnicmp(lpFileName,"display.ini",11)!=0) && 
		PathIsRelativeA(lpFileName) && ((dwDesiredAccess&GENERIC_READ)==GENERIC_READ))
	{
		//PrintLog("Opening flie %s returning file not found.\n",lpFileName);
		return(INVALID_HANDLE_VALUE);		
	}
	
	return(CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
		dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile));
}

BOOL WINAPI Vanilla_GetFileAttributesExA(LPCSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId,
								LPVOID lpFileInformation)
{
	if ((_strnicmp(lpFileName,"packfiles",9)!=0) && (_strnicmp(lpFileName,"display.ini",11)!=0) && 
		PathIsRelativeA(lpFileName))
	{
		//PrintLog("Looking for %s returning file not found.\n",lpFileName);
		SetLastError(ERROR_FILE_NOT_FOUND);
		return(false);
	}

	return(GetFileAttributesExA(lpFileName, fInfoLevelId, lpFileInformation));
};

HANDLE WINAPI MainOnly_CreateFileA(LPCSTR lpFileName,DWORD dwDesiredAccess,DWORD dwShareMode,
						 LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition,
						 DWORD dwFlagsAndAttributes,HANDLE hTemplateFile)

{
	char NewFileName[MAX_PATH];
	HANDLE HandleTest;

	if ((_strnicmp(lpFileName,"display.ini",11)!=0) && PathIsRelativeA(lpFileName))
	{
		strcpy_s(NewFileName,MAX_PATH,GetMainDirectory());
		strcat_s(NewFileName,MAX_PATH,lpFileName);

		if (_strnicmp(lpFileName,"packfiles",9)==0)
		{
			PrintLog("Loading packfile in %s ",NewFileName);

			HandleTest = CreateFileA(NewFileName, dwDesiredAccess, dwShareMode, 
				lpSecurityAttributes,dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
			if(HandleTest!=INVALID_HANDLE_VALUE)
			{
				PrintLog("found\n");
				return(HandleTest);
			}
			else
			{
				PrintLog("not found\nLoading from %s\n",lpFileName);
				return(CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
					dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile));
			}
		}
	}
	else
	{
		strcpy_s(NewFileName,MAX_PATH,lpFileName);
	}
	
	//PrintLog("CreateFileA - %s\n",NewFileName);
	return(CreateFileA(NewFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
		dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile));
}

BOOL WINAPI MainOnly_GetFileAttributesExA(LPCSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId,
								LPVOID lpFileInformation)
{
	char NewFileName[MAX_PATH];

	if ((_strnicmp(lpFileName,"display.ini",11)!=0) && PathIsRelativeA(lpFileName))
	{
		strcpy_s(NewFileName,MAX_PATH,GetMainDirectory());
		strcat_s(NewFileName,MAX_PATH,lpFileName);
		
		if (_strnicmp(lpFileName,"packfiles",9)==0)
		{
			PrintLog("Looking for packfile in %s ",NewFileName);
		
			if(GetFileAttributesExA(NewFileName,fInfoLevelId,lpFileInformation))
			{
				PrintLog("found\n");
				return(true);
			}
			else
			{
				PrintLog("not found\nLooking in %s\n",lpFileName);
				return(GetFileAttributesExA(lpFileName,fInfoLevelId,lpFileInformation));
			}
		}
	}
	else
	{
		strcpy_s(NewFileName,MAX_PATH,lpFileName);
	}

	//PrintLog("GetFileAttributesExA - %s\n",NewFileName);
	return(GetFileAttributesExA(NewFileName, fInfoLevelId, lpFileInformation));
};

LPSTR WINAPI New_GetCommandLineA(void)
{
	if (!WinMainCalled)
	{
		PrintLog("Hooked WinMain via GetCommandLineA\n");
		WinMainCalled=true;
	}

	return(GetCommandLineA());
}

/*
HANDLE WINAPI New_CreateFileW(LPCWSTR lpFileName,DWORD dwDesiredAccess,DWORD dwShareMode,
						 LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition,
						 DWORD dwFlagsAndAttributes,HANDLE hTemplateFile)

{
	//PrintLog("CreateFileW - %S\n",lpFileName);
	return(CreateFileW(lpFileName,dwDesiredAccess,dwShareMode,lpSecurityAttributes,
		dwCreationDisposition,dwFlagsAndAttributes,hTemplateFile));
}

HANDLE WINAPI New_FindFirstFileA(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData)
{
	//PrintLog("FindFirstFileA - %s\n",lpFileName);
	return(FindFirstFileA(lpFileName,lpFindFileData));
};

HANDLE WINAPI New_FindFirstFileExA(LPCSTR lpFileName,FINDEX_INFO_LEVELS fInfoLevelId, 
							  LPVOID lpFindFileData, FINDEX_SEARCH_OPS fSearchOp,
							  LPVOID lpSearchFilter, DWORD dwAdditionalFlags)
{
	//PrintLog("FindFirstFileExA - %s\n",lpFileName);
	return(FindFirstFileExA(lpFileName, fInfoLevelId, lpFindFileData,fSearchOp,lpSearchFilter,
		dwAdditionalFlags));
};

DWORD WINAPI New_GetFileAttributesA(LPCSTR lpFileName)
{
	//PrintLog("GetFileAttributesA - %s\n",lpFileName);
	return(GetFileAttributesA(lpFileName));
};

HMODULE WINAPI New_LoadLibraryA(LPCSTR lpFileName)
{
	PrintLog("LoadLibraryA - %s\n",lpFileName);
	return(LoadLibraryA(lpFileName));
};

HMODULE WINAPI New_LoadLibraryW(LPCWSTR lpFileName)
{
	PrintLog("LoadLibraryW - %S\n",lpFileName);
	return(LoadLibraryW(lpFileName));
};

FARPROC WINAPI New_GetProcAddress(HMODULE hModule,LPCSTR lpProcName)
{
	PrintLog("GetProcAddress - %s\n",lpProcName);
	return(GetProcAddress(hModule,lpProcName));
};
*/