#include <efltk/Fl_Dialog_DS.h>

Fl_Variant& Fl_Dialog_DS::operator [] (const char *field_name) {
    int fieldIndex = field_index(field_name);
    if (fieldIndex < 0) m_fields.add(field_name);
    return m_fields[field_name];
}
