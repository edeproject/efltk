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

#include "Fl_Browser.h"

class FL_API Fl_FileBrowser : public Fl_Browser
{
    const char	*directory_;
    uchar	iconsize_;
    const char	*pattern_;

    int		item_height(void *) const;
    int		item_width(void *) const;
    void       	item_draw(void *, int, int, int, int) const;
    int		incr_height() const { return (item_height(0)); }

public:
    Fl_FileBrowser(int, int, int, int, const char * = 0);

    uchar		iconsize() const { return (iconsize_); };
    void		iconsize(uchar s) { iconsize_ = s; redraw(); };

    void		directory(const char *directory) { load(directory); }
    const char	*directory(void) const { return (directory_); }

    void		filter(const char *pattern);
    const char	*filter() const { return (pattern_); };

    int		load(const char *directory);
};

#endif // !_FL_FILEBROWSER_H_

//
// End of "$Id$".
//
