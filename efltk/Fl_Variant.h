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

class Fl_Image;

enum Fl_Variant_Type {
      VAR_NONE     = 0,
      VAR_INT      = 1,
      VAR_FLOAT    = 2,
      VAR_STRING   = 4,
      VAR_TEXT     = 8,
      VAR_BUFFER   = 16,
      VAR_DATETIME = 32,
      VAR_IMAGEPTR = 64
   };

class FL_API Fl_Variant {
public:
   Fl_Variant() { m_type = VAR_NONE; }
   ~Fl_Variant() { free_buffers(); }

   void set_int(int value);
   void set_float(double value);
   void set_string(const char * value,int maxlen=0);
   void set_text(const char * value);
   void set_buffer(const void * value,int sz);
   void set_image_ptr(const Fl_Image * value);
   void set_date(Fl_Date_Time value);

   int    get_int() const;
   double get_float() const;
   const char * get_string() const;
   const void * get_buffer() const;
   const Fl_Image * get_image_ptr() const;
   Fl_Date_Time get_date() const;

   Fl_Variant_Type type() const { return m_type; }
   int size() const { return m_size; }
   void *data() const { return (void *)(variantData *)&m_data; }

   operator int () const;
   operator double () const;
   operator const char * () const;
   operator const Fl_Image * () const;
   operator Fl_Date_Time () const;

   // ASSIGNMENT OPERATORS
   Fl_Variant& operator =(const Fl_Variant &C) {
      if (this == &C) return *this;
      set_data(C);
      return *this;
   };

   Fl_Variant& operator =(const char *s) {
      set_string(s);
      return *this;
   };

   Fl_Variant& operator =(int v) {
      set_int(v);
      return *this;
   };

   Fl_Variant& operator =(double v) {
      set_float(v);
      return *this;
   };

   Fl_Variant& operator =(Fl_Date_Time dt) {
      set_date(dt);
      return *this;
   };

   Fl_Variant& operator =(const Fl_Image *pm) {
      set_image_ptr(pm);
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
      char      *stringData;
      void      *blobData;
      const Fl_Image *imagePtr;
   } m_data;
   int m_size;
   Fl_Variant_Type m_type;
};
//---------------------------------------------------------------------------
#endif
