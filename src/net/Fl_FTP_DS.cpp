/***************************************************************************
            Fl_FTP_DS.cpp  -  description
                                                                                                                                                                                                                                                                                                                                                           -------------------
            begin                : Thu Nov 28 2002
            copyright            : (C) 2002 by Alexey Parshin
            email                : alexeyp@m7.tts-sf.com
***************************************************************************/

#include <config.h>

#include <efltk/net/Fl_FTP_DS.h>
#include <efltk/Fl_Exception.h>
#include <efltk/Fl_Pixmap.h>

#include <ctype.h>
#include <stdlib.h>

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

static char *next_dir_item(char *p,char **result) {
    char *start = p;
    for (; *start == ' '; start++);
    *result = start;
    start = (char *) strchr(start,' ');
    *start = 0;
    return start + 1;
}

static const Fl_String_List
month_names("Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Nov|Dec","|");

static Fl_Data_Fields *parse_file_info_string(Fl_String& file_info) {
    char *ptr = (char *) file_info.c_str();

    char *permissions = 0L;
    char *refcount = 0L;
    char *user_name = 0L;
    char *group_name = 0L;
    char *size = 0L;
    char *month = 0L, *day = 0L, *year = 0L, *date = 0L, *time = 0L;
    char *file_name = 0L;
    bool  is_directory = false;
    bool  is_executable = false;

    Fl_Date_Time dt;
    const Fl_Image *pixmapPtr = &documentPixmap;

    ptr = next_dir_item(ptr,&permissions);

    if (isdigit(*ptr)) {
        // MS Dos style
        date = ptr;
        ptr = next_dir_item(ptr,&time);
        ptr = next_dir_item(ptr,&size);
        if (strstr(size,"DIR"))
            is_directory = true;
        time[2] = 0;
        time[5] = 0;
        int month = atoi(time);
        int day = atoi(time+3);
        int year = atoi(time+6);
        fl_try {
            Fl_Date_Time dosDate(year,month,day);
            dt = dosDate;
        }
        fl_catch(exc) {
        }
    } else {
        // Unix style
        if (permissions[0] == 'd')
            is_directory = true;
        else if (strchr(permissions,'x'))
            is_executable = true;
        ptr = next_dir_item(ptr,&refcount);
        ptr = next_dir_item(ptr,&user_name);
        ptr = next_dir_item(ptr,&group_name);
        ptr = next_dir_item(ptr,&size);
        ptr = next_dir_item(ptr,&month);
        ptr = next_dir_item(ptr,&day);
        ptr = next_dir_item(ptr,&year);
        int m = month_names.index_of(month) + 1;
        if (m >= 0) {
            int d = atoi(day);
            int y = atoi(year);
            fl_try {
                Fl_Date_Time unixDate(y,m,d);
                dt = unixDate;
            }
            fl_catch(exc) {
            }
        }
    }

    if (is_directory)
        pixmapPtr = &folderPixmap;
    else if (is_executable)
        pixmapPtr = &executablePixmap;

    // skip to the file name
    for (; *ptr == ' '; ptr++);
    file_name = ptr;

    Fl_Data_Fields *df = new Fl_Data_Fields;

    df->add("")         = pixmapPtr;
    df->add("Name")     = file_name;
    df->add("Size")     = atoi(size);
    df->add("Modified") = dt;

    df->field(0).width = 3;
    df->field(1).width = 30;
    df->field(2).width = 10;
    df->field(2).flags = FL_ALIGN_RIGHT;
    df->field(3).width = 16;

    return df;
}

// read the folder() and move item into the first entry
bool Fl_FTP_DS::open() {
    clear();

   // Connect to the server
    m_ftp.host(m_host,m_port);
    m_ftp.user(m_user);
    m_ftp.password(m_password);
    m_ftp.open();

   // Select the folder
    if (m_folder.length())
        m_ftp.cmd_cd(m_folder);

    Fl_String_List dirlist;
    m_ftp.cmd_list(dirlist);
    //dirlist.print();

    if (dirlist.count()) {
        unsigned cnt = dirlist.count();
        if (m_callback)
            m_callback(cnt,0);
        for (unsigned i = 0; i < cnt; i++) {
            Fl_Data_Fields *df = parse_file_info_string(dirlist[i]);
            if (df)
                m_list.append(df);

            if (m_callback)
                m_callback(cnt,i);
        }
    }

    if (m_callback)
        m_callback(100,100);

    first();

    m_ftp.cmd_quit();
    m_ftp.close();

    m_eof = m_list.count() == 0;

    return !m_eof;
}
