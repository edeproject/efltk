/*
*
* $Author$
* $Revision$
* $Log$
* Revision 1.1  2003/05/06 20:57:02  parshin
* 1) Fl_Config_Dialog_DS is added. The example of usage is in test/dialog. This
*    class stores/restores data in Fl_Config section. One Fl_Config may be used by
*    different dialogs.
* 2) Fl_Variant now uses convertors as_xxx() to get data from it. This means that
*    you don't care what's is inside Fl_Variant most of the time - it will try to
*    perform a conversion for you. You may also assign values to and from Fl_Variant
*    without a visible conversion - it will still work in most of the cases :)
*
*/

#ifndef _FL_CONFIG_DIALOG_DS_H_
#define _FL_CONFIG_DIALOG_DS_H_

#include <efltk/Fl_Config.h>
#include <efltk/Fl_String.h>
#include <efltk/Fl_Dialog_DS.h>

/** Fl_Config_Dialog_DS is designed to support a configuration dialogs
  * which store the widgets' data into config files. It is used with the 
  * Fl_Dialog class as a Datasource.
  */
class Fl_Config_Dialog_DS : public Fl_Dialog_DS {
    Fl_Config                     *m_config;
    Fl_String                      m_configSection;

public:
    /** Constructor uses the existing Fl_Config object and a section name in the
      * config file.
      */
    Fl_Config_Dialog_DS(Fl_Config *cfg,Fl_String section) : Fl_Dialog_DS() { m_config = cfg; m_configSection = section; }

    Fl_Config *config() const { return m_config; }
    Fl_String  section() const { return m_configSection; }

protected:
    virtual bool              load_data();
    virtual bool              save_data();
};

#endif
