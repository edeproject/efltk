/***************************************************************************
                          Fl_Variant.h  -  description
                             -------------------
    begin                : Tue Dec 14 1999
    copyright            : (C) 1999 by Alexey Parshin
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

#ifndef __FL_VARIANT_H__
#define __FL_VARIANT_H__

#include <efltk/Fl_Export.h>
#include <efltk/Fl_Date_Time.h>

class FL_API Fl_Variant {
public:
   enum {
      NONE = 0,
      INT,
      FLOAT,
      STRING,
      TEXT,
      BUFFER,
      DATETIME
   };

   Fl_Variant() { m_type = NONE; }
   ~Fl_Variant() { free_buffers(); }

   void set_int(int value);
   void set_float(double value);
   void set_string(const char * value,int maxlen=0);
   void set_text(const char * value);
   void set_buffer(const void * value,int sz);
   void set_date(Fl_Date_Time value);

   int    get_int() const;
   double get_float() const;
   const char * get_string() const;
   const void * get_buffer() const;
   Fl_Date_Time get_date() const;

   int type() const { return m_type; }
   int size() const { return m_size; }
   void *data() const { return (void *)(variantData *)&m_data; }

   operator int () const;
   operator double () const;
   operator const char * () const;
   operator Fl_Date_Time () const;

   Fl_Variant& operator =(const Fl_Variant &C) { // ASSIGNMENT  OPERATOR
      if (this == &C) return *this;
      set_data(C);
      return *this;
   };

   Fl_Variant& operator =(const char *s) { // ASSIGNMENT  OPERATOR
      set_string(s);
      return *this;
   };

protected:
   void set_data(const Fl_Variant &C);
   void free_buffers();

private:
   union variantData {
      int       intData;
      double    floatData;
      double    timeData;
      char *    stringData;
      void *    blobData;
   } m_data;
   int m_size;
   int m_type;
};
//---------------------------------------------------------------------------
#endif
