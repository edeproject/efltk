// FL_Config.h: interface for the INI_Config class.
//////////////////////////////////////////////////////////////////////

#ifndef _FL_CONFIG_H_
#define _FL_CONFIG_H_

// This is defined to include
// backward compatible funtions and behaviour with
// old Fl_Config
#define BACKWARD_COMPATIBLE 1

#include "Enumerations.h"
#include "Fl_PtrList.h"
#include "Fl_Util.h"
#include "Fl_Color.h"

#include <string.h>
#include <stdio.h>

/* error defines */
enum {
    CONF_SUCCESS = 0,  /* successful return */
    CONF_ERR_FILE,      /* trouble accessing config file or directory */
    CONF_ERR_SECTION,   /* requested section was not found */
    CONF_ERR_KEY,       /* requested key was not found */
    CONF_ERR_MEMORY,    /* memory allocation error */
    CONF_ERR_NOVALUE,   /* key found, but invalid value associated with it */

#ifdef BACKWARD_COMPATIBLE
    CONF_ERR_AGAIN,     /* try operation again (lockfile existed?) */
    CONF_ERR_DEPTH,     /* nested sections or includes in config file too deep */
    CONF_ERR_ARGUMENT   /* argument invalid (NULL?) */
#endif
};

// Classes to iterate throught the config file
class FL_API Line
{
public:
    Line(const char *k, const char *v) {
        if(k&&*k!='\0') key = strdup(k); else key=0;
        if(v&&*v!='\0') value = strdup(v); else value=0;
    }
    ~Line() { if(key) delete []key; if(value) delete []value; }
    char *key;
    char *value;
};

class FL_API Section
{
public:
    Section(const char *_name, const char *_path, Section *par) { if(_name) name = strdup(_name); else name=0; if(_path) path = strdup(_path); else path=0; parent = par;}
    ~Section() {
        Section *s; for(s = sections.first(); s != 0; s = sections.next() ) if(s) delete s;
        Line *l; for(l = lines.first(); l != 0; l = lines.next() ) if(l) delete l;
        if(name) delete []name; if(path) delete []path;
    }
    char *name, *path;
    Section *parent;
    Fl_PtrList<Line> lines;
    Fl_PtrList<Section> sections;
};

typedef Fl_PtrList<Section> SectionList;
typedef Fl_PtrList<Line> LineList;

class FL_API Fl_Config {
public:
    // List of sections
    Fl_PtrList<Section> sections;

/////////////////////////
/////////////////////////

    Fl_Config(const char *_filename, bool read=true, bool create=true);
    ~Fl_Config();

    // This returns true, if data changed.
    // call flush() to sync changes to file
    bool is_changed() { return changed; }

    const char *strerror() { return strerror(_error); }
    const char *strerror(int errnum);
    int error() { return _error; }

    bool read_file (bool create = true);
    bool flush();

    Section *create_section(const char *path);
    Section *find_section(Section *sec, const char *name, bool recursive=false);
    Section *find_section(const char *path, bool perfect_match=true);

    SectionList *section_list(const char *secpath) { Section *s=find_section(secpath); return s?&s->sections:0; }
    LineList *line_list(const char *secpath) { Section *s=find_section(secpath); return s?&s->lines:0; }

    //sets section that is used as default
    bool set_section(const char *secpath) { set_section(find_section(secpath)); return cur_sec ? true : false; }
    void set_section(Section *sec) { cur_sec = sec; }

    void remove_key(const char *section, const char *key);
    void remove_sec(const char *section);

    //these functions assumes that current section is setted
    char *read_string(const char *key) { return read_string(cur_sec, key); }
    long  read_long  (const char *key) { return read_long(cur_sec, key); }
    int   read_int   (const char *key) { return read_int(cur_sec, key); }
    float read_float (const char *key) { return read_float(cur_sec, key); }
    bool  read_bool  (const char *key) { return read_bool(cur_sec, key); }
    Fl_Color read_color(const char *key) { return read_color(cur_sec, key); }

    void write_string(const char *key, const char *value)  { write_string(cur_sec, key, value); }
    void write_long  (const char *key, const long value)   { write_long(cur_sec, key, value); }
    void write_int   (const char *key, const int value)    { write_int(cur_sec, key, value); }
    void write_float (const char *key, const float value)  { write_float(cur_sec, key, value); }
    void write_bool  (const char *key, const bool value)   { write_bool(cur_sec, key, value); }
    void write_color (const char *key, const Fl_Color value) { write_color(cur_sec, key, value); }

    //Always give section as first parameter
    char *read_string(const char *section, const char *key) { return read_string(find_section(section), key); }
    long read_long(const char *section, const char *key)    { return read_long(find_section(section), key);   }
    int  read_int(const char *section, const char *key)     { return read_int(find_section(section), key);    }
    float read_float(const char *section, const char *key)  { return read_float(find_section(section), key);  }
    bool read_bool(const char *section, const char *key)    { return read_bool(find_section(section), key);   }
    Fl_Color read_color(const char *section, const char *key) { return read_color(find_section(section), key); }

