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

#include "Fl_Export.h"
#include "Fl_Date_Time.h"

enum variantType { CVT_NONE, CVT_INT, CVT_FLOAT, CVT_STRING, CVT_TEXT, CVT_BUFFER, CVT_DATETIME };

class FL_API Fl_Variant {
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
    void setData(const Fl_Variant &C);
    void releaseBuffers();
public:
    Fl_Variant() { m_type = CVT_NONE; }
    ~Fl_Variant() { releaseBuffers(); }

    Fl_Variant& operator =(const Fl_Variant &C) { // ASSIGNMENT OPERATOR.
      if (this == &C) return *this;
      setData(C);
      return *this;
   };

    void setInteger(int value);
    void setFloat(double value);
    void setString(const char * value,int maxlen=0);
    void setText(const char * value);
    void setBuffer(const void * value,int sz);
    void setDateTime(Fl_Date_Time value);

    int    getInteger() const;
    double getFloat() const;
    const char * getString() const;
    const void * getBuffer() const;
    Fl_Date_Time getDateTime() const;

    variantType dataType() const { return m_type; }
    int dataSize() const { return m_size; }
    void * dataBuffer() const { return (void *)(variantData *)&m_data; }

    operator int () const;
    operator double () const;
    operator const char * () const;
    operator Fl_Date_Time () const;
};
//---------------------------------------------------------------------------
#endif
