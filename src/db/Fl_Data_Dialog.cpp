#include <efltk/db/Fl_Database.h>
#include <efltk/db/Fl_Query.h>
#include <efltk/Fl_Tabs.h>
#include <efltk/db/Fl_Data_Dialog.h>

// Constructor
// Fake (Fl_Data_Source *)0x1 blocks the default internal
// datasource creation
Fl_Data_Dialog::Fl_Data_Dialog(int w,int h,const char *label)
: Fl_Dialog(w,h,label,(Fl_Data_Source *)0x1) {
    m_database  = NULL;
    m_record_DS = new Fl_Record_DS();
    m_record_DS->parent(m_tabs);
    data_source(m_record_DS);
}

Fl_Data_Dialog::~Fl_Data_Dialog() {
    delete m_record_DS;
}

// Fast data connection setup
void Fl_Data_Dialog::setup(Fl_Database *db,Fl_String tableName,Fl_String keyField) {
    m_record_DS->setup(db,tableName,keyField);
}
