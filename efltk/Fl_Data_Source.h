// Fl_Data_Source.h by Alexey Parshin
#ifndef __FL_DATA_SOURCE_H__
#define __FL_DATA_SOURCE_H__

class Fl_Group;

class Fl_Data_Source {
   friend class Fl_Group;
private:
   Fl_Group* parent_;
protected:
   // these methods should be implemented in derived class
   virtual bool         loadData() = 0;
   virtual bool         saveData() = 0;
   virtual const char * read_field(const char *fname) = 0; 
   virtual const char * write_field(const char *fname) = 0; 
public:
   // ctor, dtor
   Fl_Data_Source(Fl_Group *group) { parent_ = group; }
   virtual ~Fl_Data_Source() {}
   
   // load data into widgets
   bool load();
   // unload data from widgets
   bool save();
};

#endif
