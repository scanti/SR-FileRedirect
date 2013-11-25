#pragma once

#include <map>
#include <string>

#include "Shlwapi.h"
#pragma comment(lib,"Shlwapi.lib")

struct FILEDATA
{
	std::string FilePath;
	WIN32_FILE_ATTRIBUTE_DATA atrributes;
	bool MultiDef;
};

bool CreateCache(char *DirListFile);
void DumpCache();
void ClearDirCache();

const char *TranslateFilePath(const char *FilePath);
FILEDATA *TranslateFilePathData(const char *FilePath);

