/*
 * $Id$
 *
 * Extended Fast Light Toolkit (EFLTK)
 * Copyright (C) 2002-2003 by EDE-Team
 * WWW: http://www.sourceforge.net/projects/ede
 *
 * Fast Light Toolkit (FLTK)
 * Copyright (C) 1998-2003 by Bill Spitzak and others.
 * WWW: http://www.fltk.org
 *
 * This library is distributed under the GNU LIBRARY GENERAL PUBLIC LICENSE
 * version 2. See COPYING for details.
 *
 * Author : Mikko Lahteenmaki
 * Email  : mikko@fltk.net
 *
 * Please report all bugs and problems to "efltk-bugs@fltk.net"
 *
 */

#ifndef _FL_CONFIG_H_
#define _FL_CONFIG_H_

#include "Enumerations.h"
#include "Fl_Ptr_List.h"
#include "Fl_Util.h"
#include "Fl_String.h"
#include "Fl_Color.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32_WCE
#include <wince.h>
#endif

/* error defines */
enum ConfErrors {
    CONF_SUCCESS = 0,   /* successful return */
    CONF_ERR_FILE,      /* trouble accessing config file or directory */
    CONF_ERR_SECTION,   /* requested section was not found */
    CONF_ERR_KEY,       /* requested key was not found */
    CONF_ERR_MEMORY,    /* memory allocation error */
    CONF_ERR_NOVALUE,   /* key found, but invalid value associated with it */
};

typedef Fl_Ptr_List SectionList;
typedef Fl_Ptr_List LineList;

// Classes to iterate throught the config file

/** Line */
class Line {
public:
    Line(Fl_String k, Fl_String v) { key = k; value = v; }
    Fl_String key, value;
};

/** Section */
class Section
{
public:
    Section(const Fl_String &name, const Fl_String &path, Section *par) : parent(par), name(name), path(path) { }
    ~Section() {
        uint n; for(n=0; n<sections.size(); n++) delete (Section*)sections[n];
        for(n=0; n<lines.size(); n++) delete (Line*)lines[n];
    }
    Section *parent;
    Fl_String name, path;
    LineList lines; //Line list
    SectionList sections; //Section list
};

/** Fl_Config */
class FL_API Fl_Config {
public:
    // List of sections
    SectionList sections;
    // List of lines in ROOT (no section)
    // To access these, use section NULL
    LineList lines;

    enum {
        USER=1,
        SYSTEM
    };

    /**
	 * Creates/reads/writes app specific config file.
     *
     * LINUX:<br>
     * File is created in ($home)/.ede/apps/($application)/($application).conf
     * Or ($prefix)/share/ede/apps/($application)/($application).conf
     * <br>WIN32:<br>
     * ($home)\Local Settings\.ede\apps\($application)/($application).conf
     * Or ($common files)\($application)\($application).conf
     *
     * depending ConfMode, USER or SYSTEM
     * Vendor is only used to write it down to file.
	 */
    Fl_Config(const char *vendor, const char *application, int mode=USER);

    /**
	 * Straight access for some file in filesystem.
	 */
    Fl_Config(const char *filename, bool readfile=true, bool createfile=true);

    virtual ~Fl_Config();

    virtual void clear();

    const Fl_String &filename() const { return m_filename; }
    void filename(const char *filename) { m_filename = filename; }
    void filename(const Fl_String &filename) { m_filename = filename; }

    const Fl_String &vendor() const { return m_vendor; }
    void vendor(const char *vendor) { m_vendor = vendor; }
    void vendor(const Fl_String &vendor) { m_vendor = vendor; }

    const Fl_String &application() const { return m_app; }
    void application(const char *app) { m_app = app; }
    void application(const Fl_String &app) { m_app = app; }

    // Finds config file, depending on mode.
    // USER mode finds from ~/.ede/$filename and SYSTEM from $PREFIX/share/ede/$filename
    // if "create" flag is true, path is returned even if file is not found.
    // User MUST NOT free returned pointer!
    static char *find_config_file(const char *filename, bool create=true, int mode=USER);

    // This returns true, if data changed.
    // call flush() to sync changes to file
    bool is_changed() const { return m_changed; }

    const char *strerror() const { return Fl_Config::strerror(m_error); }
    static const char *strerror(int errnum);
    int error() const { return m_error; }

    bool read_file(bool create = true);
    bool flush();

    Section *create_section(const char *path) { Fl_String tmp(path); return create_section(tmp); }
    Section *create_section(const Fl_String &path);
    Section *find_section(Section *sec, const char *name, bool recursive=false) const;
    Section *find_section(const char *path, bool perfect_match=true) const;

    SectionList *section_list(const char *secpath) const { Section *s=find_section(secpath); return s?&s->sections:0; }
    LineList *line_list(const char *secpath) const { Section *s=find_section(secpath); return s?&s->lines:0; }

    //sets section that is used as default
    void set_section(const char *secpath) { set_section(create_section(secpath)); }
    void set_section(Section *sec) { m_cur_sec = sec; }

    void remove_key(const char *section, const char *key);
    void remove_sec(const char *section);

