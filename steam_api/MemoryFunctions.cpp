#include "MemoryFunctions.h"

int isNotOKToReadMemory(void    *ptr, DWORD   size)
{
	SIZE_T                          dw;
	MEMORY_BASIC_INFORMATION	mbi;
	int                             ok;

	dw = VirtualQuery(ptr, &mbi, sizeof(mbi));
	ok = ((mbi.Protect & PAGE_READONLY) ||
		  (mbi.Protect & PAGE_READWRITE) ||
		  (mbi.Protect & PAGE_WRITECOPY) ||
		  (mbi.Protect & PAGE_EXECUTE_READ) ||
		  (mbi.Protect & PAGE_EXECUTE_READWRITE) ||
		  (mbi.Protect & PAGE_EXECUTE_WRITECOPY));

	// check the page is not a guard page

	if (mbi.Protect & PAGE_GUARD)
		ok = FALSE;
	if (mbi.Protect & PAGE_NOACCESS)
		ok = FALSE;

	return !ok;
}