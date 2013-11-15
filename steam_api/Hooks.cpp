#include "Hooks.h"
#include "FileLogger.h"
#include "Shlwapi.h"
#pragma comment(lib,"Shlwapi.lib")
#include "iat_functions.h"
#include "plug_ins.h"
#include "DirCache.h"

char LooseDirectory[MAX_PATH];
size_t LooseDirectoryLength=0;
char MainDirectory[MAX_PATH];
size_t MainDirectoryLength=0;

int WinMainCount=0;

union {
	void *set;
	int (*func)(void);
} Old_SteamAPI_Shutdown;

void SetMainDirectory(char *filepath)
{
	if(filepath && filepath[0])
	{
		// Store length of string as memcpy is quicker than strcpy when used multiple times.
		MainDirectoryLength=strlen(filepath);
		memcpy(MainDirectory,filepath,MainDirectoryLength+1);
		if(MainDirectory[MainDirectoryLength-1]!='\\')
		{
			MainDirectory[MainDirectoryLength++]='\\';
			MainDirectory[MainDirectoryLength]=0;
		}
	}
	else
	{
		MainDirectory[0]=0;
		MainDirectoryLength=0;
	}
}

char *GetMainDirectory()
{
	return(MainDirectory);
}

size_t GetMainDirLen()
{
	return(MainDirectoryLength);
}

void SetLooseDirectory(char *filepath)
{
	if(filepath && filepath[0])
	{
		// Store length of string as memcpy is quicker than strcpy when used multiple times.
		LooseDirectoryLength=strlen(filepath);
		memcpy(LooseDirectory,filepath,LooseDirectoryLength+1);
		if(LooseDirectory[LooseDirectoryLength-1]!='\\')
		{
			LooseDirectory[LooseDirectoryLength++]='\\';
			LooseDirectory[LooseDirectoryLength]=0;
		}
	}
	else
	{
		LooseDirectory[0]=0;
		LooseDirectoryLength=0;
	}
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
		//PrintLog("Opening file %s - returning file not found.\n",lpFileName);
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
		//PrintLog("Looking for %s - returning file not found.\n",lpFileName);
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
		memcpy(NewFileName,MainDirectory,MainDirectoryLength);
		strcpy(NewFileName+MainDirectoryLength,lpFileName);

		if (_strnicmp(lpFileName,"packfiles",9)==0)
		{
			//PrintLog("Loading packfile in %s ",NewFileName);

			HandleTest = CreateFileA(NewFileName, dwDesiredAccess, dwShareMode, 
				lpSecurityAttributes,dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
			if(HandleTest!=INVALID_HANDLE_VALUE)
			{
				//PrintLog("found\n");
				return(HandleTest);
			}
			else
			{
				//PrintLog("not found\n>   Loading from %s\n",lpFileName);
				return(CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
					dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile));
			}
		}
	}
	else
	{
		return(CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
		dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile));
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
		// Generate new path for relative file.
		memcpy(NewFileName,MainDirectory,MainDirectoryLength);
		strcpy(NewFileName+MainDirectoryLength,lpFileName);
		
		// vpp_pc files are in the packfiles\pc\cache directory.
		// Only check "packfiles" as quicker and whole path not needed.
		if (_strnicmp(lpFileName,"packfiles",9)==0)
		{
			// File path is looking in the packfiles directory.
			//PrintLog("Looking for packfile in %s ",NewFileName);
		
			if(GetFileAttributesExA(NewFileName,fInfoLevelId,lpFileInformation))
			{
				// Packfile exists in redirected directory. So return with info.
				//PrintLog("found\n");
				return(true);
			}
			else
			{
				// Packfile doesn't exist in redirected directory so try the original.
				//PrintLog("not found\nLooking in %s\n",lpFileName);
				return(GetFileAttributesExA(lpFileName,fInfoLevelId,lpFileInformation));
			}
		}
	}
	else
	{
		// File is "display.ini" or has a full path. So don't redirect.
		return(GetFileAttributesExA(lpFileName, fInfoLevelId, lpFileInformation));
	}

	// Not a packfile so look in the redirected directory.
	//PrintLog("GetFileAttributesExA - %s\n",NewFileName);
	return(GetFileAttributesExA(NewFileName, fInfoLevelId, lpFileInformation));
};

