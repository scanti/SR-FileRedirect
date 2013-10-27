#include "FileLogger.h"
#include "stdafx.h"

FILE *log_handle=NULL;

bool InitLogger(char *FileName)
{
	log_handle=fopen(FileName,"w");
	if (log_handle)
		return(true);
	return(false);
};

bool PrintLog(char *message,...)
{
	va_list args;
    va_start(args, message);
	
	if (log_handle)
		vfprintf(log_handle,message, args);

    va_end(args);

	if(log_handle)
		return(true);
	return(false);
};

void CloseLogger()
{
	if(log_handle)
		fclose(log_handle);
	log_handle=NULL;
	return;
};