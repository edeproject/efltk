// Fl_Data_Source.h by Alexey Parshin
#ifndef __FL_DATA_SOURCE_H__
#define __FL_DATA_SOURCE_H__

class Fl_Data_Source {
   Fl_Group *m_parent;
public:
   // ctor
   Fl_Data_Source(Fl_Group *) {};
   
   // load data into widgets
   bool load();
   // unload data from widgets
   bool save();
};

#endif