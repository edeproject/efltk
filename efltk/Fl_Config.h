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
#include "Fl_Util.h"
#include "Fl_String.h"
#include "Fl_Color.h"
#include "Fl_Ptr_List.h"
#include "Fl_Map.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32_WCE
#include "x.h"
#endif

/**
 * \defgroup Fl_Config Fl_Config globals
 */
/*@{*/

/**
 * Error codes for Fl_Config
 */
enum ConfErrors {
    CONF_SUCCESS = 0,   ///< successful operation
    CONF_ERR_FILE,      ///< trouble accessing config file or directory
    CONF_ERR_SECTION,   ///< requested section was not found
    CONF_ERR_KEY,       ///< requested key was not found
    CONF_ERR_MEMORY,    ///< memory allocation error
    CONF_ERR_NOVALUE,   ///< key found, but invalid value associated with it
};

/** List used for sections in Fl_Config_Section */
typedef Fl_Ptr_List Fl_Config_Sections;

/** Map used for entries in Fl_Config_Section */
typedef Fl_String_String_Map Fl_Config_Lines;

/*@}*/

class Fl_Config;

/**
 * The configuration section.
 * Represents one section in config (ini) file.
 * @see Fl_Config
 */
class FL_API Fl_Config_Section
{
    friend class Fl_Config;
public:
    Fl_Config_Section(const Fl_String &name, const Fl_String &path, Fl_Config_Section *par);
    virtual ~Fl_Config_Section();

    /**
     * Destroys all sections and entries.
     */
    virtual void clear();

    /**
     * Returns pointer to parent section, NULL for Fl_Config (root)
     */
    Fl_Config_Section *parent() const { return m_parent; }

    /**
     * Returns name of section, without path.
     * @see path()
     */
    const Fl_String &name() const { return m_name; }

    /**
     * Returns path to section, without name.
     * @see name()
     */
    const Fl_String &path() const { return m_path; }

    /**
     * Returns const reference to entry map.
     */
    const Fl_Config_Lines &lines() const { return m_lines; }

    /**
     * Returns reference to entry map.
     */
    Fl_Config_Lines &lines() { return m_lines; }

    /**
     * Returns const reference to section list.
     */
    const Fl_Config_Sections &sections() const { return m_sections; }

    /**
     * Returns reference to section list.
     */
    Fl_Config_Sections &sections() { return m_sections; }

    /**
     * Find section named 'name'.
     * @param name of section to find
     * @param recursive set true to perform recursive search.
     */
    Fl_Config_Section *find_section(const char *name, bool recursive=false) const;

protected:
    Fl_Config_Section *m_parent;
    Fl_String m_name, m_path;

    Fl_Config_Lines m_lines; //Line map
    Fl_Config_Sections m_sections; //Section list

    void write_section(int indent, FILE *fp) const;

    void add_entry(const Fl_String &key, const Fl_String &value);
    bool remove_entry(const Fl_String &key);
    Fl_String *find_entry(const char *key) const;
};

/**
 * The configuration holder. This class maybe used very easily to
 * store application settings to file. Either system wide or user specific,
 * depending on config type. Fl_Config is derived Fl_Config_Section, please
 * take look a look at functions it provides also.
 * @see Fl_Config_Section
 */
class FL_API Fl_Config : public Fl_Config_Section {
public:

    /**
     * Config file modes
     */
    enum ConfigType {
        USER=1, ///< User specific config file
        SYSTEM  ///< System wide config file
    };

    /**
     * Creates/reads/writes app specific config file.
     *
     * LINUX:<br>
     * File is created in ($home)/.ede/apps/($application)/($application).conf
     * Or ($prefix)/share/ede/apps/($application)/($application).conf
     *
     * <br>WIN32:<br>
     * ($home)\Local Settings\.ede\apps\($application)/($application).conf
     * Or ($common files)\($application)\($application).conf
     *
     * Location depends on ConfigType 'mode', USER or SYSTEM
     *
     * @param vendor aplication vendor, written down to file
     * @param application name, written down to file
     * @param mode which mode to use
     */
    Fl_Config(const char *vendor, const char *application, int mode=USER);

    /**
     * Access custom file in filesystem.
     *
     * @param filename path to config (ini) file.
     * @param readfile if true, file is readed on constructor. I.e no need for read_file()
     * @param createfile if true, file is created if it doesn't exists.
     */
    Fl_Config(const char *filename, bool readfile=true, bool createfile=true);

    /**
     * Destroys config
     */
    virtual ~Fl_Config();

