#include <efltk/Fl_Dialog_DS.h>
#include <efltk/Fl_Group.h>
#include <efltk/Fl_Exception.h>

// Recursive scan of group to find all the widgets
// with defined field names
void Fl_Dialog_DS::scan_widgets(Fl_Group *group) {
    if (!group) group = parent();
    unsigned cnt = group->children();
    for (unsigned i = 0; i < cnt; i++) {
        Fl_Widget *widget = group->child(i);
        if (widget->field_name().length()) {
            m_fields.add(widget->field_name());
            continue;
        }
        if (widget->is_group())
            scan_widgets((Fl_Group *)widget);
    }
    if (group == parent())
        m_widgetsScanned = true;
}

// Set the field value
Fl_Variant& Fl_Dialog_DS::operator [] (const char *field_name) {
    if (!m_widgetsScanned) scan_widgets();
    int fieldIndex = field_index(field_name);
    if (fieldIndex < 0)
        fl_throw("Sorry, the field " + Fl_String(field_name) + " doesn't exist in that dialog.");
    return m_fields[field_name];
}

