// FL_Config.h: interface for the INI_Config class.
//////////////////////////////////////////////////////////////////////

#ifndef _FL_CONFIG_H_
#define _FL_CONFIG_H_

char *double_to_str(double v);
double str_to_double(const char *v);


#include "Enumerations.h"
#include "Fl_Ptr_List.h"
#include "Fl_Util.h"
#include "Fl_Color.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32_WCE
#include <wince.h>
#endif
/* error defines */
enum {
    CONF_SUCCESS = 0,  /* successful return */
    CONF_ERR_FILE,      /* trouble accessing config file or directory */
    CONF_ERR_SECTION,   /* requested section was not found */
    CONF_ERR_KEY,       /* requested key was not found */
    CONF_ERR_MEMORY,    /* memory allocation error */
    CONF_ERR_NOVALUE,   /* key found, but invalid value associated with it */
};

typedef Fl_Ptr_List SectionList;
typedef Fl_Ptr_List LineList;

// Classes to iterate throught the config file
class FL_API Line
{
public:
    Line(const char *k, const char *v) {
        if(k&&*k!='\0') key = strdup(k); else key=0;
        if(v&&*v!='\0') value = strdup(v); else value=0;
    }
    ~Line() {
        if(key) delete []key; if(value) delete []value; }
    char *key;
    char *value;
};

class FL_API Section
{
public:
    Section(const char *_name, const char *_path, Section *par) { if(_name) name = strdup(_name); else name=0; if(_path) path = strdup(_path); else path=0; parent = par;}
    ~Section() {
        uint n; for(n=0; n<sections.size(); n++) delete (Section*)sections[n];
        for(n=0; n<lines.size(); n++) delete (Line*)lines[n];
        if(name) delete []name; if(path) delete []path;
    }
    char *name, *path;
    Section *parent;
    LineList lines; //Line list
    SectionList sections; //Section list
};

class FL_API Fl_Config {
public:
    // List of sections
    SectionList sections;
    // List of lines in ROOT (no section)
    // To access these, use section NULL
    LineList lines;

    /////////////////////////
    /////////////////////////
    typedef enum {
        USER=1,
        SYSTEM
    } ConfMode;

    // Creates/reads/writes app specific config file.
    //
    // LINUX:
    // File is created in ($home)/.ede/apps/($application)/($application).conf
    // Or ($prefix)/share/ede/apps/($application)/($application).conf
    // WIN32:
    // ($home)\Local Settings\.ede\apps\($application)/($application).conf
    // Or ($common files)\($application)\($application).conf
    //
    // depending ConfMode, USER or SYSTEM
    // Vendor is only used to write it down to file.
    Fl_Config(const char *vendor, const char *application, ConfMode mode=USER);

    //Straight access for some file in filesystem.
    Fl_Config(const char *filename, bool readfile=true, bool createfile=true);

    ~Fl_Config();

    const char *filename() { return filename_; }
    void filename(const char *filename) { if(filename_) delete []filename_; if(filename) filename_=strdup(filename); }

    const char *vendor() { return vendor_; }
    void vendor(const char *vendor) { if(vendor_) delete []vendor_; if(vendor) vendor_=strdup(vendor); }

    const char *application() { return app_; }
    void application(const char *app) { if(app_) delete []app_; if(app) app_=strdup(app); }

    // Finds config file, depending on mode.
    // USER mode finds from ~/.ede/$filename and SYSTEM from $PREFIX/share/ede/$filename
    // if "create" flag is true, path is returned even if file is not found.
    static char *find_config_file(const char *filename, bool create=true, ConfMode mode=USER);

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
    void set_section(const char *secpath) { set_section(create_section(secpath)); }
    void set_section(Section *sec) { cur_sec = sec; }

    void remove_key(const char *section, const char *key);
    void remove_sec(const char *section);

    //These functions assumes that section is set by set_section function!
    int read(const char *key, char *ret, const char *def_value, int size) { return _read_string(cur_sec, key, ret, def_value, size); }
    int read(const char *key, char *&ret, const char *def_value=0) { return _read_string(cur_sec, key, ret, def_value); }
    int read(const char *key, long &ret, long def_value=0)         { return _read_long(cur_sec, key, ret, def_value);   }
    int read(const char *key, int &ret, int def_value=0)           { return _read_int(cur_sec, key, ret, def_value);    }
    int read(const char *key, float &ret, float def_value=0)       { return _read_float(cur_sec, key, ret, def_value);  }
    int read(const char *key, double &ret, double def_value=0)     { return _read_double(cur_sec, key, ret, def_value); }
    int read(const char *key, bool &ret, bool def_value=0)         { return _read_bool(cur_sec, key, ret, def_value);   }
    int read(const char *key, Fl_Color &ret, Fl_Color def_value=0) { return _read_color(cur_sec, key, ret, def_value);  }

