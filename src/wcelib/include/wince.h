// Windows ce defines

#ifndef _WINCE_H
#define _WINCE_H

# ifdef _WIN32_WCE  // Double check

#include <efltk/fl_utf8.h>
#include <efltk/filename.h>
#include <tchar.h>
#include <wceatl.h>
#include <winnetwk.h>
#include <winbase.h>
#include <windows.h>
#include <crtdbg.h>
#include <Atlconv.h>
#include <winbase.h>
#include <winnt.h>
#include <stdlib.h>

#include <drawacp.h>
# define Arc CeArc
# define Chord CeChord
# define Pie CePie

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
		return	fl_utf_strcasecmp(string1,string2);
	}

	static int strncasecmp(const char *string1, const char *string2,int len){
		return fl_utf_strncasecmp(string1,string2,len);
	}

	static char * strdup(const char *todup){
	  int len = strlen(todup);
	  char *buf = new char[len];
	  memcpy(buf,todup,len);
	  buf[len] = 0;
	  return buf;
	}

	typedef struct tagMINMAXINFO {
		POINT ptReserved; 
		POINT ptMaxSize; 
		POINT ptMaxPosition; 
		POINT ptMinTrackSize; 
		POINT ptMaxTrackSize; 
	} MINMAXINFO; 

	static char * strerror(int num){return "unknown wce error";}

# define floorf(a)	float(floor(float(a)))
# define ceilf(a)	float(ceil(float(a)))
# define fmodf(a,b)	float(fmod(float(a),float(b)))
# define fabsf(a)	float(fabs(float(a)))
# define sinf(a)	float(sin(float(a)))
# define cosf(a)	float(cos(float(a)))
# define tanf(a)	float(tan(float(a)))
# define asinf(a)	float(asin(float(a)))
# define acosf(a)	float(acos(float(a)))
# define atanf(a)	float(atan(float(a)))
# define atan2f(a,b)	float(atan2(float(a),float(b)))
# define expf(a)	float(exp(float(a)))
# define logf(a)	float(log(float(a)))
# define log10f(a)	float(log10(float(a)))
# define sqrtf(a)	float(sqrt(float(a)))

# endif
#endif //_WINCE_H