    /**
     * Finds config file, depending on mode.
     * NOTE: User MUST NOT free returned pointer!
     *
     * LINUX:<br>
     * File is created in ($home)/.ede/apps/($application)/($application).conf
     * Or ($prefix)/share/ede/apps/($application)/($application).conf
     *
     * <br>WIN32:<br>
     * ($home)\Local Settings\.ede\apps\($application)/($application).conf
     * Or ($common files)\($application)\($application).conf
     *
     * @param filename Relative filename, e.g. "myapp_config.ini"
     * @param create if true, path is returned even if file is not found. Otherwise NULL if path not found.
     * @param mode which mode to use
     */
    static char *find_config_file(const char *filename, bool create=true, int mode=USER);


    /**
     * (re)read file. NOTE: Deletes current entries from this Fl_Config object.
     * @param create if true, file is created if it doesn't exists.
     * @see filename()
     */
    bool read_file(bool create = true);

    /**
     * Flush entries to file.
     * Returns true on success.
     * @see filename()
     */
    bool flush();

    /** Returns current filename. */
    const Fl_String &filename() const { return m_filename; }
    /** Set new filename. You need to call read_file() to get new entries. */
    void filename(const char *filename) { m_filename = filename; }
    /** Set new filename. You need to call read_file() to get new entries. */
    void filename(const Fl_String &filename) { m_filename = filename; }

    /** Returns current vendor name. */
    const Fl_String &vendor() const { return m_vendor; }
    /** Set new vendor name. */
    void vendor(const char *vendor) { m_vendor = vendor; }
    /** Set new vendor name. */
    void vendor(const Fl_String &vendor) { m_vendor = vendor; }

    /** Returns current application name. */
    const Fl_String &application() const { return m_app; }
    /** Set new application name. */
    void application(const char *app) { m_app = app; }
    /** Set new application name. */
    void application(const Fl_String &app) { m_app = app; }

    /**
     * Returns true, if data changed.
     * call flush() to sync changes to file
     * @see flush()
     */
    bool is_changed() const { return m_changed; }

    /**
     * Set changed, forces flush() to write file.
     * Even if it is not changed.
     */
    void set_changed() { m_changed = true; }

    /**
     * Returns last error happened.
     */
    int error() const { return m_error; }

    /**
     * Reset error, normally you don't need to call this.
     */
    void reset_error() { m_error = 0; }

    /**
     * Return string presentation for last happened error.
     */
    const char *strerror() const { return Fl_Config::strerror(m_error); }

    /**
     * Return error string, associated with 'errnum'
     */
    static const char *strerror(int errnum);

    /**
     * Create new section. You can pass full path as section name.
     * For example: create_section("/path/to/my/section");
     * All nested sections are created automatically.
     *
     * Returns pointer to created section, NULL if failed.
     */
    Fl_Config_Section *create_section(const char *path) { Fl_String tmp(path); return create_section(tmp); }

    /**
     * Create new section. You can pass full path as section name.
     * For example: create_section("/path/to/my/section");
     * All nested sections are created automatically.
     *
     * Returns pointer to created section, NULL if failed.
     */
    Fl_Config_Section *create_section(const Fl_String &path);

    /**
     * Find section. You can pass full path as section name.
     * For example: find_section("/path/to/my/section");
     *
     * Returns pointer to found section, NULL if not found.
     *
     * @param perfect_match is true, it returns NULL if no exact section found. Otherwise it returns last found section in path.
     */
    Fl_Config_Section *find_section(const char *path, bool perfect_match=true) const;

    /**
     * Return child sections of section specified 'secpath'
     */
    Fl_Config_Sections *section_list(const char *secpath) const { Fl_Config_Section *s=find_section(secpath); return s ? (&s->sections()) : 0; }

    /**
     * Return entries of section specified 'secpath'
     */
    Fl_Config_Lines *line_list(const char *secpath) const { Fl_Config_Section *s=find_section(secpath); return s ? (&s->lines()) : 0; }

    /**
     * Set default section for read/write operations.
     * NOTE: section is created, if it's not found.<BR>
     * NOTE: You can pass path to section e.g "/path/to/my/section"
     */
    void set_section(const char *secpath) { set_section(create_section(secpath)); }

    /**
     * Set default section for read/write operations.
     */
    void set_section(Fl_Config_Section *sec) { m_cur_sec = sec; }

    /**
     * Remove entry associated with 'key' from section.
     * NOTE: You can pass path to section e.g "/path/to/my/section"
     */
    void remove_key(const char *section, const char *key);

    /**
     * Remove section specified by 'section'.
     * NOTE: You can pass path to section e.g "/path/to/my/section"
     */
    void remove_sec(const char *section);


