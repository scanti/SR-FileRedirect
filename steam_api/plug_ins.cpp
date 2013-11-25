#include "plug_ins.h"
#include "FileLogger.h"
#include "MemoryFunctions.h"
#pragma comment(lib,"Version.lib")

int GetSRVersion()
{
	HMODULE hMod;
	HRSRC hResInfo;
	DWORD dwSize;
	HGLOBAL hResData;
	LPVOID pRes, pResCopy;
	UINT uLen;
	VS_FIXEDFILEINFO *lpFfi;

	hMod=GetModuleHandleA(NULL);

	hResInfo = FindResource(hMod, MAKEINTRESOURCE(1), RT_VERSION);
	dwSize = SizeofResource(hMod, hResInfo);
	hResData = LoadResource(hMod, hResInfo);
	pRes = LockResource(hResData);
	pResCopy = LocalAlloc(LMEM_FIXED, dwSize);
	CopyMemory(pResCopy, pRes, dwSize);
	FreeResource(hResData);

	VerQueryValue(pResCopy, TEXT("\\"), (LPVOID*)&lpFfi, &uLen);

	DWORD dwFileVersionMS = lpFfi->dwFileVersionMS;
	DWORD dwFileVersionLS = lpFfi->dwFileVersionLS;

	DWORD dw1 = HIWORD(dwFileVersionMS);
	DWORD dw2 = LOWORD(dwFileVersionMS);
	DWORD dw3 = HIWORD(dwFileVersionLS);
	DWORD dw4 = LOWORD(dwFileVersionLS);

	LocalFree(pResCopy);
	return(dw3);
}