HANDLE WINAPI Redirect_CreateFileA(LPCSTR lpFileName,DWORD dwDesiredAccess,DWORD dwShareMode,
						 LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition,
						 DWORD dwFlagsAndAttributes,HANDLE hTemplateFile)

{
	char NewFileName[MAX_PATH];
	HANDLE HandleTest;

	if ((_strnicmp(lpFileName,"display.ini",11)!=0) && PathIsRelativeA(lpFileName))
	{
		memcpy(NewFileName,MainDirectory,MainDirectoryLength);
		strcpy(NewFileName+MainDirectoryLength,lpFileName);

		//PrintLog("Loading file from %s ",NewFileName);

		HandleTest = CreateFileA(NewFileName, dwDesiredAccess, dwShareMode, 
			lpSecurityAttributes,dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
		if(HandleTest!=INVALID_HANDLE_VALUE)
		{
			//PrintLog("found\n");
			return(HandleTest);
		}

		memcpy(NewFileName,LooseDirectory,LooseDirectoryLength);
		strcpy(NewFileName+LooseDirectoryLength,lpFileName);
		//PrintLog("not found\n>   Loading from %s ",NewFileName);
		
		HandleTest = CreateFileA(NewFileName, dwDesiredAccess, dwShareMode, 
			lpSecurityAttributes,dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
		if((HandleTest!=INVALID_HANDLE_VALUE))
		{
			//PrintLog("found\n");
			return(HandleTest);
		}

		if(_strnicmp(lpFileName,"packfiles",9)!=0)
		{
			//PrintLog("returning not found\n");
			return(HandleTest);
		}

		//PrintLog("not found\n>>      Loading from %s\n",lpFileName);
	}
		
	return(CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
		dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile));
}

BOOL WINAPI Redirect_GetFileAttributesExA(LPCSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId,
								LPVOID lpFileInformation)
{
	char NewFileName[MAX_PATH];


if ((_strnicmp(lpFileName,"display.ini",11)!=0) && PathIsRelativeA(lpFileName))
	{
		memcpy(NewFileName,MainDirectory,MainDirectoryLength);
		strcpy(NewFileName+MainDirectoryLength,lpFileName);

		//PrintLog("Looking for file %s ",NewFileName);

		if(GetFileAttributesExA(NewFileName,fInfoLevelId,lpFileInformation))
		{
			//PrintLog("found\n");
			return(true);
		}

		memcpy(NewFileName,LooseDirectory,LooseDirectoryLength);
		strcpy(NewFileName+LooseDirectoryLength,lpFileName);
		//PrintLog("not found\n>   Looking for %s ",NewFileName);
		
		if(GetFileAttributesExA(NewFileName,fInfoLevelId,lpFileInformation))
		{
			//PrintLog("found\n");
			return(true);
		}

		if(_strnicmp(lpFileName,"packfiles",9)!=0)
		{
			//PrintLog("returning not found\n");
			return(false);
		}

		//PrintLog("not found\n>>      Loading for %s\n",lpFileName);
	}

	return(GetFileAttributesExA(lpFileName, fInfoLevelId, lpFileInformation));
};

LPSTR WINAPI New_GetCommandLineA(void)
{
// The first time called it's by the CRT initialisation routines. This means the system is in
// an undefined state.

	if (WinMainCount==0)
	{
		WinMainCount++;
		PrintLog("GetCommandLineA called by CRT init.\n");
		return(GetCommandLineA());
	}

// We want the second time it is called. This means it's being called by WinMain.

	if(WinMainCount==1)
	{
		PrintLog("Hooked WinMain via GetCommandLineA\n");
		
		if(PatchIat(GetModuleHandleA(NULL),"steam_api.dll","SteamAPI_Shutdown",
			(void *)QuittingGameHook, &Old_SteamAPI_Shutdown.set)==S_OK)
			PrintLog("Patched steam_api.dll:SteamAPI_Shutdown.\n");

		PrintLog("Saints Row Version = %i\n",GetSRVersion());
	
		CreateCache("dirlist.txt");
		DumpCache();

		WinMainCount++;
	}

	return(GetCommandLineA());
}

int _stdcall QuittingGameHook()
{
	PrintLog("Hooked game quitting via SteamAPI_Shutdown.\n");
	return (Old_SteamAPI_Shutdown.func());
}