//
// "$Id$"
//
// Fl_FileBrowser routines for the Fast Light Tool Kit (FLTK).
//
// Copyright 1997-1999 by Easy Software Products.
// Copyright 2003 by Mikko Lahteenmaki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//
// Contents:
//   Fl_FileBrowser::load()			- Load a directory into the browser.
//   Fl_FileBrowser::up()			- Up one directory, and load it

#include <config.h>
#include "../core/fl_internal.h"

#include <efltk/vsnprintf.h>
#include <efltk/Fl_FileBrowser.h>
#include <efltk/Fl_Pixmap.h>
#include <efltk/fl_ask.h>
#include <efltk/fl_draw.h>
#include <efltk/filename.h>
#include <efltk/fl_utf8.h>

#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
# include <windows.h>
# include <io.h>
# include <direct.h>
#else /* _WIN32 */
# include <unistd.h>
#endif

#ifdef _WIN32
static const char * datas_cd[] = {
"16 16 29 1",
" 	c None",
".	c #737173",
"+	c #9CCF9C",
"@	c #CECF63",
"#	c #C6C7C6",
"$	c #319E9C",
"%	c #63CF9C",
"&	c #B5B6B5",
"*	c #313031",
"=	c #CECF9C",
"-	c #DEDFDE",
";	c #848684",
">	c #319ECE",
",	c #639ECE",
"'	c #63CFCE",
")	c #D6D7D6",
"!	c #949694",
"~	c #A5A6A5",
"{	c #639E9C",
"]	c #000000",
"^	c #CECFCE",
"/	c #F7F7F7",
"(	c #E7E7E7",
"_	c #EFEFEF",
":	c #FFFFFF",
"<	c #CEFFFF",
"[	c #009ECE",
"}	c #00FF00",
"|	c #008600",
"        ...     ",
"      ..+@#..   ",
"     .$%+@&##*  ",
"    .%%$%=#&-&* ",
"    ;>,%';&)#&* ",
"   .!~{';];~&^^*",
"   .&&^;]/];^^^*",
"   .(/(&;];&_/^*",
" ;;;;~&~~;$-(:* ",
";:::.~~&)=%><&* ",
";:###.~&^=+[[]  ",
";:****;;^=+**]  ",
";:}|::##***#.]  ",
".;;;;;;;;;;;;]  ",
" ]]]]]]]]]]]]   ",
"                "};

static const char * datas_floppy[] = {
"16 16 11 1",
" 	c None",
".	c #848684",
"+	c #737173",
"@	c #9CFFFF",
"#	c #000000",
"$	c #FFFFFF",
"%	c #CEFFFF",
"&	c #CECFCE",
"*	c #C6C7C6",
"=	c #B5B6B5",
"-	c #FF0000",
"         ...... ",
"        +@@@@@@#",
"        +$$$$$##",
"        +$$$%%%#",
"        +%%%%%%#",
"        +&*&=*=#",
"  ......+*....*#",
" .******+&+#+$=#",
".$$$$$$$$###### ",
".*********-*.+# ",
".***....****.+# ",
".*..####...*.+# ",
".***$$$$****.+# ",
".............#  ",
" ############   ",
"                "};
static Fl_Pixmap cd_pix(datas_cd);
static Fl_Pixmap floppy_pix(datas_floppy);
#endif

static const char * datas_harddisk[] = {
"16 16 12 1",
" 	c None",
".	c #737173",
"+	c #B5B6B5",
"@	c #000000",
"#	c #FFFFFF",
"$	c #9C9E9C",
"%	c #D6D7D6",
"&	c #C6C7C6",
"*	c #00CF00",
"=	c #008600",
"-	c #949694",
";	c #DEDFDE",
"                ",
"                ",
"                ",
"                ",
"  ............. ",
" .++++++++++++.@",
".############$.@",
".%&&&&&&&+*=+-.@",
".;+&&&&&+++++-.@",
".;..........+-.@",
".%##########+-.@",
"..............@ ",
" @@@@@@@@@@@@@  ",
"                ",
"                ",
"                "};
static const char *up_xpm[] = {
"16 16 6 1",
" 	c None",
"*  c #000000",
".	c #FFE79C",
"+	c #C6864A",
"@	c #FFC78C",
"#	c #000000",
"                ",
"                ",
"    ...+        ",
"   @.@@@+       ",
"  @@@@@@@@@@@@  ",
" @@...*.......# ",
" @.@@***@@@@@+# ",
" @.@*****@@@@+# ",
" @.@@@*@@@@@@+# ",
" @.@@@*@@@@@@+# ",
" @.@@@*****@@+# ",
" @.@@@@@@@@@@+# ",
" @.+++++++++++# ",
"  ############# ",
"                ",
"                "};
static Fl_Pixmap up_pix(up_xpm);
static Fl_Pixmap hd_pix(datas_harddisk);
                    
