// Windows ce defines

#ifndef _WINCE_H
#define _WINCE_H

# ifdef _WIN32_WCE  // Double check
#   include <efltk/fl_utf8.h>
#	include <efltk/filename.h>
#include <tchar.h>
#include <wceatl.h>
#include <winnetwk.h>
#include <winbase.h>
#include <windows.h>
#include <crtdbg.h>
#include <Atlconv.h>
#include <winbase.h>
#include <winnt.h>


	static char * getcwd(char *tmp, int size) { 
	  static unsigned short tmp2[FL_PATH_MAX];
	  int length = GetModuleFileName(0,tmp2,sizeof(tmp)*sizeof(short)); 
	  fl_unicode2utf(tmp2,length,tmp);
	  return tmp; 
	}


	static wchar_t * _wgetenv(wchar_t *env){
		static wchar_t tmp[FL_PATH_MAX];
		if(wcscmp(tmp,L"\\Windows"))
			wcscpy(tmp,L"\\Windows");
		env = tmp;
		return env;
	}

	static int stricmp(const char *string1, const char *string2){
	  static unsigned short tmp1[FL_PATH_MAX];
	  static unsigned short tmp2[FL_PATH_MAX];
	  fl_utf2unicode((const unsigned char*)string1,strlen(string1),tmp1);
	  fl_utf2unicode((const unsigned char*)string2,strlen(string2),tmp2);

	  return _wcsicmp(tmp1,tmp2);		
	}

/*	
	int __cdecl stricmp(const unsigned short* s1, const char* s2)
	{
		USES_CONVERSION;
		return wcsicmp(s1, A2T(s2));
	}
*/

	static float cosf(float x){
		double xx = (double)x;
		return (float)cos(xx);
	}

	static float sinf(float x){
		double xx = (double)x;
		return (float)sin(xx);
	}

	static float acosf(float x){
		double xx = (double)x;
		return (float)acos(xx);
	}
	static float asinf(float x){
		double xx = (double)x;
		return (float)asin(xx);
	}


	static char * strdup(const char *todup){
	  wchar_t *wbuf		= (wchar_t*) malloc(strlen(todup) *sizeof(wchar_t));
	  char *retdup	= (char*) malloc(strlen(todup)+1);
	  if(!wbuf)
		  return 0;
	  fl_utf2unicode((const unsigned char*)todup,strlen(todup),wbuf);
	  fl_unicode2utf(wbuf,wcslen(wbuf),retdup);
	  free(wbuf);
	  return retdup;
		
	}

	typedef struct tagMINMAXINFO {
		POINT ptReserved; 
		POINT ptMaxSize; 
		POINT ptMaxPosition; 
		POINT ptMinTrackSize; 
		POINT ptMaxTrackSize; 
	} MINMAXINFO; 

	float atan2f( float y, float x ){
		return (float) atan2((double)y,(double)x);
	
	}


# endif
#endif //_WINCE_H