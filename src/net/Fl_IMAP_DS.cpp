/***************************************************************************
                                                    Fl_IMAP_DS.cpp  -  description
                                                          -------------------
        begin                : Thu Nov 28 2002
        copyright            : (C) 2002 by Alexey Parshin
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

#include <config.h>

#include <efltk/net/Fl_IMAP_DS.h>
#include <efltk/Fl_Exception.h>
#include <efltk/Fl_Pixmap.h>

#include <stdlib.h>

#ifndef _WIN32
# include <unistd.h>
#endif

// REPLACE WITH XPM, now it's GIF
static const unsigned char exec_xpm[889] = {
    71,73,70,56,57,97,16,0,16,0,247,0,0,5,5,5,133,133,133,197,197,197,251,251,
    251,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,33,
    249,4,1,0,0,255,0,44,0,0,0,0,16,0,16,0,64,8,86,0,255,9,28,72,176,160,192,0,
    2,6,40,92,200,48,0,128,131,2,0,72,156,72,209,225,193,0,24,51,106,196,248,240,
    223,198,143,25,33,130,212,216,17,33,195,147,3,44,26,92,201,178,229,64,132,2,
    98,202,156,169,18,33,69,137,3,0,228,172,153,16,229,66,158,62,127,150,236,25,
    84,229,205,163,19,93,174,12,8,0,59};

static const char * document_xpm[] = {
    "16 16 4 1",
    "   c None",
    ".  c #000000",
    "+  c #FFFFFF",
    "@  c #808080",
    "                ",
    "  ........      ",
    "  .+++++.@.     ",
    "  .+++++.+@.    ",
    "  .+++++.++@.   ",
    "  .+++++.....@  ",
    "  .++++++@@@.@  ",
    "  .+++++++++.@  ",
    "  .+++++++++.@  ",
    "  .+++++++++.@  ",
    "  .+++++++++.@  ",
    "  .+++++++++.@  ",
    "  .+++++++++.@  ",
    "  ...........@  ",
    "   @@@@@@@@@@@  ",
    "                "};

static const char * folder_xpm[] = {
    "16 16 5 1",
    "   c None",
    ".  c #FFE79C",
    "+  c #C6864A",
    "@  c #FFC78C",
    "#  c #000000",
    "                ",
    "                ",
    "    ...+        ",
    "   @.@@@+       ",
    "  @@@@@@@@@@@@  ",
    " @@...........# ",
    " @.@@@@@@@@@@+# ",
    " @.@@@@@@@@@@+# ",
    " @.@@@@@@@@@@+# ",
    " @.@@@@@@@@@@+# ",
    " @.@@@@@@@@@@+# ",
    " @.@@@@@@@@@@+# ",
    " @.+++++++++++# ",
    "  ############# ",
    "                ",
    "                "};

//static const Fl_Pixmap executablePixmap(exec_xpm);
static const Fl_Image executablePixmap(exec_xpm, sizeof(exec_xpm));
static const Fl_Pixmap folderPixmap(folder_xpm);
static const Fl_Pixmap documentPixmap(document_xpm);

// read the folder() and move item into the first entry
bool Fl_IMAP_DS::open() {
    clear();

    // Connect to the server
    m_imap.cmd_login(m_user,m_password);

    // Select the mail box
    int total_messages, first_message = 1;
    m_imap.cmd_select(m_folder,total_messages);

    if (m_msgid) {
        first_message = m_msgid;
        total_messages = m_msgid;
    }
    if (total_messages) {
        if (m_callback)
            m_callback(total_messages,0);
        for (int msg_id = first_message; msg_id <= total_messages; msg_id++) {
            Fl_Data_Fields   *df = new Fl_Data_Fields;

            df->user_data((void *)msg_id);

            if (m_fetchbody)
                m_imap.cmd_fetch_message(msg_id,*df);
            else    m_imap.cmd_fetch_headers(msg_id,*df);

            m_list.append(df);

            if (m_callback)
                m_callback(total_messages,msg_id);
        }
        if (m_callback)
            m_callback(total_messages,total_messages);
    } else {
        if (m_callback)
            m_callback(100,100);
    }

    first();

    m_imap.cmd_logout();
    m_imap.close();

    m_eof = m_list.count() == 0;

    return !m_eof;
}
