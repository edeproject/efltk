#ifndef __FL_RECORD_DS_H__
#define __FL_RECORD_DS_H__

#include <efltk/Fl_Map.h>
#include <efltk/Fl_String.h>
#include <efltk/Fl_Data_Source.h>
#include <efltk/db/Fl_Query.h>
#include <efltk/db/Fl_Database.h>
#include <efltk/Fl_Dialog_DS.h>
#include <efltk/Fl_Variant.h>

class FL_API Fl_Record_DS : public Fl_Dialog_DS {
protected:
    Fl_String           m_tableName;
    Fl_String           m_keyField;
    Fl_Variant          m_keyValue;
    bool                m_queriesAreBuilt;
    Fl_Query           *m_selectQuery;
    Fl_Query           *m_updateQuery;
    Fl_Query           *m_insertQuery;
    Fl_Query           *m_saveQuery;
    int                 m_recordCount;

    virtual bool build_queries();

public:
    Fl_Record_DS(Fl_Group *group,Fl_Database *db=NULL,Fl_String tableName="",Fl_String keyField="");
    ~Fl_Record_DS();

    /// how many rows do we have ds?
    virtual unsigned record_count() const { return m_recordCount; }

    /// fast setup of data connection
    void       setup(Fl_Database *db,const Fl_String tableName,const Fl_String keyField);

    /// properties
    virtual void database(Fl_Database *);
    Fl_Database *database() const;

    void       table(const Fl_String tname);
    Fl_String  table() const { return m_tableName; }

    void       key_field(const Fl_String);
    Fl_String  key_field() const { return m_keyField; }

    void       key_value(Fl_Variant);
    Fl_Variant key_value() const;

    /// Actual database operations
    virtual bool load_data();
    virtual bool save_data();
};

#endif
