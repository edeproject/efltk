#include <config.h>

#include <efltk/filename.h>
#include <efltk/fl_utf8.h>

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#ifdef _WIN32

#if !defined(__GNUC__) && !defined(__BORLANDC__)
# define S_ISREG(m)      (((m) & _S_IFMT) == _S_IFREG)
# define S_ISDIR(m)      (((m) & _S_IFMT) == _S_IFDIR)
# define S_ISBLK(m)      (((m) & _S_IFMT) == _S_IFBLK)
#endif /* __GNUC__ */

#define lstat stat

#else

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>

#endif


#if defined(_WIN32) && !defined(__CYGWIN__)
# include <windows.h>
# include <io.h>

# ifndef _WIN32_WCE
#  include <direct.h>
# else
#  include <wince.h>
#  include <stdlibx.h>
# endif /* _WIN32_WCE */

#elif !defined(_WIN32_WCE)

# include <unistd.h>
# include <pwd.h>

#endif

// Define access mode constants if they aren't already defined.
#ifndef F_OK
# define F_OK 00
#endif
#ifndef X_OK
# define X_OK 01
#endif
#ifndef W_OK
# define W_OK 02
#endif
#ifndef R_OK
# define R_OK 04
#endif

bool Fl_File_Attr::parse(const char *filename)
{
#ifdef _WIN32
	capacity=0;
	free=0;
#ifndef _WIN32_WCE
	if(strlen(filename) < 4 && filename[1]==':') {
        char nbuf[4];nbuf[0] = filename[0];nbuf[1]=':';nbuf[2]='\\';nbuf[3]='\0';

        // Don't even try to read floppy, etc...
        // We all know how fast this is in windoze... =)
        uint type = GetDriveTypeA(nbuf);
        if(type==DRIVE_CDROM||type==DRIVE_FIXED) {
            uint64 ign;
            GetDiskFreeSpaceExA(nbuf, (PULARGE_INTEGER)&ign, (PULARGE_INTEGER)&capacity, (PULARGE_INTEGER)&free);
        }
        flags |= DEVICE;
        return true;
    }

#endif // _WIN32_WCE

#endif //_WIN32

    const char *file = filename;
#if defined(_WIN32) || defined(__EMX__)
    if(filename[strlen(filename)-1] == '\\') {
        // Windows thinks C:\test\ doesn't exists, but C:\test does?!!
        char tmp[4096]; strcpy(tmp, filename); tmp[strlen(filename)-1] = '\0';
        file = tmp;
    }
#endif // WIN32 || __EMX__

    struct stat s;
    if(lstat(file, &s) < 0)
        return false;

    if(S_ISDIR(s.st_mode)) flags.set(DIR);
    if(S_ISREG(s.st_mode)) flags.set(FILE);
#ifndef _WIN32
    if(S_ISLNK(s.st_mode)) flags.set(LINK);
#endif

    size = (ulong)s.st_size;
	modified = (ulong)s.st_mtime;

    const time_t *t = &s.st_mtime;	
    struct tm *lt = localtime(t);
    strftime(time, 128, "%x  %X", lt);

    return true;
}