// Define access mode constants if they aren't already defined.
#ifndef R_OK
# define R_OK 04
#endif

void Fl_File_Browser::default_callback(Fl_Widget *w, void *d)
{
    Fl_File_Browser *b = (Fl_File_Browser*)w;
    if(!b->item()) return;
    if(!Fl::event_clicks() && Fl::event_key()!=FL_Enter) return;

    Fl_String dir(b->directory());

    if(b->item() != b->up_item()) {

        dir += b->item()->label(1);

        if(access(dir, R_OK)!=0) return;

        if(fl_is_dir(dir)) {
            b->load(dir);
            b->redraw();
        }

    } else {

        b->up();
    }
}

Fl_File_Browser::Fl_File_Browser(
	int        x,	// I - Upper-lefthand X coordinate
        int        y,   // I - Upper-lefthand Y coordinate
	int        w,   // I - Width in pixels
	int        h,   // I - Height in pixels
	const char *l)  // I - Label text
: Fl_ListView(x, y, w, h, l)
{
	m_add_up_item = true;
	m_up_item = 0;

	callback(default_callback);
	when(FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE);
	data_source(&m_dir_ds);
}

#ifdef _WIN32

static uint get_dev_size(uint64 size, Fl_String &suffix)
{	
	if(size<1024) {
		suffix=_("bytes");
		return (uint)size;
	}
	if(size>1024) {
		size /= 1024;
		suffix=_("Kb");
	}
	if(size>1024) {
		size /= 1024;		
		suffix=_("Mb");
	}
	return (uint)size;
}

#endif

#ifdef _WIN32
static const char *types[] = {
    N_("Unknown"),
	
    N_("File"),
    N_("Dir"),
    N_("Link"),

    N_("CD-Rom"),
    N_("Removable"),
    N_("Local Disk"),
    N_("Network Disk"),
    N_("RAM Disk")
};
#endif

// 'Fl_FileBrowser::up()' - Up one directory, and load it
void Fl_File_Browser::up()
{
    if(directory().empty()) return;

    Fl_String dir(directory());
    // Remove last slash
    dir[dir.length()-1] = '\0';

    int pos = dir.rpos(slash);
    if(pos==-1) dir="";
    else dir = dir.sub_str(0, pos+1);

    redraw();
    load(dir);
}

