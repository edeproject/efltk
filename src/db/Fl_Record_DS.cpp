#include <efltk/Fl_Group.h>
#include <efltk/db/Fl_Record_DS.h>

// Constructor
Fl_Record_DS::Fl_Record_DS(Fl_Group *group,Fl_Database *db,Fl_String tableName="",Fl_String keyField="") 
: Fl_Dialog_DS(group)
{
    m_keyValue = -1;
    m_queriesAreBuilt = false;
    m_selectQuery = new Fl_Query(db);
    m_updateQuery = new Fl_Query(db);
    m_insertQuery = new Fl_Query(db);
    m_saveQuery = NULL;
    m_recordCount = 0;
    m_tableName = tableName;
    m_keyField = keyField;
}

// Destructor
Fl_Record_DS::~Fl_Record_DS() {
    delete m_selectQuery;
    delete m_updateQuery;
    delete m_insertQuery;
}

// Build the set of SQL queries for select, insert, and update.
// If the list of widgets is empty - scan the attached group.
bool Fl_Record_DS::build_queries() {

    if (m_queriesAreBuilt) 
        return true;

    // Find all the widgets with defined field names
    scan_widgets();

    if (!field_count())
        return false;

    Fl_String columnNames;
    Fl_String paramNames;
    Fl_String updateNames;

    m_saveQuery = m_insertQuery;

    for (unsigned i = 0; i < field_count(); i++) {
        Fl_String fieldName = field(i).name();
        if (columnNames.length()) {
            columnNames += "," + fieldName;
            paramNames  += ",:" + fieldName;
            updateNames += "," + fieldName + "=:" + fieldName;
        } else {
            columnNames = fieldName;
            paramNames  = ":" + fieldName;
            updateNames = fieldName + "=:" + fieldName;
        }
    }

    m_selectQuery->sql("SELECT "+columnNames+" FROM "+m_tableName+" WHERE "+m_keyField+"=:key");
    m_insertQuery->sql("INSERT INTO "+m_tableName+"("+columnNames+") VALUES ("+paramNames+")");
    m_updateQuery->sql("UPDATE "+m_tableName+" SET "+updateNames+" WHERE "+m_keyField+"=:key");

    m_queriesAreBuilt = true;

    return true;
}

bool Fl_Record_DS::load_data() {
    if (!build_queries())
        return false;

    puts(m_selectQuery->sql().c_str());

    m_selectQuery->param("key") = m_keyValue;
    m_selectQuery->open();
    if (!m_selectQuery->eof()) {
        m_recordCount = 1;
        m_saveQuery = m_updateQuery;
        // First, loading data into the buffer fields
        for (unsigned i = 0; i < m_selectQuery->field_count(); i++) {
            Fl_Data_Field& src = m_selectQuery->field(i);
            Fl_Data_Field& dst = m_fields.field(src.name());
            dst.value = src.value;
        }
        m_selectQuery->close();
    } else {
        m_recordCount = 0;
    }
    return true;
}

bool Fl_Record_DS::save_data() {
    if (!build_queries())
        return false;

    for (unsigned i = 0; i < field_count(); i++) {
        Fl_Data_Field& src = m_fields.field(i);
        m_saveQuery->param(src.name()) = src.value;
    }

    puts(m_saveQuery->sql().c_str());
    m_updateQuery->param("key") = m_keyValue;
    m_saveQuery->exec();

    return true;
}

// properties
void Fl_Record_DS::database(Fl_Database *db) {
    m_selectQuery->database(db);
    m_updateQuery->database(db);
    m_insertQuery->database(db);
}

Fl_Database *Fl_Record_DS::database() const {
    return m_selectQuery->database();
}

void Fl_Record_DS::table(const Fl_String tname) {
    if (m_tableName != tname) {
        m_tableName = tname;
        m_queriesAreBuilt = false;
    }
}

void Fl_Record_DS::setup(Fl_Database *db,const Fl_String tableName,const Fl_String keyField) {
    database(db);
    table(tableName);
    key_field(keyField);
}

void Fl_Record_DS::key_field(const Fl_String keyField) {
    if (m_keyField != keyField) {
        m_keyField = keyField;
        m_queriesAreBuilt = false;
    }
}

void Fl_Record_DS::key_value(Fl_Variant keyValue) {
    m_keyValue = keyValue;
}

Fl_Variant Fl_Record_DS::key_value() const {
    return m_keyValue;
}
