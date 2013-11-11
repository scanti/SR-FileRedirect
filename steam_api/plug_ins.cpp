#include "plug_ins.h"
#include "FileLogger.h"
#include "MemoryFunctions.h"

int GetSRVersion()
{
	char *Version;
	char *Ident;

// __try, __except block doesn't work. Will have to manually check if memory address is within
// .rdata or .data to avoid access violations.

	//Version=(char *)0x05407b10;
	Version=(char *)0x0;
	Ident=(char *)0x05407b14;

	if(isNotOKToReadMemory(Version,2))
	{
		PrintLog("ERROR - Version pointer invalid.\n");
		return(-1);
	}

	if(isNotOKToReadMemory(Ident,4))
	{
		PrintLog("ERROR - Ident pointer invalid.\n");
		return(-1);
	}

	if(_strnicmp(Version,"07",2)==0 && _strnicmp(Ident,"SR35",4)==0)
		return(7);
	
	return(-1);
}
