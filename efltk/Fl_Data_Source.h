/***************************************************************************
                          Fl_Data_Source.h  -  description
                             -------------------
    begin                : Fri Mar 31 2000
    copyright            : (C) 2000-2002 by Alexey S.Parshin
    email                : alexeyp@m7.tts-sf.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef __FL_DATA_SOURCE_H__
#define __FL_DATA_SOURCE_H__

#include <efltk/Fl_Variant.h>

class Fl_Group;

class Fl_Data_Source {
   friend class Fl_Group;
private:
   Fl_Group* parent_;
protected:
   // these methods should be implemented in derived class
   virtual bool              load_data() = 0;
   virtual bool              save_data() = 0;
public:
   // ctor, dtor
   Fl_Data_Source(Fl_Group *group) { parent_ = group; }
   virtual ~Fl_Data_Source() {}

   // access to the field by name
   virtual const Fl_Variant& operator [] (const char *field_name) const = 0;
   virtual Fl_Variant&       operator [] (const char *field_name) = 0;

   // how many fields do we have in the current record?
   virtual int               field_count() const = 0;
   virtual int               field_index(const char *) const { return -1; }
   
   // access to the field by number, 0..field_count()-1
   virtual const Fl_Variant& operator [] (int) const = 0;
   virtual Fl_Variant&       operator [] (int) = 0;

   virtual bool              read_field(const char *fname,Fl_Variant& value) = 0; 
   virtual bool              write_field(const char *fname,const Fl_Variant& fvalue) = 0; 

   // dataset navigation
   virtual bool              open()  { return true; }
   virtual bool              close() { return true; }
   virtual bool              first() { return true; }
   virtual bool              next()  { return true; }
   virtual bool              prior() { return true; }
   virtual bool              last()  { return true; }
   virtual bool              find(Fl_Variant position) { return true; }

   // load data into widgets
   bool load();
   // unload data from widgets
   bool save();
};

#endif
