// Windows ce defines

#ifndef _WINCE_H
#define _WINCE_H

# ifdef _WIN32_WCE  // Double check


#include <tchar.h>
//#include <wceatl.h>
#include <winnetwk.h>
#include <winbase.h>
#include <windows.h>
#include <crtdbg.h>
#include <winbase.h>
#include <winnt.h>
#include <stdlibx.h>
#include <sys/types.h>
#include <drawacp.h>
#include <locale.h>
# define Arc CeArc
# define Chord CeChord
# define Pie CePie

#define ENUMLOGFONTW ENUMLOGFONT
#define ENUMLOGFONTA ENUMLOGFONT
#define FindNextFileA FindNextFileW


	typedef struct tagMINMAXINFO {
		POINT ptReserved; 
		POINT ptMaxSize; 
		POINT ptMaxPosition; 
		POINT ptMinTrackSize; 
		POINT ptMaxTrackSize; 
	} MINMAXINFO; 


# endif
#endif //_WINCE_H