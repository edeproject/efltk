// Fl_Config.cpp: implementation of the Fl_Config class.
//
//////////////////////////////////////////////////////////////////////

#include "fl_internal.h"

#include <efltk/vsnprintf.h>
#include <efltk/Fl_String_List.h>
#include <efltk/Fl_Exception.h>
#include <efltk/Fl_Config.h>
#include <efltk/filename.h>
#include <efltk/fl_utf8.h>

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#ifdef _WIN32_WCE
#include <stdlibx.h>
#endif
#include <config.h>

#ifdef _WIN32

# include <io.h>
# include <direct.h>
# include <windows.h>
# define access(a,b) _access(a,b)
# define mkdir(a,b) _mkdir(a)
# define R_OK 4

#else

# include <unistd.h>

#endif /* _WIN32 */

#define LOCALE_TO_C() \
    char *locale = setlocale(LC_ALL, ""); \
    char *restore_locale = locale ? strdup(locale) : strdup("C"); \
    setlocale(LC_ALL, "C")

#define RESTORE_LOCALE() \
    setlocale(LC_ALL, restore_locale); \
    free(restore_locale)

static int is_path_rooted(const char *fn)
{
    /* see if an absolute name was given: */
#ifdef _WIN32
    if (fn[0] == '/' || fn[0] == '.' || fn[0] == '\\' || fn[1]==':')
#else
    if (fn[0] == '/' || fn[0] == '.')
#endif
        return 1;
    return 0;
}

// recursively create a path in the file system
static bool makePath( const char *path ) {
    if(access(path, 0)) {
        const char *s = strrchr( path, slash );
        if ( !s ) return 0;
        int len = s-path;
        char *p = (char*)malloc( len+1 );
        memcpy( p, path, len );
        p[len] = 0;
        makePath( p );
        free( p );
        return ( mkdir( path, 0777 ) == 0 );
    }
    return true;
}

// strip the filename and create a path
static bool makePathForFile( const char *path )
{
    const char *s = strrchr( path, slash );
    if ( !s ) return false;
    int len = s-path;
    char *p = (char*)malloc( len+1 );
    memcpy( p, path, len );
    p[len] = 0;
    bool ret=makePath( p );
    free( p );
    return ret;
}

