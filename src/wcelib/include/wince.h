// Windows ce defines

# ifdef _WIN32_WCE  // Double check
#   include <efltk/fl_utf8.h>
#	include <windows.h>
#	include <efltk/filename.h>
	static char * getcwd(char *tmp, int size) { 
	  static unsigned short tmp2[FL_PATH_MAX];
	  int length = GetModuleFileName(0,tmp2,sizeof(tmp)*sizeof(short)); 
	  fl_unicode2utf(tmp2,length,tmp);
	  return tmp; 
	}


	static char * getenv(char *env){
		static char tmp[FL_PATH_MAX];
		if(strcmp(tmp,"\\Windows"))
			strcpy(tmp,"\\Windows");
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


	typedef struct tagMINMAXINFO {
		POINT ptReserved; 
		POINT ptMaxSize; 
		POINT ptMaxPosition; 
		POINT ptMinTrackSize; 
		POINT ptMaxTrackSize; 
	} MINMAXINFO; 


# endif
