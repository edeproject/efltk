/***************************************************************************
                          Fl_Masked_Input.h - description
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

#ifndef Fl_Masked_Input_H
#define Fl_Masked_Input_H

#include <efltk/Fl_Input.h>
#include <efltk/Fl_String.h>

class FL_API Fl_Masked_Input : public Fl_Input {
   Fl_String   m_mask;
   Fl_String   m_inputMask;
   Fl_String   m_backgroundMask;

   bool        checkCharacterAtPos(int pos,char& key);
   bool        checkCharacter(int pos,char& key);
public:
   Fl_Masked_Input(int,int,int,int,const char * = 0);

   int  handle(int event);

   void mask(const char *m);
   const char *mask() const  { return m_mask.c_str(); }
};

#endif 