Fl_File_Attr *fl_file_attr(const char *name)
{
    Fl_File_Attr *a = new Fl_File_Attr();
    a->parse(name);
    return a;
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////

static inline bool isdirsep(char c) { return (c=='/' || c=='\\'); }

/* expand a file name by prepending current directory, deleting . and
   .. (not really correct for symbolic links) between the prepended
   current directory.  Use $PWD if it exists.
   Returns true if any changes were made.
*/
bool fl_file_absolute(char *to, int to_len, const char *from)
{
    if (isdirsep(from[0])        /*|| from[0] == '|' // for tcl pipes? */
#if defined(_WIN32) || defined(__EMX__) && !defined(__CYGWIN__)
        || from[0] && from[1]==':'
#endif
       )
    {
        memcpy(to, from, to_len);
        return false;
    }
	
    char *a,temp[FL_PATH_MAX];
    const char *start = from;

#ifndef _WIN32
    a = fl_getenv("PWD");
    if(a) memcpy(temp, a, FL_PATH_MAX);
    else 
#endif
	{
		a = fl_getcwd(temp, FL_PATH_MAX); if (!a) return false;
	}
#if defined(_WIN32) || defined(__EMX__) && !defined(__CYGWIN__)
    // forward slashes only
    for (a = temp; *a; a++) if (*a=='\\') *a = '/';
#else
    a = temp+strlen(temp);
#endif
    if (isdirsep(*(a-1))) a--;
    /* remove intermediate . and .. names: */
    while (*start == '.')
    {
        if (start[1]=='.' && isdirsep(start[2]))
        {
            char *b;
            for (b = a-1; b >= temp && !isdirsep(*b); b--);
            if (b < temp) break;
            a = b;
            start += 3;
        }
        else if (isdirsep(start[1]))
        {
            start += 2;
        } else
            break;
    }
    *a++ = '/';
    strncpy(a, start, FL_PATH_MAX-(a-temp));
    temp[FL_PATH_MAX-1] = 0;
    memcpy(to, temp, to_len);
    return true;
}

/* expand a file name by substuting environment variables and
   home directories.  Returns true if any changes were made.
   to & from may be the same buffer.
*/
bool fl_file_expand(char *buf, int buf_len, const char *from) 
{
	char *temp = new char[buf_len];
	strncpy(temp, from, buf_len);
	char *start = temp;
	char *end = temp+strlen(temp);
	
	bool ret = false;
	
	for (char *a=temp; a<end; ) 
	{	// for each slash component
		char *e; 
		for (e=a; e<end && !isdirsep(*e); e++); // find next slash
		const char *value = 0; // this will point at substitute value
		switch (*a) {
		case '~':	// a home directory name
			if (e <= a+1) {	// current user's directory
				value = fl_get_homedir();
			} 
#ifndef _WIN32
			else {	// another user's directory
				struct passwd *pwd;
				char t = *e; *(char *)e = 0; 
				pwd = getpwnam(a+1); 
				*(char *)e = t;
				if (pwd) value = pwd->pw_dir;
			}
#endif
			break;
		case '$':		/* an environment variable */
			{
			char t = *e; *(char *)e = 0; 
#ifdef _WIN32
			int len    = strlen(a+1);
			unsigned short* wbuf = (unsigned short*)malloc((len+6) * sizeof(short));
			len = fl_utf2unicode((unsigned char*)a+1, len, wbuf);
			wbuf[len] = 0;
			unsigned short *env = (unsigned short*)_wgetenv((wchar_t*)wbuf);
			free(wbuf);
			if(env) {
				value = (char*) malloc(wcslen((wchar_t*)env) * 5);
				len = fl_unicode2utf(env, wcslen((wchar_t*)env), (char*)value);
				((char*)value)[len] = 0;
			} else
				value = 0;
#else
			value = fl_getenv(a+1);
#endif
			*(char *)e = t;
			}
			break;
		}
		if (value) {
			// substitutions that start with slash delete everything before them:
			if (isdirsep(value[0])) start = a;
#if defined(WIN32) || defined(__EMX__) && !defined(__CYGWIN__)
			// also if it starts with "A:"
			if (value[0] && value[1]==':') start = a;
#endif
			int t = strlen(value); if (isdirsep(value[t-1])) t--;
			if ((end+1-e+t) >= buf_len) end += buf_len - (end+1-e+t);
			memmove(a+t, e, end+1-e);
			end = a+t+(end-e);
			*end = '\0';
			memcpy(a, value, t);
			ret = true;
#ifdef WIN32
			free((char*)value);
#endif
		} else {
			a = e+1;
#if defined(WIN32) || defined(__EMX__) && !defined(__CYGWIN__)
			if (*e == '\\') {*e = '/'; ret = true;} // ha ha!
#endif
		}
	}
	strncpy(buf, start, buf_len);
	delete []temp;
	return ret;
}

// returns pointer to the last '.' or to the NULL if none:
const char *fl_file_getext(const char *buf)
{
    const char *q = 0;
    const char *p = buf;
    for (p=buf; *p; p++) {
        if (*p == '/') q = 0;
#if defined(WIN32) || defined(__EMX__) && !defined(__CYGWIN__)
        else if (*p == '\\') q = 0;
#endif
        else if (*p == '.') q = p;
    }
    return q ? q : p;
}

// Replace .ext with new extension
// If no . in name, append new extension
// If new extension is NULL, act like it is ""
char *fl_file_setext(char *buf, const char *ext)
{
    char *q = (char *)fl_file_getext(buf);
    if (ext) strcpy(q,ext); else *q = 0;
    return(buf);
}

bool fl_is_dir(const char* name) {
	if(!name || !*name) return false;

#ifdef _WIN32
	// Windows thinks that "C:" is not dir, but "C:\\" is.
	// It also thinks that "C:\somedir\" is not dir, but "C:\somedir" is.. SIGH! 
	char buffer[FL_PATH_MAX];

	int len = strlen(name);
	if(name[1]==':' && name[2] == '\0') {
		buffer[0] = name[0];
		buffer[1] = ':';
		buffer[2] = '\\';
		buffer[3] = '\0';
		name = buffer;
	}
	else if(len>3 && (name[len-1] == '\\' || name[len-1] == '/') ) {
		memcpy(buffer, name, len);
		buffer[len-1] = '\0';
		name = buffer;
	}
#endif

    struct stat s;
    return (stat(name, &s)==0) && S_ISDIR(s.st_mode);
}

bool fl_file_exists(const char *name) {
    return (access(name, F_OK)==0);
}

char *fl_get_homedir() {
   char *path = new char[FL_PATH_MAX];
	const char *str1;

#ifdef _WIN32
	TCHAR w32path[4096];
    HKEY hKey;
    if(RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders"), 0, KEY_READ, &hKey)==ERROR_SUCCESS)
    {
        DWORD size=4096;
		// Change "Personal" to "Desktop" if you want...
		if(RegQueryValueEx(hKey, TEXT("Local AppData"), NULL, NULL, (LPBYTE)w32path, &size)==ERROR_SUCCESS)
		{
			RegCloseKey(hKey);			
#ifdef UNICODE
			int len = wcslen(w32path);			
			path[fl_unicode2utf((unsigned short*)w32path, len, path)] = '\0';
#else
			memcpy(path, w32path, FL_PATH_MAX);
#endif
			return path;
		}		
    }

	// This should be good for WinNT, Win2K according to MSDN
	const char *str3;
    if((str3=fl_getenv("HOMEPATH"))!=NULL) 
	{
        if((str1=fl_getenv("HOMEDRIVE"))==NULL)
            str1="c:\\";
        strcat(path, str1);
        strcat(path+strlen(str1), str3);
        return path;
    }
#endif /* _WIN32 */

    str1=fl_getenv("HOME");
    if (str1) {
         memcpy(path, str1, strlen(str1)+1);
         return path;
    }

    return 0;
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

Fl_String fl_file_expand(const Fl_String &from)
{
	Fl_String ret;
	
	for(int n=0; n<from.length(); n++) 
	{
		// find next slash
		int e;
		for(e=n; e<from.length() && !isdirsep(from[e]); e++);
		Fl_String value; // this will point at substitute value
		switch(from[n]) {
	
		// a home directory name
		case '~':
			if(e <= n+1) {	// current user's directory
				value = fl_homedir();
			} 
#ifndef _WIN32
			else {	// another user's directory
				struct passwd *pwd;
				pwd = getpwnam(from.sub_str(n+1, e-n-1)); 
				if(pwd) value = pwd->pw_dir;
			}
#endif
			break;

		// an environment variable
		case '$':
			value = fl_getenv(from.sub_str(n+1, e-n-1));
			break;
		}

		if(!value.empty()) {
			// substitutions that start with slash delete everything before them:
			ret += value;
			ret += slash;
		} else {
			ret.append(from.c_str()+n, e-n+1);
			//ret += from.sub_str(n, e-n+1);
		}
		n = e;
	}
	return ret;
}

const Fl_String &fl_homedir()
{
	static Fl_String home;
	if(home.length()>0) return home;
	
	char *homedir = fl_get_homedir();
	home.append(homedir, strlen(homedir));
	free((char*)homedir);
	return home;
}

Fl_String fl_file_absolute(const Fl_String &from)
{
	char path[FL_PATH_MAX];
	if(!getcwd(path, FL_PATH_MAX)) return Fl_String(from);
	Fl_String ret(path);
	if(!isdirsep(ret[ret.length()-1]) && !isdirsep(from[0]))
		ret += slash;
	ret.append(from.c_str(), from.length());
	return ret;
}

Fl_String fl_file_getext(const Fl_String &str)
{
	int pos = str.rpos('.');
	if(pos>-1) { pos++; return str.sub_str(pos, str.length()-pos); }
	return Fl_String("");
}

Fl_String fl_file_setext(const Fl_String &str, const char *ext)
{
	Fl_String ret(str);
	int pos = ret.rpos('.');	
	if(pos>-1) ret.sub_delete(pos, ret.length()-pos);
	if(ext[0]!='.') ret += '.';
	ret += ext;
	return ret;
}

Fl_String fl_file_filename(const Fl_String &str)
{
	int pos = str.rpos('/');
	if(pos==-1) pos = str.rpos('\\');
	if(pos>-1) { pos++; return str.sub_str(pos, str.length()-pos); }
	return Fl_String("");
}
