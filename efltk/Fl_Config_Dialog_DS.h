#ifndef _FL_CONFIG_DIALOG_DS_H_
#define _FL_CONFIG_DIALOG_DS_H_

#include <efltk/Fl_Config.h>
#include <efltk/Fl_String.h>
#include <efltk/Fl_Dialog_DS.h>

/** 
 * Fl_Config_Dialog_DS is designed to support a configuration dialogs
 * which store the widgets' data into config files. It is used with the 
 * Fl_Dialog class as a Datasource.
 *
 * Each tab label in dialog are used as section name. For example all data
 * under [General] tab are found in [General] section in config file.
 */
class Fl_Config_Dialog_DS : public Fl_Dialog_DS 
{
    Fl_Config *m_config;
public:
    /** 
	 * Constructor uses the existing Fl_Config object and a section name in the
     * config file.
     */
    Fl_Config_Dialog_DS(Fl_Config *cfg) : Fl_Dialog_DS() { m_config = cfg; }

	/**
	 * Return Fl_Config of this datasource.
	 */
    Fl_Config *config() const { return m_config; }

protected:
    virtual bool load_data();
    virtual bool save_data();
};

#endif
