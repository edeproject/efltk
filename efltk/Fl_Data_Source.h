// Fl_Data_Source.h by Alexey Parshin
#ifndef __FL_DATA_SOURCE_H__
#define __FL_DATA_SOURCE_H__

class Fl_Data_Source {
   Fl_Group *m_parent;
protected:
   // these methods should be implemented in derived class
   virtual bool loadData() = 0;
   virtual bool saveData() = 0; 
public:
   // ctor, dtor
   Fl_Data_Source(Fl_Group *group) { m_parent = group; }
   virtual ~Fl_Data_Source(Fl_Group *) {}
   
   // load data into widgets
   bool load() { return loadData(); }
   // unload data from widgets
   bool save() { return saveData(); }
};

#endif