    /**
     * Read Fl_String entry from config.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: This function assumes that current section is set with set_section().
     *
     * @param key Key to entry.
     * @param ret Result is stored to this.
     * @param def_value Default value for ret, if not found.
     */
    int read(const char *key, Fl_String &ret, const char *def_value) { return _read_string(m_cur_sec, key, ret, def_value); }

    /**
     * Read char* entry from config.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: This function assumes that current section is set with set_section().
     *
     * @param key Key to entry.
     * @param ret Result is stored to this.
     * @param def_value Default value for ret, if not found.
     * @param size of 'ret' char* array.
     */
    int read(const char *key, char *ret, const char *def_value, int size) { return _read_string(m_cur_sec, key, ret, def_value, size); }

    /**
     * Read char* entry from config.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: 'ret' is allocated by Fl_Confing, user MUST free 'ret' by calling free() function.
     * NOTE: This function assumes that current section is set with set_section().
     *
     * @param key Key to entry.
     * @param ret Result is stored to this.
     * @param def_value Default value for ret, if not found.
     */
    int read(const char *key, char *&ret, const char *def_value=0) { return _read_string(m_cur_sec, key, ret, def_value); }

    /**
     * Read long entry from config.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: This function assumes that current section is set with set_section().
     *
     * @param key Key to entry.
     * @param ret Result is stored to this.
     * @param def_value Default value for ret, if not found.
     */
    int read(const char *key, long &ret, long def_value=0)         { return _read_long(m_cur_sec, key, ret, def_value);   }

    /**
     * Read int entry from config.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: This function assumes that current section is set with set_section().
     *
     * @param key Key to entry.
     * @param ret Result is stored to this.
     * @param def_value Default value for ret, if not found.
     */
    int read(const char *key, int &ret, int def_value=0)           { return _read_int(m_cur_sec, key, ret, def_value);    }

    /**
     * Read float entry from config.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: This function assumes that current section is set with set_section().
     *
     * @param key Key to entry.
     * @param ret Result is stored to this.
     * @param def_value Default value for ret, if not found.
     */
    int read(const char *key, float &ret, float def_value=0)       { return _read_float(m_cur_sec, key, ret, def_value);  }

    /**
     * Read double entry from config.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: This function assumes that current section is set with set_section().
     *
     * @param key Key to entry.
     * @param ret Result is stored to this.
     * @param def_value Default value for ret, if not found.
     */
    int read(const char *key, double &ret, double def_value=0)     { return _read_double(m_cur_sec, key, ret, def_value); }

    /**
     * Read bool entry from config.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: This function assumes that current section is set with set_section().
     *
     * @param key Key to entry.
     * @param ret Result is stored to this.
     * @param def_value Default value for ret, if not found.
     */
    int read(const char *key, bool &ret, bool def_value=0)         { return _read_bool(m_cur_sec, key, ret, def_value);   }

    /**
     * Read Fl_Color entry from config.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: This function assumes that current section is set with set_section().
     *
     * @param key Key to entry.
     * @param ret Result is stored to this.
     * @param def_value Default value for ret, if not found.
     */
    int read(const char *key, Fl_Color &ret, Fl_Color def_value=0) { return _read_color(m_cur_sec, key, ret, def_value);  }


    /**
     * Write Fl_String entry to config. You must call flush() to sunc changes to file.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: This function assumes that current section is set with set_section().
     *
     * @param key Key to entry.
     * @param value value to set. if entry with 'key' exists, value is replaced.
     */
    int write(const char *key, const Fl_String &value) { return _write_string(m_cur_sec, key, value); }

    /**
     * Write const char* entry to config. You must call flush() to sunc changes to file.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: This function assumes that current section is set with set_section().
     *
     * @param key Key to entry.
     * @param value value to set. if entry with 'key' exists, value is replaced.
     */
    int write(const char *key, const char *value)    { return _write_string(m_cur_sec, key, value); }

    /**
     * Write long entry to config. You must call flush() to sunc changes to file.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: This function assumes that current section is set with set_section().
     *
     * @param key Key to entry.
     * @param value value to set. if entry with 'key' exists, value is replaced.
     */
    int write(const char *key, const long value)     { return _write_long(m_cur_sec, key, value); }

    /**
     * Write int entry to config. You must call flush() to sunc changes to file.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: This function assumes that current section is set with set_section().
     *
     * @param key Key to entry.
     * @param value value to set. if entry with 'key' exists, value is replaced.
     */
    int write(const char *key, const int value)      { return _write_int(m_cur_sec, key, value); }

