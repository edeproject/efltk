/*
* $Id$
*
* Extended Fast Light Toolkit (EFLTK)
* Copyright (C) 2002-2003 by EDE-Team
* WWW: http://www.sourceforge.net/projects/ede
*
* Fast Light Toolkit (FLTK)
* Copyright (C) 1998-2003 by Bill Spitzak and others.
* WWW: http://www.fltk.org
*
* This library is distributed under the GNU LIBRARY GENERAL PUBLIC LICENSE
* version 2. See COPYING for details.
*
* Author : Alexey Parshin
* Email  : alexey@fltk.net
*
* Please report all bugs and problems to "efltk-bugs@fltk.net"
*
*/

#ifndef _FL_IMAP_DS_H_
#define _FL_IMAP_DS_H_

#include <efltk/Fl_Memory_DS.h>
#include <efltk/net/Fl_IMAP_Connect.h>

typedef void (*Fl_Progress_Callback)(int total,int progress);

class Fl_IMAP_DS : public Fl_Memory_DS  {
public:
    // ctor, dtor 
    Fl_IMAP_DS() : Fl_Memory_DS(), m_showpolicy(0), m_fetchbody(false), m_callback(NULL) { }
    virtual ~Fl_IMAP_DS() { close(); }

    enum {
        SHOW_ALL = 0,
        HIDE_MESSAGES = 1,
        HIDE_FOLDERS = 2,
        NO_SORT = 4
    };

    char showpolicy() const         { return m_showpolicy; }
    void showpolicy(char type)      { m_showpolicy = type; }

    void host(Fl_String host_name)  { m_imap.host(host_name); }
    Fl_String host() const          { return m_imap.host(); }

    void user(Fl_String usr)        { m_user = usr; }    
    Fl_String user() const          { return m_user; }    
    void password(Fl_String pwd)    { m_password = pwd; }    
    Fl_String password() const      { return m_password; }    

    void folder(const char *d) { m_folder = d; }
    void folder(const Fl_String &d) { m_folder = d; }
    const Fl_String &folder() const { return m_folder; }

    void fetchbody(bool fb)         { m_fetchbody = fb; }
    bool fetchbody() const          { return m_fetchbody; }

    // dataset navigation
    virtual bool              open();

    void callback(Fl_Progress_Callback cb) { m_callback = cb; }
private:
    Fl_IMAP_Connect     m_imap;    
    Fl_String           m_folder;
    char                m_showpolicy;
    Fl_String           m_user;
    Fl_String           m_password;
    bool                m_fetchbody;
    Fl_Progress_Callback m_callback;
};

#endif