    //These functions assumes that section is set by set_section function!
    int write(const char *key, const char *value)    { return _write_string(cur_sec, key, value); }
    int write(const char *key, const long value)     { return _write_long(cur_sec, key, value); }
    int write(const char *key, const int value)      { return _write_int(cur_sec, key, value); }
    int write(const char *key, const float value)    { return _write_float(cur_sec, key, value); }
    int write(const char *key, const double value)   { return _write_double(cur_sec, key, value); }
    int write(const char *key, const bool value)     { return _write_bool(cur_sec, key, value); }
    int write(const char *key, const Fl_Color value) { return _write_color(cur_sec, key, value); }

    //Always give section as first parameter!
    int get(const char *section, const char *key, char *ret, const char *def_value, int size) { return _read_string(find_section(section), key, ret, def_value, size); }
    int get(const char *section, const char *key, char *&ret, const char *def_value=0) { return _read_string(find_section(section), key, ret, def_value); }
    int get(const char *section, const char *key, long &ret, long def_value=0)        { return _read_long(find_section(section), key, ret, def_value);            }
    int get(const char *section, const char *key, int &ret, int def_value=0)          { return _read_int(find_section(section), key, ret, def_value);               }
    int get(const char *section, const char *key, float &ret, float def_value=0)      { return _read_float(find_section(section), key, ret, def_value);         }
    int get(const char *section, const char *key, double &ret, double def_value=0)    { return _read_double(find_section(section), key, ret, def_value);      }
    int get(const char *section, const char *key, bool &ret, bool def_value=0)        { return _read_bool(find_section(section), key, ret, def_value);            }
    int get(const char *section, const char *key, Fl_Color &ret, Fl_Color def_value=0) { return _read_color(find_section(section), key, ret, def_value);   }

    //Always give section as first parameter!
    int set(const char *section, const char *key, const char *value) { return _write_string(create_section(section), key, value); }
    int set(const char *section, const char *key, const long value)  { return _write_long(create_section(section), key, value);   }
    int set(const char *section, const char *key, const int value)   { return _write_int(create_section(section), key, value);    }
    int set(const char *section, const char *key, const float value) { return _write_float(create_section(section), key, value);  }
    int set(const char *section, const char *key, const bool value)  { return _write_double(create_section(section), key, value); }
    int set(const char *section, const char *key, const Fl_Color value) { return _write_color(create_section(section), key, value); }

private:
    int _error;
    char *filename_;
    char *vendor_, *app_;
    Section *cur_sec;
    bool changed;

    void write_section(int indent, FILE *fp, Section *sec);
    Line *create_string(Section *section, const char * key, const char * value);
    Line *find_string(Section *section, const char *key);

    int _read_string(Section *s, const char *key, char *ret, const char *def_value, int size);
    int _read_string(Section *s, const char *key, char *&ret, const char *def_value);
    int _read_long  (Section *s, const char *key, long &ret, long def_value);
    int _read_int   (Section *s, const char *key, int &ret, int def_value);
    int _read_float (Section *s, const char *key, float &ret, float def_value);
    int _read_double(Section *s, const char *key, double &ret, double def_value);
    int _read_bool  (Section *s, const char *key, bool &ret, bool def_value);
    int _read_color(Section *s, const char *key, Fl_Color &ret, Fl_Color def_value);

    int _write_string(Section *s, const char *key, const char *value);
    int _write_long  (Section *s, const char *key, const long value);
    int _write_int   (Section *s, const char *key, const int value);
    int _write_float (Section *s, const char *key, const float value);
    int _write_double(Section *s, const char *key, const double value);
    int _write_bool  (Section *s, const char *key, const bool value);
    int _write_color (Section *s, const char *key, const Fl_Color value);
};

FL_API int conf_is_path_rooted(const char *path);
static inline const char* fl_find_config_file(const char *filename, bool create=true) {
    return Fl_Config::find_config_file(filename, create, Fl_Config::USER);
}

#endif // !defined(AFX_INI_CONFIG_H__A9AF989B_9D44_48ED_B56F_187FCAC49818__INCLUDED_)