    /**
     * Write float entry to config. You must call flush() to sunc changes to file.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: This function assumes that current section is set with set_section().
     *
     * @param key Key to entry.
     * @param value value to set. if entry with 'key' exists, value is replaced.
     */
    int write(const char *key, const float value)    { return _write_float(m_cur_sec, key, value); }

    /**
     * Write double entry to config. You must call flush() to sunc changes to file.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: This function assumes that current section is set with set_section().
     *
     * @param key Key to entry.
     * @param value value to set. if entry with 'key' exists, value is replaced.
     */
    int write(const char *key, const double value)   { return _write_double(m_cur_sec, key, value); }

    /**
     * Write bool entry to config. You must call flush() to sunc changes to file.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: This function assumes that current section is set with set_section().
     *
     * @param key Key to entry.
     * @param value value to set. if entry with 'key' exists, value is replaced.
     */
    int write(const char *key, const bool value)     { return _write_bool(m_cur_sec, key, value); }

    /**
     * Write Fl_Color entry to config. You must call flush() to sunc changes to file.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: This function assumes that current section is set with set_section().
     *
     * @param key Key to entry.
     * @param value value to set. if entry with 'key' exists, value is replaced.
     */
    int write(const char *key, const Fl_Color value) { return _write_color(m_cur_sec, key, value); }


    /**
     * Read Fl_String entry from config.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: section must be set as first parameter!
     *
     * @param section Section for entry
     * @param key Key to entry.
     * @param ret Result is stored to this.
     * @param def_value Default value for ret, if not found.
     */
    int get(const char *section, const char *key, Fl_String &ret, const char *def_value) { return _read_string(find_section(section), key, ret, def_value); }

    /**
     * Read char* entry from config.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: section must be set as first parameter!
     *
     * @param section Section for entry
     * @param key Key to entry.
     * @param ret Result is stored to this.
     * @param def_value Default value for ret, if not found.
     */
    int get(const char *section, const char *key, char *ret, const char *def_value, int size) { return _read_string(find_section(section), key, ret, def_value, size); }

    /**
     * Read char* entry from config.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: 'ret' is allocated by Fl_Confing, user MUST free 'ret' by calling free() function.
     * NOTE: section must be set as first parameter!
     *
     * @param section Section for entry
     * @param key Key to entry.
     * @param ret Result is stored to this.
     * @param def_value Default value for ret, if not found.
     */
    int get(const char *section, const char *key, char *&ret, const char *def_value=0) { return _read_string(find_section(section), key, ret, def_value); }

    /**
     * Read long entry from config.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: section must be set as first parameter!
     *
     * @param section Section for entry
     * @param key Key to entry.
     * @param ret Result is stored to this.
     * @param def_value Default value for ret, if not found.
     */
    int get(const char *section, const char *key, long &ret, long def_value=0)         { return _read_long(find_section(section), key, ret, def_value);            }

    /**
     * Read int entry from config.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: section must be set as first parameter!
     *
     * @param section Section for entry
     * @param key Key to entry.
     * @param ret Result is stored to this.
     * @param def_value Default value for ret, if not found.
     */
    int get(const char *section, const char *key, int &ret, int def_value=0)           { return _read_int(find_section(section), key, ret, def_value);               }

    /**
     * Read float entry from config.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: section must be set as first parameter!
     *
     * @param section Section for entry
     * @param key Key to entry.
     * @param ret Result is stored to this.
     * @param def_value Default value for ret, if not found.
     */
    int get(const char *section, const char *key, float &ret, float def_value=0)       { return _read_float(find_section(section), key, ret, def_value);         }

    /**
     * Read double entry from config.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: section must be set as first parameter!
     *
     * @param section Section for entry
     * @param key Key to entry.
     * @param ret Result is stored to this.
     * @param def_value Default value for ret, if not found.
     */
    int get(const char *section, const char *key, double &ret, double def_value=0)     { return _read_double(find_section(section), key, ret, def_value);      }

    /**
     * Read bool entry from config.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: section must be set as first parameter!
     *
     * @param section Section for entry
     * @param key Key to entry.
     * @param ret Result is stored to this.
     * @param def_value Default value for ret, if not found.
     */
    int get(const char *section, const char *key, bool &ret, bool def_value=0)         { return _read_bool(find_section(section), key, ret, def_value);            }

    /**
     * Read Fl_Color entry from config.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: section must be set as first parameter!
     *
     * @param section Section for entry
     * @param key Key to entry.
     * @param ret Result is stored to this.
     * @param def_value Default value for ret, if not found.
     */
    int get(const char *section, const char *key, Fl_Color &ret, Fl_Color def_value=0) { return _read_color(find_section(section), key, ret, def_value);   }