char *get_sys_dir() {
#ifndef _WIN32
    return CONFIGDIR;
#else
    static char path[FL_PATH_MAX];
    HKEY hKey;
    if(RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows\\CurrentVersion", 0, KEY_READ, &hKey)==ERROR_SUCCESS)
    {
        DWORD size=4096;
        RegQueryValueExW(hKey, L"CommonFilesDir", NULL, NULL, (LPBYTE)path, &size);
        RegCloseKey(hKey);
        return path;
    }
    return "C:\\EFLTK\\";
#endif
}

char *Fl_Config::find_config_file(const char *filename, bool create, int mode)
{
    static char path[4096];

    if(is_path_rooted(filename)) {
        strncpy(path, filename, sizeof(path));
        return (create || !access(path, R_OK)) ? path : 0;
    }
    if(mode==USER) {
        char *cptr = fl_get_homedir();
        char *ret=0;
        if(cptr) {
            snprintf(path, sizeof(path)-1, "%s%c%s%c%s", cptr, slash, ".ede", slash, filename);
            if(create || !access(path, R_OK)) {
                ret = path;
            }
            delete []cptr;
            return ret;
        }
		return 0;
    } else {
        snprintf(path, sizeof(path)-1, "%s%c%s", get_sys_dir(), slash, filename);
        return (create || !access(path, R_OK)) ? path : 0;
    }
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define S(item) ((Fl_Config_Section*)item)

Fl_Config::Fl_Config(const char *vendor, const char *application, int mode)
: Fl_Config_Section("","",0)
{
    m_cur_sec = 0;
    m_changed=false;
    m_error = 0;

    if(vendor) m_vendor = vendor;
    if(application) m_app = application;

    if(!m_app.empty()) {
        const char *file=0;
        char tmp[FL_PATH_MAX];
#ifdef _WIN32
        if(mode==SYSTEM)
            snprintf(tmp, sizeof(tmp)-1, "%s%c%s.conf", m_app.c_str(), slash, m_app.c_str());
        else
#endif
            snprintf(tmp, sizeof(tmp)-1, "apps%c%s%c%s.conf", slash, m_app.c_str(), slash, m_app.c_str());
        file = find_config_file(tmp, true, mode);
        if(file) {
            bool ret = makePathForFile(file);
            if(ret) {
                m_filename = file;
                read_file(true);
            } else
                m_error = CONF_ERR_FILE;
        } else
            m_error = CONF_ERR_FILE;
    } else
        m_error = CONF_ERR_FILE;
}

Fl_Config::Fl_Config(const char *filename, bool read, bool create)
: Fl_Config_Section("","",0)
{
    if(filename) m_filename = filename;

    m_error = 0;
    m_cur_sec = 0;
    m_changed=false;

    if(create && !m_filename.empty()) {
        makePathForFile(m_filename.c_str());
    }

    if(read) read_file(create);
}

Fl_Config::~Fl_Config()
{
    flush();
    clear();
}

/* get error string associated with error number */
const char *Fl_Config::strerror(int error)
{
    switch(error)
    {
    case CONF_SUCCESS:     return _("Successful completion");
    case CONF_ERR_FILE:    return _("Could not access config file");
    case CONF_ERR_SECTION: return _("Config file section not found");
    case CONF_ERR_KEY:     return _("Key not found in section");
    case CONF_ERR_MEMORY:  return _("Could not allocate memory");
    case CONF_ERR_NOVALUE: return _("Invalid value associated with key");
    default:               return _("Unknown error");
    }
}

bool Fl_Config::read_file(bool create)
{
    bool error = false;
    if(m_filename.empty()) {
        m_error = CONF_ERR_FILE;
        return false;
    }

    if(create && !fl_file_exists(m_filename.c_str())) {
        FILE *f = fl_fopen(m_filename.c_str(), "w+");
        if(f) {
            fputs(" ", f);
            fclose(f);
        } else error=true;
    }

    if(error) {
        m_error = CONF_ERR_FILE;
        return false;
    }

    // If somebody calls this function two times, we
    // need to clean earlier section list...
    clear();

    /////
    struct stat fileStat;
    stat(m_filename.c_str(), &fileStat);
    unsigned int size = fileStat.st_size;
    if(size == 0) {
        m_error = 0;
        return true;
    }

    FILE *fp = fl_fopen(m_filename.c_str(), "r");
    if(!fp) {
        //fprintf(stderr, "fp == 0: %s\n", m_filename);
        m_error = CONF_ERR_FILE;
        return false;
    }

    unsigned bsize = size*sizeof(char);
    char *buffer = (char*)malloc(bsize+1);
    buffer[bsize] = 0;
    if(!buffer) {
        m_error = CONF_ERR_MEMORY;
        return false;
    }

    unsigned int readed = fread(buffer, 1, size, fp);
    if(readed <= 0) {
        free((char*)buffer);
        fclose(fp);
        m_error = CONF_ERR_FILE;
        return false;
    }
    fclose(fp);

    Fl_String_List strings(buffer, "\n");

    free((char*)buffer);

    Fl_Config_Section *section = this;
    for(unsigned n=0; n<strings.size(); n++)
    {
        Fl_String line;
        int comment_pos = strings[n].rpos('#');
        if(comment_pos>=0) {
            line = strings[n].sub_str(comment_pos, strings[n].length()-comment_pos).trim();
        } else {
            line = strings[n].trim();
        }

        if(line[0] == '[')
        {
            int pos = line.pos(']');
            if(pos>=0)
            {
                Fl_String sec(line.sub_str(1, pos-1));
                section = create_section(sec);
            }
        }
        else if(line[0] != '#')
        {
            int pos = line.pos('=');
            if(pos==-1) pos = line.pos(':');
            if(pos>=0) {
                Fl_String key(line.sub_str(0, pos));
                pos++;
                Fl_String value(line.sub_str(pos, line.length()-pos));
                section->add_entry(key, value);
            }
        }
    }

    m_error = 0;
    m_changed=false;
    return true;
}

bool Fl_Config::flush()
{
    if(!m_changed) return true;
    if(m_filename.empty()) return false;

    FILE *file = fl_fopen(m_filename.c_str(), "w+");
    if(!file)
        fl_throw(::strerror(errno));

    LOCALE_TO_C();

    fprintf(file, "# EFLTK INI Version %f\n", FL_VERSION);
    if(!m_vendor.empty()) fprintf(file, "# Vendor: %s\n", m_vendor.c_str());
    if(!m_app.empty())    fprintf(file, "# Application: %s\n", m_app.c_str());

    // Flush sections
    write_section(0, file);

    RESTORE_LOCALE();

    fclose(file);

    m_error = 0;
    m_changed=false;
    return true;
}

Fl_Config_Section *Fl_Config::create_section(const Fl_String &name)
{
    if(name.empty()) return 0;

    Fl_Config_Section *section = find_section(name, true);
    if(section) return section;

    int pos = name.rpos('/');
    if(pos==-1) {
        section = new Fl_Config_Section(name, "", 0);
        sections().append(section);
        return section;
    }
    pos++;

    Fl_String sec_name(name.sub_str(pos, name.length()-pos));
    Fl_String sec_path(name.sub_str(0, pos));

    Fl_Config_Section *parent = find_section(sec_path, false);
    Fl_Config_Sections *list = &sections();

    if(!parent) {
        Fl_String_List sections;
        sections.from_string(sec_path, "/");

        Fl_String path;
        for(unsigned n=0; n<sections.size(); n++) {
            if(parent) list = &parent->sections();

            parent = new Fl_Config_Section(sections[n], path, parent);
            list->append(parent);

            path += sections[n];
            path += '/';
        }
    }

    if(parent) list = &parent->sections();

    section = new Fl_Config_Section(sec_name, sec_path, parent);
    list->append(section);

    m_error = 0;
    return section;
}

Fl_Config_Section *Fl_Config::find_section(const char *path, bool perfect_match) const
{
    if(!path || !*path) return 0;

    Fl_String_List sections;
    sections.from_string(path, "/");

    if(sections.size()==0)
        return find(path, false);

    Fl_Config_Section *section = (Fl_Config_Section *)this;
    for(unsigned n=0; n<sections.size(); n++) {

        Fl_Config_Section *tmp = section->find(sections[n], false);
        if(!tmp) {
            if(perfect_match)
                return 0;
            else
                break;
        }
        section = tmp;
    }
    return section;
}

void Fl_Config::remove_key(const char *section, const char *key)
{
    if(key) {
        Fl_Config_Section *sect = find_section(section, true);
        if(sect->remove_entry(key)) {
            m_error = 0;
            m_changed = true;
            return;
        }
    }
    m_error = CONF_ERR_KEY;
}

void Fl_Config::remove_sec(const char *section)
{
    if(!section) return;

    Fl_Config_Section *sect;
    if((sect = find_section(section, true)) != 0) {
        if(sect->parent()) {
            sect->parent()->sections().remove(sect);
        } else {
            sections().remove(sect);
        }
        delete sect;
        m_error = 0;
        m_changed = true;
        return;
    }
    m_error = CONF_ERR_SECTION;
}

/*
 *  Read functions
 */

int Fl_Config::_read_string(Fl_Config_Section *s, const char *key, char *ret, const char *def_value, int size)
{
    if(!key || !s) {
        if(def_value) strncpy(ret, def_value, size);
        else ret[0] = '\0';
        m_error = (!key ? CONF_ERR_KEY : CONF_ERR_SECTION);
        return m_error;
    }

    Fl_String *val = s->find_entry(key);
    if(val) {
        int len = (val->length() < size) ? val->length()+1 : size;
        memcpy(ret, val->c_str(), len);
        return (m_error = CONF_SUCCESS);
    }

    if(def_value) strncpy(ret, def_value, size);
    else ret[0] = '\0';

    m_error = CONF_ERR_KEY;
    return m_error;
}

int Fl_Config::_read_string(Fl_Config_Section *s, const char *key, char *&ret, const char *def_value)
{
    if(!key || !s) {
        ret = def_value?strdup(def_value):0;
        m_error = (!key ? CONF_ERR_KEY : CONF_ERR_SECTION);
        return m_error;
    }

    Fl_String *val = s->find_entry(key);
    if(val && !val->empty())
    {
        ret = strdup(val->c_str());
        return (m_error = CONF_SUCCESS);
    }

    ret = def_value ? strdup(def_value) : 0;
    m_error = CONF_ERR_KEY;
    return m_error;
}

int Fl_Config::_read_string(Fl_Config_Section *s, const char *key, Fl_String &ret, const char *def_value)
{
    if(!key || !s) {
        ret = def_value;
        m_error = !key ? CONF_ERR_KEY : CONF_ERR_SECTION;
        return m_error;
    }

    Fl_String *val = s->find_entry(key);
    if(val) {
        ret = (*val);
        return (m_error = CONF_SUCCESS);
    }

    ret = def_value;
    return (m_error = CONF_ERR_KEY);
}

int Fl_Config::_read_long(Fl_Config_Section *s, const char *key, long &ret, long def_value)
{
    Fl_String tmp;
    if(!_read_string(s, key, tmp, 0)) {
        ret = tmp[0] ? strtol(tmp, NULL, 10) : def_value;
    } else
        ret = def_value;
    return m_error;
}

int Fl_Config::_read_int(Fl_Config_Section *s, const char *key, int &ret, int def_value)
{
    Fl_String tmp;
    if(!_read_string(s, key, tmp, 0)) {
        ret = tmp.to_int(def_value);
    } else
        ret = def_value;
    return m_error;
}

int Fl_Config::_read_float (Fl_Config_Section *s, const char *key, float &ret, float def_value)
{
    Fl_String tmp;
    if(!_read_string(s, key, tmp, 0)) {
        LOCALE_TO_C();
        ret = (float)strtod(tmp, 0);
        RESTORE_LOCALE();
    } else
        ret = def_value;
    return m_error;
}

int Fl_Config::_read_double(Fl_Config_Section *s, const char *key, double &ret, double def_value)
{
    Fl_String tmp;
    if(!_read_string(s, key, tmp, 0)) {
        LOCALE_TO_C();
        ret = strtod(tmp, 0);
        RESTORE_LOCALE();
    } else
        ret = def_value;
    return m_error;
}

int Fl_Config::_read_bool(Fl_Config_Section *s, const char *key, bool &ret, bool def_value)
{
    Fl_String tmp;
    if(_read_string(s, key, tmp, 0)) {
        ret = def_value;
        return m_error;
    }

    tmp = tmp.upper_case();
    if(tmp=="TRUE" ||
       tmp=="YES" ||
       tmp=="ON" ||
       tmp=="1" )
    {
        ret = true;
    } else if(tmp=="FALSE" ||
              tmp=="NO" ||
              tmp=="OFF" ||
              tmp=="0" )
    {
        ret = false;
    } else {
        m_error = CONF_ERR_NOVALUE;
        ret = def_value;
    }
    return m_error;
}

int Fl_Config::_read_color(Fl_Config_Section *s, const char *key, Fl_Color &ret, Fl_Color def_value)
{
    Fl_String tmp;
    if(_read_string(s, key, tmp, 0)) {
        ret = def_value;
        return m_error;
    }

    int r=0,g=0,b=0;
    if(sscanf(tmp, "RGB(%d,%d,%d)", &r, &g, &b)!=3) {
        ret = def_value;
        return (m_error = CONF_ERR_NOVALUE);
    }
    ret = fl_rgb(r,g,b);
    return m_error;
}

/*
 *  Write functions
 */

int Fl_Config::_write_string(Fl_Config_Section *s, const char *key, const char *value)
{
    Fl_String val(value);
    return _write_string(s, key, val);
}

int Fl_Config::_write_string(Fl_Config_Section *s, const char *key, const Fl_String &value)
{
    if(!s) return (m_error = CONF_ERR_SECTION);
    if(!key) return (m_error = CONF_ERR_KEY);

    Fl_String *val = s->find_entry(key);
    if(val) {
        (*val) = value;
    } else
        s->add_entry(key, value);

    m_changed=true;
    return (m_error=CONF_SUCCESS);
}

int Fl_Config::_write_long(Fl_Config_Section *s, const char *key, const long value)
{
    char tmp[128]; snprintf(tmp, sizeof(tmp)-1, "%ld", value);
    return _write_string(s, key, tmp);
}

int Fl_Config::_write_int(Fl_Config_Section *s, const char *key, const int value)
{
    char tmp[128]; snprintf(tmp, sizeof(tmp)-1, "%d", value);
    return _write_string(s, key, tmp);
}

int Fl_Config::_write_float(Fl_Config_Section *s, const char *key, const float value)
{
    LOCALE_TO_C();
    char tmp[32]; snprintf(tmp, sizeof(tmp)-1, "%g", value);
    RESTORE_LOCALE();
    return _write_string(s, key, tmp);
}

int Fl_Config::_write_double(Fl_Config_Section *s, const char *key, const double value)
{
    LOCALE_TO_C();
    char tmp[32]; snprintf(tmp, sizeof(tmp)-1, "%g", value);
    RESTORE_LOCALE();
    return _write_string(s, key, tmp);
}

int Fl_Config::_write_bool(Fl_Config_Section *s, const char *key, const bool value)
{
    if(value) return _write_string(s, key, "1");
    return _write_string(s, key, "0");
}

int Fl_Config::_write_color(Fl_Config_Section *s, const char *key, const Fl_Color value)
{
    uint8 r,g,b;
    fl_get_color(value, r,g,b);
    char tmp[32];
    snprintf(tmp, sizeof(tmp)-1, "RGB(%d,%d,%d)", r,g,b);
    return _write_string(s, key, tmp);
}

//////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////

Fl_Config_Section::Fl_Config_Section(const Fl_String &name, const Fl_String &path, Fl_Config_Section *par)
: m_parent(par), m_name(name), m_path(path)
{

}

Fl_Config_Section::~Fl_Config_Section()
{
    clear();
}

void Fl_Config_Section::clear()
{
    for(unsigned n=0; n<sections().size(); n++) {
        Fl_Config_Section *s = (Fl_Config_Section *)sections()[n];
        delete s;
    }
    m_lines.clear();
    m_sections.clear();
}

void Fl_Config_Section::write_section(int indent, FILE *fp) const
{
    for(int a=0; a<indent; a++) fprintf(fp, " ");

    if(!name().empty())
        fprintf(fp, "[%s%s]\n", path().c_str(), name().c_str());

    for(Fl_Config_Lines::Iterator it(m_lines); it.current(); it++) {
        if(!it.id().empty()) {
            for(int a=0; a<indent; a++) fprintf(fp, " ");
            fprintf(fp, "  %s=%s\n", it.id().c_str(), it.value().c_str());
        }
    }

    fprintf(fp, "\n");

    for(unsigned n=0; n<sections().size(); n++) {
        Fl_Config_Section *child = S(sections()[n]);
        child->write_section(indent+2, fp);
    }
}

void Fl_Config_Section::add_entry(const Fl_String &key, const Fl_String &value)
{
    if(key.empty()) return;
    lines().insert(key.trim(), value.trim());
}

bool Fl_Config_Section::remove_entry(const Fl_String &key)
{
    return lines().remove(key);
}

Fl_String *Fl_Config_Section::find_entry(const char *key) const
{
    if(key) {
        if(lines().contains(key))
            return &lines().get_value(key);
    }
    return 0;
}

Fl_Config_Section *Fl_Config_Section::find(const char *name, bool recursive) const
{
    const Fl_Config_Sections *list = &sections();

    for(uint n=0; n<list->size(); n++) {
        Fl_Config_Section *s = S(list->item(n));
        if(s->name() == name) {
            return s;
        }
        if(recursive) {
            s = s->find(name, recursive);
            if(s) return s;
        }
    }
    return 0;
}
