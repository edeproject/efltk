#include <efltk/Fl_Util.h>
#include <efltk/Fl_String_List.h>
#include <efltk/filename.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

#include <sys/stat.h>
#include <time.h>

#ifdef _WIN32

# include <windows.h>
# include <io.h>
# include <direct.h>

# define S_ISLNK(m)      (false)
#ifndef __GNUC__
# define S_ISREG(m)      (((m) & _S_IFMT) == _S_IFREG)
# define S_ISDIR(m)      (((m) & _S_IFMT) == _S_IFDIR)
# define S_ISBLK(m)      (((m) & _S_IFMT) == _S_IFBLK)
#endif /* __GNUC__ */

#define lstat stat

#else

# include <sys/types.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>

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

bool Fl_FileAttr::parse(const char *filename)
{
#ifdef _WIN32
	capacity=0;
	free=0;					
    if(strlen(filename) < 4 && filename[1]==':') {
        char nbuf[4];nbuf[0] = filename[0];nbuf[1]=':';nbuf[2]='\\';nbuf[3]='\0';

        // Don't even try to read floppy, etc...
        // We all know how fast this is in windoze... =)
        uint type = GetDriveType(nbuf);
        if(type==DRIVE_CDROM||type==DRIVE_FIXED) {
            uint64 ign;
            GetDiskFreeSpaceEx(nbuf, (PULARGE_INTEGER)&ign, (PULARGE_INTEGER)&capacity, (PULARGE_INTEGER)&free);
        }
        flags |= FL_DEVICE;
        return true;
    }
#endif

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

    if(S_ISDIR(s.st_mode)) flags |= FL_DIR;
    if(S_ISREG(s.st_mode)) flags |= FL_FILE;
    if(S_ISLNK(s.st_mode)) flags |= FL_LINK;

    size = (ulong)s.st_size;
	modified = (ulong)s.st_mtime;

    const time_t *t = &s.st_mtime;	
    struct tm *lt = localtime(t);
    strftime(time, 128, "%x  %X", lt);

    return true;
}

Fl_FileAttr *fl_file_attr(const char *name)
{
    Fl_FileAttr *a = new Fl_FileAttr();
    a->parse(name);
    return a;
}