    //Always give section as first parameter
    void write_string(const char *sec, const char *key, const char *value);
    void write_long  (const char *sec, const char *key, const long value);
    void write_int   (const char *sec, const char *key, const int value);
    void write_float (const char *sec, const char *key, const float value);
    void write_bool  (const char *sec, const char *key, const bool value);
    void write_color (const char *sec, const char *key, const Fl_Color value);

private:
    int _error;
    char *filename;
    Section *cur_sec;
    bool changed;

    void write_section(int indent, FILE *fp, Section *sec);
    Line *create_string(Section *section, const char * key, const char * value);
    Line *find_string(Section *section, const char *key);

    char *read_string(Section *s, const char *key);
    long  read_long  (Section *s, const char *key);
    int   read_int   (Section *s, const char *key);
    float read_float (Section *s, const char *key);
    bool  read_bool  (Section *s, const char *key);
    Fl_Color read_color(Section *s, const char *key);

    void write_string(Section *s, const char *key, const char *value);
    void write_long  (Section *s, const char *key, const long value);
    void write_int   (Section *s, const char *key, const int value);
    void write_float (Section *s, const char *key, const float value);
    void write_bool  (Section *s, const char *key, const bool value);
    void write_color (Section *s, const char *key, const Fl_Color value);

public:
#ifdef BACKWARD_COMPATIBLE
    ////////////////////////////////////
    // BACKWARD COMPATIBILITY SECTION //
    ////////////////////////////////////

    // Functions below are backward compatible with
    // old Fl_Config functions, so no old apps code
    // changes needed

    inline void __get_section_and_key(const char *str, char *section, char *key)
    {
        int len=strlen(str);
        const char *strptr = str+len-1;
        char ch=0; int pos=0;
        while((ch=*strptr--)) {
            if(ch=='/') {
                strncpy(section, str, len-pos-1);
                strncpy(key, str+(len-pos), pos);
                return;
            }
            pos++;
        }
        strncpy(key, str, 256);
    }

    // get the string value of a key from the config file
    int get(const char *key, char *value, int value_length) {
        char s[1024]={0}, k[256]={0}; __get_section_and_key(key, s, k);
        char *readed = read_string(s, k);
        if(readed) { strncpy(value, readed, value_length); delete []readed; }
        return error();
    }

    // get the long value of a key from the config file
    int get(const char *key, long &lvalue) {
        char s[1024]={0}, k[256]={0}; __get_section_and_key(key, s, k);
        lvalue = read_long(s, k);
        return error();
    }

    // get the int value of a key from the config file
    int get(const char *key, int &ivalue) {
        char s[1024]={0}, k[256]={0}; __get_section_and_key(key, s, k);
        ivalue = read_int(s, k);
        return error();
    }

    // get the uchar value of a key from the config file
    int get(const char *key, uchar &ucvalue) {
        char s[1024]={0}, k[256]={0}; __get_section_and_key(key, s, k);
        int v = read_int(s, k);
        ucvalue = (uchar)v;
        return error();
    }

    // get the boolean value of a key from the config file
    int get_boolean(const char *key, int &bvalue) {
        char s[1024]={0}, k[256]={0}; __get_section_and_key(key, s, k);
        bvalue = read_bool(s, k);
        return error();
    }

    // set the string value of a key in the config file
    int set(const char *key, const char *value = "") {
        char s[1024]={0}, k[256]={0}; __get_section_and_key(key, s, k);
        write_string(s, k, value);
        return error();
    }

    // clear the string value of a key in the config file
    int clear(const char *key)  {
        char s[1024]={0}, k[256]={0}; __get_section_and_key(key, s, k);
        write_string(s, k, "");
        return error();
    }

    // set the long value of a key in the config file
    int set(const char *key, long lvalue) {
        char s[1024]={0}, k[256]={0}; __get_section_and_key(key, s, k);
        write_long(s, k, lvalue);
        return error();
    }

    // set the int value of a key in the config file
    int set(const char *key, int ivalue) {
        char s[1024]={0}, k[256]={0}; __get_section_and_key(key, s, k);
        write_int(s, k, ivalue);
        return error();
    }

    // set the boolean value of a key in the config file
    int set_boolean(const char *key, int bvalue) {
        char s[1024]={0}, k[256]={0}; __get_section_and_key(key, s, k);
        write_bool(s, k, bvalue>1?true:false);
        return error();
    }

    // delete a key/value from the config file
    int del(const char *key) {
        char s[1024]={0}, k[256]={0}; __get_section_and_key(key, s, k);
        remove_key(s, k);
        return error();
    }

    static void clear_cache() { void conf_clear_cache(); conf_clear_cache();}

    ///////////////////////////////////////////
    // END OF BACKWARD COMPATIBILITY SECTION //
    ///////////////////////////////////////////
#endif
};

FL_API int conf_is_path_rooted(const char *path);
FL_API const char* fl_find_config_file(const char* fn, bool cflag=true);
#ifdef BACKWARD_COMPATIBLE
extern Fl_Config *current_config;
inline void conf_clear_cache(void) { if(current_config) current_config->flush(); }
#endif

#endif // !defined(AFX_INI_CONFIG_H__A9AF989B_9D44_48ED_B56F_187FCAC49818__INCLUDED_)

