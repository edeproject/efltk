/*
*
* $Author$
* $Revision$
* $Log$
* Revision 1.1  2003/05/06 20:57:07  parshin
* 1) Fl_Config_Dialog_DS is added. The example of usage is in test/dialog. This
*    class stores/restores data in Fl_Config section. One Fl_Config may be used by
*    different dialogs.
* 2) Fl_Variant now uses convertors as_xxx() to get data from it. This means that
*    you don't care what's is inside Fl_Variant most of the time - it will try to
*    perform a conversion for you. You may also assign values to and from Fl_Variant
*    without a visible conversion - it will still work in most of the cases :)
*
*/

#include <efltk/Fl_Config_Dialog_DS.h>

bool Fl_Config_Dialog_DS::load_data() { 
    if (!m_config)
        return true; 
    m_config->set_section(m_configSection);
    if (!m_widgetsScanned) scan_widgets();
    for (unsigned i = 0; i < field_count(); i++) {
        Fl_Data_Field&  field = m_fields.field(i);
        Fl_String       value;
        m_config->read(field.name().c_str(), value,"");
        field = value;
    }
    return true; 
}

bool Fl_Config_Dialog_DS::save_data() { 
    if (!m_config)
        return true; 
    m_config->set_section(m_configSection);
    if (!m_widgetsScanned) scan_widgets();
    for (unsigned i = 0; i < field_count(); i++) {
        Fl_Data_Field&  field = m_fields.field(i);
        Fl_String value = field.as_string();
        m_config->write(field.name().c_str(), value);
    }
    return true; 
}
