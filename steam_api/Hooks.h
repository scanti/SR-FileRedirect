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

HANDLE WINAPI Redirect_CreateFileA(LPCSTR lpFileName,DWORD dwDesiredAccess,DWORD dwShareMode,
						 LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition,
						 DWORD dwFlagsAndAttributes,HANDLE hTemplateFile);

BOOL WINAPI Redirect_GetFileAttributesExA(LPCSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId,
								LPVOID lpFileInformation);


LPSTR WINAPI New_GetCommandLineA(void);
int _stdcall QuittingGameHook();