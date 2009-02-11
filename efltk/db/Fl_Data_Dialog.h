#ifndef FL_DATA_DIALOG_H
#define FL_DATA_DIALOG_H

#include <efltk/Fl_Dialog.h>
#include "Fl_Record_DS.h"

class Fl_Database;

/** Fl_Data_Dialog class
  * designed to easy insert the new or edit the existing
  * record in the database table.
  */
class Fl_Data_Dialog : public Fl_Dialog  {
protected:    
    Fl_Database   *m_database;
    Fl_Record_DS  *m_record_DS;
public:
    /** Constructs new Data Dialog from size and caption*/
    Fl_Data_Dialog(int w,int h,const char *label=0L);

    /** Destroys Data Dialog */
    ~Fl_Data_Dialog();

    /** Fast setup of the database table connection:
      * - database
      * - table name
      * - key field name in the table
      */
    void setup(Fl_Database *db,Fl_String tableName,Fl_String keyField);

    /// properties
    virtual void database(Fl_Database *db)          { m_record_DS->database(db); }
    Fl_Database *database() const                   { return m_record_DS->database(); }

    void       table(const Fl_String tname)         { m_record_DS->table(tname); }
    Fl_String  table() const                        { return m_record_DS->table(); }

    void       key_field(const Fl_String fieldName) { m_record_DS->key_field(fieldName); }
    Fl_String  key_field() const                    { return m_record_DS->key_field(); }

    void       key_value(Fl_Variant val)            { m_record_DS->key_value(val); }
    Fl_Variant key_value() const                    { return m_record_DS->key_value(); }
};

#endif
