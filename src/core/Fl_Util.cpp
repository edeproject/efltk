#include <config.h>

#include <efltk/Fl_Util.h>
#include <efltk/Fl_String_List.h>
#include <efltk/filename.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

#ifdef _WIN32_WCE
#include <wince.h>
#endif

#define append_num(ftype, fmt, type) \
    ftype = va_arg(ap, type); \
    sprintf(tmpnum, fmt, ftype); \
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
                append_num(type_d, fmt, int);
                break;
            case 'f':
            case 'e':
            case 'g':
                append_num(type_g, fmt, double);
                break;
            case 'l':
                *fmtptr++ = *ptr++;
                append_num(type_ld, fmt, long int);
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

    char **str_array;
    const char *s;
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

//////////////////////////////////////////////////

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

