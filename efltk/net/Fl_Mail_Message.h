/** 
  * Fl_Mail_Message.h
  * This file contains interface to Fl_Mail_Message class .
  * 
  * The source below is under LGPL license.
  *     Information about GNU LGPL: http://www.gnu.org/copyleft/lesser.html
  *
  * Copyright (c) EDE Team. More information about project: http://ede.sf.net
  *
  * Authors (sorted by time they worked on this source file):
  *     Alexey Parshin, alexey§fltk.net
  *     Dejan Lekic, dejan§nu6.org
  *
  * Contributors (ie. people that have sent patches, ideas, suggestions):
  *     Mikko Lahteenmaki, mikko§fltk.net
  *
  * PLEASE report any bug, bugfix, improvement or suggestion to 
  *     efltk-bugs@fltk.net
  ****************************************************************************/

#ifndef __FL_MAIL_MESSAGE_H__
#define __FL_MAIL_MESSAGE_H__

#include <efltk/Fl_String.h>
#include <efltk/Fl_String_List.h>
#include <efltk/Fl_Ptr_List.h>

class Fl_Mail_Message_Part;

/**
 * This class is used by Fl_Mail_Message to hold all eventuall message parts
 */
class Fl_Mail_Message_Part_List 
{
    Fl_Ptr_List     m_messageParts;
public:
    Fl_Mail_Message_Part_List() {}
    ~Fl_Mail_Message_Part_List() { clear(); }

    void clear();
    unsigned count() const { return m_messageParts.count(); }

    void add(Fl_Mail_Message_Part *mpart) { m_messageParts.append(mpart); }

    Fl_Mail_Message_Part& operator [] (unsigned i) { return *(Fl_Mail_Message_Part *)m_messageParts[i]; }
    const Fl_Mail_Message_Part& operator [] (unsigned i) const  { return *(Fl_Mail_Message_Part *)m_messageParts[i]; }
};

/**
 * This class is used for working with parts of Mail messages...
 */
class Fl_Mail_Message_Part 
{
    Fl_String_List              m_messageText;
    Fl_Mail_Message_Part_List   m_messageParts;
    Fl_String                        m_contentType;
    Fl_String                        m_contentTransferEncoding;
protected:
    virtual void parse_headers(unsigned start,unsigned end) {}
    virtual void parse_part() {}
public:
    Fl_Mail_Message_Part(const Fl_String_List& source,unsigned start,unsigned end);
    virtual ~Fl_Mail_Message_Part() {}
};

/**
 * Main class for sending/receiving mails.
 */
class Fl_Mail_Message : Fl_Mail_Message_Part 
{
    Fl_String                       m_returnPath;
    Fl_String                       m_from;
    Fl_String                       m_to;
    Fl_String                       m_subject;
    Fl_String                       m_boundary;
    Fl_String                       m_date;
public:
    Fl_Mail_Message(const Fl_String_List& source) : Fl_Mail_Message_Part(source,0,source.count()) {}
    virtual ~Fl_Mail_Message() {}
    virtual void parse_headers(unsigned start,unsigned end);
    virtual void parse_part();
};

#endif

/***** $Id$
 *     Project: eFLTK
 ***   This source code is released under GNU LGPL License
 *     Copyright (c) EDE Team, 2000-DWYRT  (DWYRT = Date When You Read This)
 ***** Equinox Desktop Environment, http://ede.sf.net */