    /**
     * Write Fl_String entry to config. You must call flush() to sunc changes to file.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: section must be set as first parameter!
     *
     * @param section Section for entry
     * @param key Key to entry.
     * @param value value to set. if entry with 'key' exists, value is replaced.
     */
    int set(const char *section, const char *key, const Fl_String &value) { return _write_string(create_section(section), key, value); }

    /**
     * Write const char *entry to config. You must call flush() to sunc changes to file.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: section must be set as first parameter!
     *
     * @param section Section for entry
     * @param key Key to entry.
     * @param value value to set. if entry with 'key' exists, value is replaced.
     */
    int set(const char *section, const char *key, const char *value) { return _write_string(create_section(section), key, value); }

    /**
     * Write long entry to config. You must call flush() to sunc changes to file.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: section must be set as first parameter!
     *
     * @param section Section for entry
     * @param key Key to entry.
     * @param value value to set. if entry with 'key' exists, value is replaced.
     */
    int set(const char *section, const char *key, const long value)  { return _write_long(create_section(section), key, value);   }

    /**
     * Write int entry to config. You must call flush() to sunc changes to file.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: section must be set as first parameter!
     *
     * @param section Section for entry
     * @param key Key to entry.
     * @param value value to set. if entry with 'key' exists, value is replaced.
     */
    int set(const char *section, const char *key, const int value)   { return _write_int(create_section(section), key, value);    }

    /**
     * Write float entry to config. You must call flush() to sunc changes to file.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: section must be set as first parameter!
     *
     * @param section Section for entry
     * @param key Key to entry.
     * @param value value to set. if entry with 'key' exists, value is replaced.
     */
    int set(const char *section, const char *key, const float value) { return _write_float(create_section(section), key, value);  }

    /**
     * Write bool entry to config. You must call flush() to sunc changes to file.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: section must be set as first parameter!
     *
     * @param section Section for entry
     * @param key Key to entry.
     * @param value value to set. if entry with 'key' exists, value is replaced.
     */
    int set(const char *section, const char *key, const bool value)  { return _write_double(create_section(section), key, value); }

    /**
     * Write Fl_Color entry to config. You must call flush() to sunc changes to file.
     * Returns CONF_SUCCESS on success, otherwise errorcode.
     * NOTE: section must be set as first parameter!
     *
     * @param section Section for entry
     * @param key Key to entry.
     * @param value value to set. if entry with 'key' exists, value is replaced.
     */
    int set(const char *section, const char *key, const Fl_Color value) { return _write_color(create_section(section), key, value); }

private:
    int m_error;
    Fl_String m_filename;
    Fl_String m_vendor, m_app;

    Fl_Config_Section *m_cur_sec;
    bool m_changed;

    int _read_string(Fl_Config_Section *s, const char *key, Fl_String &ret, const char *def_value);
    int _read_string(Fl_Config_Section *s, const char *key, char *ret, const char *def_value, int size);
    int _read_string(Fl_Config_Section *s, const char *key, char *&ret, const char *def_value);
    int _read_long  (Fl_Config_Section *s, const char *key, long &ret, long def_value);
    int _read_int   (Fl_Config_Section *s, const char *key, int &ret, int def_value);
    int _read_float (Fl_Config_Section *s, const char *key, float &ret, float def_value);
    int _read_double(Fl_Config_Section *s, const char *key, double &ret, double def_value);
    int _read_bool  (Fl_Config_Section *s, const char *key, bool &ret, bool def_value);
    int _read_color (Fl_Config_Section *s, const char *key, Fl_Color &ret, Fl_Color def_value);

    int _write_string(Fl_Config_Section *s, const char *key, const Fl_String &value);
    int _write_string(Fl_Config_Section *s, const char *key, const char *value);
    int _write_long  (Fl_Config_Section *s, const char *key, const long value);
    int _write_int   (Fl_Config_Section *s, const char *key, const int value);
    int _write_float (Fl_Config_Section *s, const char *key, const float value);
    int _write_double(Fl_Config_Section *s, const char *key, const double value);
    int _write_bool  (Fl_Config_Section *s, const char *key, const bool value);
    int _write_color (Fl_Config_Section *s, const char *key, const Fl_Color value);
};

// Backward compatibility...
static inline const char* fl_find_config_file(const char *filename, bool create=true) {
    return Fl_Config::find_config_file(filename, create, Fl_Config::USER);
}

#endif