// 'Fl_FileBrowser::load()' - Load a directory into the browser.
int                                         // O - Number of files loaded
Fl_File_Browser::load(const Fl_String &dir) // I - Directory to load
{	
    Fl_String old_dir(directory());
    directory(dir);

    clear();
    header()->clear();
    m_up_item = 0;

    if(dir.empty()) {
        header()->add_column("", 20);

        // No directory specified:
        //  - For UNIX list all mount points.
        //  - For Woe32 list all valid drive letters.

        //icon      = Fl_FileIcon::find("any", Fl_FileIcon::DEVICE);
        //if (icon == (Fl_FileIcon *)0)
        //	icon = Fl_FileIcon::find("any", Fl_FileIcon::DIR);

        begin();
        char filename[FL_PATH_MAX];
#ifdef _WIN32
        header()->add_column(_("File"), 100);
        header()->add_column(_("Type"), 100);
        header()->add_column(_("Capacity"), 100);
        header()->add_column(_("Free Space"), 100);

        // Drive available bits
        DWORD drives = GetLogicalDrives();
        for(int i = 'A'; i <= 'Z'; i ++, drives >>= 1) {
            if (drives & 1) {
                Fl_ListView_Item *item = new Fl_ListView_Item();
                item->image(&hd_pix);
                snprintf(filename, sizeof(filename)-1, "%c:\\", i);
                item->label(1, filename);

                Fl_File_Attr *attr = fl_file_attr(filename);
                if(attr->flags & Fl_File_Attr::DEVICE)
                {
                    uint type = GetDriveTypeA(filename);
                    char *typestr=_(types[0]);

                    if(type==DRIVE_CDROM)		{ typestr=_(types[4]); item->image(&cd_pix); }
                    else if(type==DRIVE_REMOVABLE)	{ typestr=_(types[5]); item->image(&floppy_pix); }
                    else if(type==DRIVE_FIXED)		typestr=_(types[6]);
                    else if(type==DRIVE_REMOTE)		typestr=_(types[7]);
                    else if(type==DRIVE_RAMDISK)	typestr=_(types[8]);

                    item->label(2, typestr);

                    uint s = 0;
                    Fl_String suffix;
                    if((s = get_dev_size(attr->capacity, suffix))>0) {
                        item->label(3, Fl_String(s)+" "+suffix);
                    }
                    if((s = get_dev_size(attr->free, suffix))>0) {
                        item->label(4, Fl_String(s)+" "+suffix);
                    }

                    /*
                     //TOO SLOW!!!
                     char drivename[255];
                     if(GetVolumeInformation(
                     filename, drivename, sizeof(drivename)-1,
                     NULL, NULL, NULL, NULL, 0))
                     {
                     if(drivename[0])
                     snprintf(fname, sizeof(fname)-1, "%s (%s)", filename, drivename);
                     }
                     */
                }

            }
        }
#else
        header()->add_column(_("File"), 100);
        header()->add_column(_("Device"), 100);
        header()->add_column(_("Type"), 100);

        FILE    *mtab = 0;      // /etc/mtab or /etc/mnttab file
        char    line[1024];     // Input line
        char	dev[256];		// Device name
        char	fstype[256];	// Filesystem type

        // Open the file that contains a list of mounted filesystems...
#  if defined(__hpux) || defined(__sun)
        // Fairly standard
        mtab = fl_fopen("/etc/mnttab", "r");
#  elif defined(__sgi) || defined(linux)
        // More standard
        mtab = fl_fopen("/etc/mtab", "r");
#  endif
        // Otherwise fallback to full list
        if(mtab == NULL) mtab = fl_fopen("/etc/fstab", "r");
        if(mtab == NULL) mtab = fl_fopen("/etc/vfstab", "r");

        if (mtab != NULL)
        {
            while (fgets(line, sizeof(line), mtab) != NULL)
            {
                if (line[0] == '#' || line[0] == '\n')
                    continue;
                if (sscanf(line, "%255s%4095s%255s", dev, filename, fstype) != 3)
                    continue;
                if(!strcasecmp(dev, "none"))
                    continue;

                Fl_ListView_Item *item = new Fl_ListView_Item();
                item->image(&hd_pix);
                item->label(1, filename);
                item->label(2, dev);
                item->label(3, fstype);
            }
            fclose(mtab);
        }
#endif // _WIN32
        end();
        return children();

    } else {

        fill(m_dir_ds);
        if(children()==0) {
            clear();
            header()->clear();

            header()->add_column("", 20);
            header()->add_column(_("Name"), 100);
            header()->add_column(_("Size"), 100);
            header()->add_column(_("Type"), 100);
            header()->add_column(_("Modified"), 100);

            if(add_up_item()) {
                m_up_item = new Fl_ListView_ItemExt(0, _("Up.."));
                m_up_item->image(0, &up_pix);
                insert(*m_up_item, 0);
            }

            return 0;
        }

        if(add_up_item()) {
            m_up_item = new Fl_ListView_ItemExt(0, _("Up.."));
            m_up_item->image(0, &up_pix);
            insert(*m_up_item, 0);
        }

        //I18N !! UHH, Pretty lame way.. :)
        if(header()->columns()>0) {
            for(uint n=0; n<header()->columns(); n++) {
                header()->column_label(n, _(header()->column_label(n)));
            }
        }
    }

    return children()-1;
}
