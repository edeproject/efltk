/***************************************************************************
                          Fl_Masked_Input.cpp - description
                             -------------------
    begin                : Tue Dec 14 1999
    copyright            : (C) 1999-2002 by Alexey Parshin
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

#include <efltk/fl_math.h>
#include <efltk/Fl.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl_Masked_Input.h>
#include <efltk/Fl_Date_Time.h>

#include <string.h>
#include <ctype.h>

// If you define this symbol as zero you will get the peculiar fltk
// behavior where moving off the end of an input field will move the
// cursor into the next field:
// define it as 1 to prevent cursor movement from going to next field:
#define NORMAL_INPUT_MOVE 0

#define ctrl(x) (x^0x40)

static const char maskControlCharacters[] = "@0123456789AaLlZz#Tt";

void Fl_Masked_Input::mask(const char *m) {
   m_mask = m;
   m_inputMask = m;
   m_backgroundMask = m;
   
   char *bg_mask_ptr = m_backgroundMask;
   char *input_mask_ptr = m_inputMask;

   unsigned l = m_mask.length();
   unsigned j = 0;
   for (unsigned i = 0; i < l; i++,j++) {
      if (m[i] == '\\' || !strchr(maskControlCharacters,m[i])) {   // background char
         i++;
         bg_mask_ptr[j] = m[i];
         input_mask_ptr[j] = ' ';
      } else {
         bg_mask_ptr[j] = ' ';
         input_mask_ptr[j] = m[i];
      }
   }
   bg_mask_ptr[j] = 0;
   input_mask_ptr[j] = 0;
}

int Fl_Masked_Input::handle(int event) {

   if (event != FL_KEYBOARD) return Fl_Input::handle(event);

   char ascii = Fl::event_text()[0];

   int del;
   if (Fl::compose(del)) {
      int pos = position();
      char& key = ascii;
      if (pos >= m_inputMask.length())
         return 1;
      return checkCharacter(pos,key);
   }

   return Fl_Input::handle(event);
}

Fl_Masked_Input::Fl_Masked_Input(int x, int y, int w, int h, const char *l)
: Fl_Input(x, y, w, h, l) {
}

bool Fl_Masked_Input::checkCharacterAtPos(int pos,char& key) {
   bool rc = false;
   if (pos >= m_inputMask.length()) return false;
   switch (m_inputMask[pos]) {
   case '@':   // optional character - digit,letter
               rc = true;
               break;
   case 'L':    // capital character, must
               rc = isalpha(key) && key == toupper(key);
               break;
   case 'l':   // small character, must
               rc = isalpha(key) && key != toupper(key);
               break;
   case 'Z':    // capital character, optional
               rc = (isalpha(key) && key == toupper(key)) || key == ' ';
               break;
   case 'z':   // small character, optional
               rc = (isalpha(key) && key != toupper(key)) || key == ' ';
               break;
   case '#':   rc = isdigit(key) || key == ' ';    // optional digit
               break;
   case '0':
   case '1':
   case '2':
   case '3':
   case '4':
   case '5':
   case '6':
   case '7':
   case '8':   // Digit, must
   case '9':   rc = isdigit(key) && key <= m_inputMask[pos];
               break;
   case 'T':   // A/P for AM/PM, must
               rc = key == 'A' || key == 'P';
               break;
   case 't':   // a/p for am/pm, must
               rc = key == 'a' || key == 'p';
               break;
   default :   // background mask char?
               rc = m_backgroundMask[pos] == key;
               break;
   }
   return rc;
}

bool Fl_Masked_Input::checkCharacter(int pos,char& key) {
   char et[] = { 0, 0 };
   int rc = 1;
   int maxPos = m_inputMask.length();
   while (pos < maxPos) {
      if (m_inputMask[pos] == ' ') {
         // use background mask
         et[0] = m_backgroundMask[pos];
         rc = replace(pos, pos+1, et, 1);
         pos++;
         position(pos, Fl::event_state(FL_SHIFT) ? mark() : pos);
      } else {
         if (checkCharacterAtPos(pos,key)) {
            et[0] = key;
            rc = replace(pos, pos+1, et, 1);
            return (rc>0);
         }
         return 1;
      }
   }
   return 1;
}
