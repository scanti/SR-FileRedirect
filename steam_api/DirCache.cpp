#include "DirCache.h"
#include "FileLogger.h"
#include "stdafx.h"
#include <algorithm>

const char *SearchList[3]=
{
	"",
	"tables\\",
	"packfiles\\pc\\cache\\"
};

std::map<std::string,FILEDATA> DirCache;
FILE *DirListHandle=NULL;

std::string StringToUpper(std::string strToConvert)
{
	std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::toupper);

    return(strToConvert);
}

std::string StringToLower(std::string strToConvert)
{
	std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::tolower);

    return(strToConvert);
}

bool CreateCache(char *DirListFile)
{
	DirListHandle=fopen(DirListFile,"r");
	if(!DirListHandle)
		PrintLog("ERROR - Failed to open directory list file %s\n",DirListFile);

	PrintLog("Creating cache data from %s\n",DirListFile);

	char CurrentDirectory[MAX_PATH];
	char CurrentSearchDirectory[MAX_PATH];
	char CurrentSearch[MAX_PATH];

	char PathBuffer[MAX_PATH];

	bool SearchRootVPP=false;

	while(!SearchRootVPP)
	{

// For the last iteration we want to only check the vpp_pc files in the game's root directory.

		if(!DirListHandle || !fgets(CurrentDirectory,MAX_PATH,DirListHandle))
		{
			CurrentDirectory[0]=0;
			SearchRootVPP=true;
		}
		else
		{
// Remove any control codes from the end of the file path string
			for(int i=strlen(CurrentDirectory)-1;i>=0;i--)
			{
				if(CurrentDirectory[i]>31)
					break;
				CurrentDirectory[i]=0;
			}

	// If the line is blank then skip

			if(!CurrentDirectory[0])
				continue;

	// If the file path is "." then set it to the current directory otherwise FindFirstFileA will search the root directory
	// of your drive.
			
			if(!strcmp(CurrentDirectory,"."))
				GetCurrentDirectoryA(MAX_PATH,CurrentDirectory);
		}
		
		HANDLE SearchDirHandle;
		WIN32_FIND_DATAA FileData;
		
		for(int i=SearchRootVPP?2:0;i<3;i++)
		{
			strcpy_s(CurrentSearchDirectory,MAX_PATH,CurrentDirectory);
			PathAppendA(CurrentSearchDirectory,SearchList[i]);
			strcpy_s(CurrentSearch,MAX_PATH,CurrentSearchDirectory);
			PathAppendA(CurrentSearch,"*.*");

			SearchDirHandle=FindFirstFileA(CurrentSearch,&FileData);

			if(SearchDirHandle==INVALID_HANDLE_VALUE)
				continue;

			do
			{
				if(!strcmp(FileData.cFileName,".") || !strcmp(FileData.cFileName,"..") || (FileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))
					continue;

				char *Extension=PathFindExtensionA(FileData.cFileName);

				if(!_stricmp(Extension,".txt") || !_stricmp(Extension,".exe") || !_stricmp(Extension,".dll") || 
						!_stricmp(Extension,".ini") || !_strnicmp(Extension,".srtt",5))
					continue;

				strcpy_s(PathBuffer,MAX_PATH,SearchList[i]);
				PathAppendA(PathBuffer,FileData.cFileName);
				std::string SearchFileName(PathBuffer);
				SearchFileName=StringToLower(SearchFileName);
				std::map<std::string,FILEDATA>::iterator itDirCache;

				itDirCache=DirCache.find(SearchFileName);

				if(itDirCache==DirCache.end())
				{
					FILEDATA PushData;
					strcpy_s(PathBuffer,MAX_PATH,CurrentSearchDirectory);
					PathAppendA(PathBuffer,FileData.cFileName);
					std::string FullFindFilePath(PathBuffer);
					PushData.FilePath=FullFindFilePath;
					PushData.atrributes.dwFileAttributes=FileData.dwFileAttributes;
					PushData.atrributes.ftCreationTime=FileData.ftCreationTime;
					PushData.atrributes.ftLastAccessTime=FileData.ftLastAccessTime;
					PushData.atrributes.ftLastWriteTime=FileData.ftLastWriteTime;
					PushData.atrributes.nFileSizeHigh=FileData.nFileSizeHigh;
					PushData.atrributes.nFileSizeLow=FileData.nFileSizeLow;
					DirCache[SearchFileName]=PushData;
				}
				
			} while(FindNextFileA(SearchDirHandle,&FileData));
			
			FindClose(SearchDirHandle);
		}
	}
	if(DirListHandle)
		fclose(DirListHandle);
	return(true);
}

void DumpCache()
{
	PrintLog("Directory cache :\n");
	for(std::map<std::string,FILEDATA>::iterator DumpRecord = DirCache.begin(), itr_end = DirCache.end(); DumpRecord != itr_end; ++DumpRecord)
	{
		PrintLog("%s -> %s\n",DumpRecord->first.c_str(),DumpRecord->second.FilePath.c_str());
	}
	PrintLog("*** End of Directory Cache ***\n");
	return;
}

const char *TranslateFilePath(const char *FilePath)
{
	std::string FilePathString(FilePath);
	FilePathString=StringToLower(FilePathString);


	std::map<std::string,FILEDATA>::iterator FoundFilePath;

	FoundFilePath=DirCache.find(FilePathString);

	if(FoundFilePath==DirCache.end())
		return(NULL);

	return(FoundFilePath->second.FilePath.c_str());
}

FILEDATA *TranslateFilePathData(const char *FilePath)
{
	std::string FilePathString(FilePath);
	FilePathString=StringToLower(FilePathString);


	std::map<std::string,FILEDATA>::iterator FoundFilePath;

	FoundFilePath=DirCache.find(FilePathString);

	if(FoundFilePath==DirCache.end())
		return(NULL);

	return(&FoundFilePath->second);
}

void ClearDirCache()
{
	DirCache.clear();
	return;
}

		

