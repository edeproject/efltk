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

#include <Fl_Date_Time.h>

enum variantType { CVT_NONE, CVT_INT, CVT_FLOAT, CVT_STRING, CVT_TEXT, CVT_BUFFER, CVT_DATETIME };

class Fl_Variant {
   union variantData {
      int       intData;
      double    floatData;
      double    timeData;
      char *    stringData;
      void *    blobData;
   } m_data;
   int            m_size;
   variantType    m_type;
protected:
   SP_EXPORT void setData(const Fl_Variant &C);
   SP_EXPORT void releaseBuffers();
public:
   SP_EXPORT Fl_Variant() { m_type = CVT_NONE; }
   SP_EXPORT ~Fl_Variant() { releaseBuffers(); }

   SP_EXPORT Fl_Variant& operator =(const Fl_Variant &C) { // ASSIGNMENT OPERATOR.
      if (this == &C) return *this;
      setData(C);
      return *this;
   };

   SP_EXPORT void setInteger(int value);
   SP_EXPORT void setFloat(double value);
   SP_EXPORT void setString(const char * value,int maxlen=0);
   SP_EXPORT void setText(const char * value);
   SP_EXPORT void setBuffer(const void * value,int sz);
   SP_EXPORT void setDateTime(CDateTime value);

   SP_EXPORT int    getInteger() const;
   SP_EXPORT double getFloat() const;
   SP_EXPORT const char * getString() const;
   SP_EXPORT const void * getBuffer() const;
   SP_EXPORT CDateTime getDateTime() const;

   SP_EXPORT variantType dataType() const { return m_type; }
   SP_EXPORT int dataSize() const { return m_size; }
   SP_EXPORT void * dataBuffer() const { return (void *)(variantData *)&m_data; }

   SP_EXPORT operator int () const;
   SP_EXPORT operator double () const;
   SP_EXPORT operator const char * () const;
   SP_EXPORT operator CDateTime () const;
};
//---------------------------------------------------------------------------
#endif