    //These functions assumes that section is set by set_section function!
    int read(const char *key, Fl_String &ret, const char *def_value) { return _read_string(m_cur_sec, key, ret, def_value); }
    int read(const char *key, char *ret, const char *def_value, int size) { return _read_string(m_cur_sec, key, ret, def_value, size); }
    int read(const char *key, char *&ret, const char *def_value=0) { return _read_string(m_cur_sec, key, ret, def_value); }
    int read(const char *key, long &ret, long def_value=0)         { return _read_long(m_cur_sec, key, ret, def_value);   }
    int read(const char *key, int &ret, int def_value=0)           { return _read_int(m_cur_sec, key, ret, def_value);    }
    int read(const char *key, float &ret, float def_value=0)       { return _read_float(m_cur_sec, key, ret, def_value);  }
    int read(const char *key, double &ret, double def_value=0)     { return _read_double(m_cur_sec, key, ret, def_value); }
    int read(const char *key, bool &ret, bool def_value=0)         { return _read_bool(m_cur_sec, key, ret, def_value);   }
    int read(const char *key, Fl_Color &ret, Fl_Color def_value=0) { return _read_color(m_cur_sec, key, ret, def_value);  }

    //These functions assumes that section is set by set_section function!
    int write(const char *key, const Fl_String &value) { return _write_string(m_cur_sec, key, value); }
    int write(const char *key, const char *value)    { return _write_string(m_cur_sec, key, value); }
    int write(const char *key, const long value)     { return _write_long(m_cur_sec, key, value); }
    int write(const char *key, const int value)      { return _write_int(m_cur_sec, key, value); }
    int write(const char *key, const float value)    { return _write_float(m_cur_sec, key, value); }
    int write(const char *key, const double value)   { return _write_double(m_cur_sec, key, value); }
    int write(const char *key, const bool value)     { return _write_bool(m_cur_sec, key, value); }
    int write(const char *key, const Fl_Color value) { return _write_color(m_cur_sec, key, value); }

    //Always give section as first parameter!
    int get(const char *section, const char *key, Fl_String &ret, const char *def_value) { return _read_string(find_section(section), key, ret, def_value); }
    int get(const char *section, const char *key, char *ret, const char *def_value, int size) { return _read_string(find_section(section), key, ret, def_value, size); }
    int get(const char *section, const char *key, char *&ret, const char *def_value=0) { return _read_string(find_section(section), key, ret, def_value); }
    int get(const char *section, const char *key, long &ret, long def_value=0)         { return _read_long(find_section(section), key, ret, def_value);            }
    int get(const char *section, const char *key, int &ret, int def_value=0)           { return _read_int(find_section(section), key, ret, def_value);               }
    int get(const char *section, const char *key, float &ret, float def_value=0)       { return _read_float(find_section(section), key, ret, def_value);         }
    int get(const char *section, const char *key, double &ret, double def_value=0)     { return _read_double(find_section(section), key, ret, def_value);      }
    int get(const char *section, const char *key, bool &ret, bool def_value=0)         { return _read_bool(find_section(section), key, ret, def_value);            }
    int get(const char *section, const char *key, Fl_Color &ret, Fl_Color def_value=0) { return _read_color(find_section(section), key, ret, def_value);   }

    //Always give section as first parameter!
    int set(const char *section, const char *key, const Fl_String &value) { return _write_string(create_section(section), key, value); }
    int set(const char *section, const char *key, const char *value) { return _write_string(create_section(section), key, value); }
    int set(const char *section, const char *key, const long value)  { return _write_long(create_section(section), key, value);   }
    int set(const char *section, const char *key, const int value)   { return _write_int(create_section(section), key, value);    }
    int set(const char *section, const char *key, const float value) { return _write_float(create_section(section), key, value);  }
    int set(const char *section, const char *key, const bool value)  { return _write_double(create_section(section), key, value); }
    int set(const char *section, const char *key, const Fl_Color value) { return _write_color(create_section(section), key, value); }

private:
    int m_error;
    Fl_String m_filename;
    Fl_String m_vendor, m_app;

    Section *m_cur_sec;
    bool m_changed;

    void write_section(int indent, FILE *fp, Section *sec) const;
    Line *create_string(Section *section, const Fl_String &key, const Fl_String &value);
    Line *find_string(Section *section, const char *key);

    int _read_string(Section *s, const char *key, Fl_String &ret, const char *def_value);
    int _read_string(Section *s, const char *key, char *ret, const char *def_value, int size);
    int _read_string(Section *s, const char *key, char *&ret, const char *def_value);
    int _read_long  (Section *s, const char *key, long &ret, long def_value);
    int _read_int   (Section *s, const char *key, int &ret, int def_value);
    int _read_float (Section *s, const char *key, float &ret, float def_value);
    int _read_double(Section *s, const char *key, double &ret, double def_value);
    int _read_bool  (Section *s, const char *key, bool &ret, bool def_value);
    int _read_color(Section *s, const char *key, Fl_Color &ret, Fl_Color def_value);

    int _write_string(Section *s, const char *key, const Fl_String &value);
    int _write_string(Section *s, const char *key, const char *value);
    int _write_long  (Section *s, const char *key, const long value);
    int _write_int   (Section *s, const char *key, const int value);
    int _write_float (Section *s, const char *key, const float value);
    int _write_double(Section *s, const char *key, const double value);
    int _write_bool  (Section *s, const char *key, const bool value);
    int _write_color (Section *s, const char *key, const Fl_Color value);
};

static inline const char* fl_find_config_file(const char *filename, bool create=true) {
    return Fl_Config::find_config_file(filename, create, Fl_Config::USER);
}

#endif