char *fl_get_homedir()
{
    char *path = new char[4096];
    memset(path, 0, 4096);
	const char *str1;

#ifdef _WIN32
	const char *str2;
    HKEY hKey;
    if(RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders",0,KEY_READ,&hKey)==ERROR_SUCCESS)
    {
        DWORD size=4096;
        LONG result=RegQueryValueEx(hKey, "Local AppData", NULL, NULL, (LPBYTE)path, &size);  // Change "Personal" to "Desktop" if you want...
        RegCloseKey(hKey);
        return path;
    }

    if((str2=getenv("HOMEPATH"))!=NULL) {      // This should be good for WinNT, Win2K according to MSDN
        if((str1=getenv("HOMEDRIVE"))==NULL)
            str1="c:";
        strcat(path, str1);
        strcat(path+strlen(str1), str2);
        return path;
    }
#endif

    if((str1=getenv("HOME"))!=NULL) {
        strcpy(path, str1);
        return path;
    }

    return 0;
}

bool fl_file_exists(const char *name) {
    return (access(name, F_OK)==0);
}

bool fl_is_dir(const char* name)
{
    const char *file = name;
#if defined(_WIN32) || defined(__EMX__)
    char tmp[FL_PATH_MAX];
    if(name[strlen(name)-1] == '\\') {
        // Windows thinks C:\test doesn't exists, but C:\test\ does?!!
        strcpy(tmp, name); tmp[strlen(name)-1] = '\0';//\\';
        file = tmp;
    }
#endif // WIN32 || __EMX__

    struct stat s;
    if(stat(file, &s) < 0) return false;
    if(S_ISDIR(s.st_mode)) return true;
    return false;
}

char **fl_get_files(char *path, int *files_count)
{
    char **tmp = 0;
    int num_files = 0;

    dirent **files;
    num_files = fl_filename_list(path, &files);

    if(num_files) {
        tmp = (char **)malloc((num_files+1)*sizeof(char *)+sizeof(char *));

        int n;
        for(n = 0; n < num_files; n ++) {
            char *file = tmp[num_files] = strdup(files[n]->d_name);
            tmp[n] = file;
        }
        tmp[n] = 0; //make sure last item in list is 0
    }

    if(files_count) *files_count=num_files;
    return tmp;
}

#define append_num(ftype, fmt, type) \
    type_##ftype = va_arg(ap, type); \
    sprintf(tmpnum, fmt, type_##ftype); \
    len += strlen(tmpnum);

int fl_va_len(char *format, va_list ap)
{
    char *ptr = format;
    int len = 0;

    char *type_s;
    int type_d;
    double type_g;
    long int type_ld;
    char tmpnum[64];

    char ch;
    while((ch = *ptr++)) {
        if(ch=='%') {
            ch = *ptr++;
            // Copy format
            char fmt[64] = {0};
            char *fmtptr = fmt;
            *fmtptr++ = '%';
            while(isdigit(ch)) {
                ch=*ptr++;
                *fmtptr++ = ch;
                if(ch=='.') { ch=*ptr++; *fmtptr++ = ch; }
            }
            *fmtptr++ = ch;
            switch(tolower(ch)) {
            case 's':
                type_s = va_arg(ap, char *);
                len += strlen(type_s);
                break;
            case 'd':
            case 'o':
            case 'x':
                append_num(d, fmt, int);
                break;
            case 'f':
            case 'e':
            case 'g':
                append_num(g, fmt, double);
                break;
            case 'l':
                *fmtptr++ = *ptr++;
                append_num(ld, fmt, long int);
                break;

            case '%':
            default:
                break;
            }
        }
    }
    return len+strlen(format);
}

char *fl_strdup_printf(char *string, ...)
{
    char *s;
    int len = 0;

    if(!string || !strcmp(string, ""))
        return 0;

    va_list ap;
    va_start(ap, string);
    len = fl_va_len(string, ap);
    va_end(ap);

    s = new char[strlen(string)+len];

    va_start(ap, string);
    vsprintf(s, string, ap);
    va_end(ap);

    return s;
}

char **fl_split(const char *string,
                const char *delimiter,
                int         max_tokens)
{
    static Fl_CString_List string_list;
    string_list.clear();

    char **str_array, *s;
    unsigned int n = 0;

    if(string == NULL || delimiter == NULL )
        return NULL;

    if (max_tokens < 1)
        max_tokens = 255;

    s = strstr (string, delimiter);
    if(s) {
        unsigned int delimiter_len = strlen (delimiter);
        do {
            uint len;
            char *new_string;

            len = s - string;
            new_string = new char[len + 1];
            strncpy(new_string, string, len);
            new_string[len] = 0;
            string_list.append(new_string);
            n++;
            string = s + delimiter_len;
            s = strstr(string, delimiter);
        }
        while (--max_tokens && s);
    }

    if(*string && max_tokens) {
        n++;
        char *_s = strdup(string);
        string_list.append(_s);
    }

    str_array = (char**)malloc((n+1)*(sizeof(char*)));
    str_array[n] = 0;

    char **ptr = str_array;
    for(n=0; n<string_list.size(); n++)
        *ptr++ = (char*)string_list[n];

    return str_array;
}

char *fl_tolower(char *string)
{
    char *ptr = string;
    while(*ptr) *ptr++=tolower(*ptr);
    return string;
}

char *fl_toupper(char *string)
{
    char *ptr = string;
    while(*ptr) *ptr++=toupper(*ptr);
    return string;
}

char *fl_trimleft(char *string)
{
    char *start;

    if(string == NULL )
        return NULL;

    for(start = string; *start && isspace (*start); start++);

    memmove(string, start, strlen(start) + 1);

    return string;
}

char *fl_trimright(char *string)
{
    char *s;

    if(string == NULL )
        return NULL;

    if (!*string)
        return string;

    for (s = string + strlen (string) - 1; s >= string && isspace((unsigned char)*s); s--)
        *s = '\0';
     
    return string;
}

void fl_freev(char **str_array)
{
    if(str_array) {
        for(int n=0; str_array[n]!=0; n++) {			
            delete []str_array[n];			
		}
		delete []str_array;
    }
}

int fl_start_child_process(char *cmd)
{
#ifndef _WIN32
    int pid, status;
    int nulldev;
    extern char **environ;

    if (cmd == NULL)
        return (1);

    pid = fork ();
    if (pid == -1)
        return (-1);
    if (pid == 0)
    {
        char *argv[4];
        // child
        argv[0] = "sh";
        argv[1] = "-c";
        argv[2] = cmd;
        argv[3] = NULL;

        // The following is to avoid X locking when executing
        //  terminal based application that requires user input
        if ((nulldev = open ("/dev/null", O_RDWR)))
        {
            close (0); dup (nulldev);
            close (1); dup (nulldev);
            close (2); dup (nulldev);
        }

        if (execve ("/bin/sh", argv, environ) == -1)
            perror ("/bin/sh");
        _exit (127);
    }
    do
    {
        if (waitpid (pid, &status, 0) == -1)
        {
            if (errno != EINTR)
                return (-1);
        }
        else
            return status;
    }
    while (1);
    
#endif
    return 0;
}

#include <efltk/fl_draw.h>

const char *fl_cut_line(const char *str, int maxwidth)
{
    int len = strlen(str);
    int w=0;
    static char buf[4096];

    maxwidth-=6; //Just guess...
    if(maxwidth<0) {
        return "";
    }
    w = int(fl_width(buf, len));
    if(w<maxwidth) return str;

    strncpy(buf, str, sizeof(buf));
    int pos=len+1;
    while(pos-->0) {
        w = int(fl_width(buf, pos-2));
        if(w<maxwidth) {
            break;
        }
        if(pos-3>0) buf[pos-3] = '.';
        if(pos-2>0) buf[pos-2] = '.';
        if(pos-1>0) buf[pos-1] = '.';
        if(pos>=0) buf[pos] = '\0';
    }
    return buf;
}

const char *fl_cut_multiline(const char *buf, int maxwidth)
{
    static char ret[4096];
    int ret_size=0;

    char *ptr = (char *)buf;
    char *lines = strtok(ptr,"\n");
    while(lines) {
        const char *tmp = fl_cut_line(lines, maxwidth);
        int tmp_len = strlen(tmp);

        strncpy(ret+ret_size, tmp, tmp_len);
        ret[ret_size+tmp_len] = '\n';
        ret_size+=tmp_len+1;

        lines = strtok(NULL, "\n");
    }
    ret[ret_size-1] = '\0';

    return ret;
}

