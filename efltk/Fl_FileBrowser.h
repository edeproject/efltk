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
 * Author : Mikko Lahteenmaki
 * Email  : mikko@fltk.net
 *
 * Please report all bugs and problems to "efltk-bugs@fltk.net"
 *
 */

#ifndef _FL_FILEBROWSER_H_
#define _FL_FILEBROWSER_H_

#include "Fl_Util.h"
#include "Fl_ListView.h"
#include "Fl_ListView_Item.h"
#include "Fl_Directory_DS.h"

class FL_API Fl_File_Browser : public Fl_ListView
{
public:
    Fl_File_Browser(int x, int y, int w, int h, const char *label = 0);

    // Set match pattern files
    void pattern(const char *pattern) { m_dir_ds.pattern(pattern); load(directory()); }
    void pattern(const Fl_String &pattern) { m_dir_ds.pattern(pattern); load(directory()); }
    const Fl_String &pattern() const { return m_dir_ds.pattern(); }

    // Set files show policy, according to Fl_Directory_DS
    char showpolicy() const { return m_dir_ds.showpolicy(); }
    void showpolicy(char type) { m_dir_ds.showpolicy(type); }

    // Load and set directory
    int	load(const Fl_String &directory);
    int	load(const char *directory) { Fl_String dir(directory); return load(dir); }

    // Set new directory
    void directory(const char *directory) { load(directory); }
    void directory(const Fl_String &directory) { load(directory); }
    const Fl_String &directory() const { return m_dir_ds.directory(); }

    // Returns relative selected filename.
    const Fl_String &filename() const;
    // Returns absolute path of selected filename.
    Fl_String filename_full() const;

    // Go one dir up, and reload
    void up();

    // Returns pointer to item called "UP.."
    Fl_ListView_ItemExt *up_item() const { return m_up_item; }

    bool add_up_item() const { return m_add_up_item; }
    void add_up_item(bool val) { m_add_up_item = val; }

    // Backward compatibility:
    void filter(const char *pattern) { m_dir_ds.pattern(pattern); load(directory()); }
    const char *filter() const { return m_dir_ds.pattern(); };

    // Default callback
    static void default_callback(Fl_Widget *, void *);

private:
    bool m_add_up_item;
    Fl_ListView_ItemExt *m_up_item;
    Fl_Directory_DS m_dir_ds;
};

// Backward compatibility
typedef Fl_File_Browser Fl_FileBrowser;

#endif // !_FL_FILEBROWSER_H_

//
// End of "$Id$".
//
