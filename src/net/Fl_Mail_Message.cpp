/** 
  * Fl_Mail_Message implementation.
  * This file contains implementation of Fl_Mail_Message (and related) classes.
  * 
  * The source below is under LGPL license.
  *     Information about GNU LGPL: http://www.gnu.org/copyleft/lesser.html
  *
  * Copyright (c) EDE Team. More information about project: http://ede.sf.net
  *
  * Authors (sorted by time they worked on this source file):
  * 	Alexey Parshin, alexey§fltk.net
  * 	Dejan Lekic, dejan§nu6.org
  *
  * Contributors (ie. people that have sent patches, ideas, suggestions):
  *     Mikko Lahteenmaki, mikko§fltk.net
  *
  * PLEASE report any bug, bugfix, improvement or suggestion to 
  * 	efltk-bugs@fltk.net
  ****************************************************************************/
  
#include <efltk/net/Fl_Mail_Message.h>

Fl_Mail_Message_Part::Fl_Mail_Message_Part(const Fl_String_List& source,unsigned start,unsigned end) {
    for (unsigned i = start; i <= end; i++ )
        m_messageText.append(source[i]);
}

void Fl_Mail_Message_Part_List::clear() {
    for (unsigned i = 0; i < m_messageParts.count(); i++ )
        delete (Fl_Mail_Message_Part *)m_messageParts[i];
}

/***** $Id$
 *     Project: eFLTK
 ***   This source code is released under GNU LGPL License
 *     Copyright (c) EDE Team, 2000-DWYRT  (DWYRT = Date When You Read This)
 ***** Equinox Desktop Environment, http://ede.sf.net */
