/* fl_plugin.cxx
 *
 * "$Id$"
 *
 * This is a wrapper to make it simple to load plugins on various
 * systems. fl_load_plugin(file, symbol) will load the file as a
 * plugin and then return a pointer to "symbol" in that file.
 *
 * If symbol is null it will return a non-zero value if the plugin
 * loads but you cannot use this value for anything.
 *
 * If there is any problem (file not found, does not load as a plugin,
 * the symbol is not found) it will return null if there is any problem
 * and print debugging info on stderr.
 *
 */

#include <efltk/fl_load_plugin.h>
#include <stdio.h>
#include <config.h>
#include <efltk/filename.h>
#include <efltk/fl_utf8.h>

#if defined(_WIN32)

# include <windows.h>
# include <winbase.h>

void* fl_load_plugin(const char* name, const char* symbol)
{
	WCHAR wbuf[FL_PATH_MAX];
	WCHAR wbuf2[FL_PATH_MAX];
	if(name) fl_utf2unicode((const uchar*)name,strlen(name), (unsigned short*)wbuf); else return 0;
	if(symbol) fl_utf2unicode((const uchar*)symbol,strlen(symbol), (unsigned short*)wbuf2);
    HINSTANCE handle = LoadLibraryW(wbuf);
	if (handle)
    {
        if (!symbol) return (void*)handle;
#ifndef _WIN32_WCE
		void* f = (void*)GetProcAddress(handle, name);
#else
		void* f = (void*)GetProcAddressW(handle, wbuf2);
#endif 
        if (f) return f;
        fprintf(stderr, "%s: function %s missing\n", name, symbol);
        return 0;
    }

    char* msgbuf = 0;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                  FORMAT_MESSAGE_FROM_SYSTEM |
                  FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL,
                  GetLastError(),
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                  (LPTSTR)&msgbuf,
                  0,
                  NULL);
    fprintf(stderr, "%s\n", msgbuf);
    LocalFree(msgbuf);
    return 0;
}


#else
#if HAVE_DLOPEN

#include <errno.h>
# include <unistd.h>
# include <dlfcn.h>

void* fl_load_plugin(const char* name, const char* symbol)
{
    // do not allow plugins if this executable is setuid
    if (getuid() != geteuid())
    {
        fprintf(stderr, "%s: plugins disabled in setuid programs\n", name);
        return 0;
    }
    void* handle = dlopen(name, RTLD_NOW);
    if (handle)
    {
        if (!symbol) return handle;
        void* f = dlsym(handle, symbol);
        if (f) return f;
    }
    fprintf(stderr, "%s\n", dlerror());
    return 0;
}


#else

void* fl_load_plugin(const char* name, const char*)
{
    fprintf(stderr, "%s: loading of plugins not supported\n", name);
    return 0;
}
#endif
#endif

//
// End of "$Id$"
//
