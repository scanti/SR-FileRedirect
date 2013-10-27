#pragma once

#include "stdafx.h"

void SetLooseDirectory(char *filepath);
char *GetLooseDirectory();
void SetMainDirectory(char *filepath);
char *GetMainDirectory();
size_t GetMainDirLen();

HANDLE WINAPI Vanilla_CreateFileA(LPCSTR lpFileName,DWORD dwDesiredAccess,DWORD dwShareMode,
						 LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition,
						 DWORD dwFlagsAndAttributes,HANDLE hTemplateFile);

BOOL WINAPI Vanilla_GetFileAttributesExA(LPCSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId,
								LPVOID lpFileInformation);

HANDLE WINAPI MainOnly_CreateFileA(LPCSTR lpFileName,DWORD dwDesiredAccess,DWORD dwShareMode,
						 LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition,
						 DWORD dwFlagsAndAttributes,HANDLE hTemplateFile);

BOOL WINAPI MainOnly_GetFileAttributesExA(LPCSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId,
								LPVOID lpFileInformation);

LPSTR WINAPI New_GetCommandLineA(void);

/*
HANDLE WINAPI New_CreateFileW(LPCTSTR lpFileName,DWORD dwDesiredAccess,DWORD dwShareMode,
						 LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition,
						 DWORD dwFlagsAndAttributes,HANDLE hTemplateFile);

HANDLE WINAPI New_FindFirstFileA(LPCSTR lpFileName,LPWIN32_FIND_DATAA lpFindFileData);

HANDLE WINAPI New_FindFirstFileExA(LPCSTR lpFileName,FINDEX_INFO_LEVELS fInfoLevelId, 
							  LPVOID lpFindFileData, FINDEX_SEARCH_OPS fSearchOp,
							  LPVOID lpSearchFilter, DWORD dwAdditionalFlags);

DWORD WINAPI New_GetFileAttributesA(LPCSTR lpFileName);

HMODULE WINAPI New_LoadLibraryA(LPCSTR lpFileName);
HMODULE WINAPI New_LoadLibraryW(LPCWSTR lpFileName);
FARPROC WINAPI New_GetProcAddress(HMODULE hModule,LPCSTR lpProcName);
*/