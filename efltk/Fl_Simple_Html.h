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

#ifndef _FL_SIMPLE_HTML_H_
#define _FL_SIMPLE_HTML_H_

#include <stdio.h>

#include <efltk/Fl.h>
#include <efltk/Fl_Group.h>
#include <efltk/Fl_Scrollbar.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl_Image.h>
#include <efltk/Fl_Image_Cache.h>

//
// Fl_Help_Func type - link callback function for files...
//
typedef const char *(Fl_Help_Func)(Fl_Widget *, const char *);

//
// Fl_Help_Block structure...
//
struct Fl_Help_Block
{
    const char *start,		// Start of text
               *end;		// End of text
    uchar border;		// Draw border?
    Fl_Color bgcolor;	// Background color
    int	x,		// Indentation/starting X coordinate
        y,		// Starting Y coordinate
        w,		// Width
        h;		// Height
    int	line[32];	// Left starting position for each line
};

//
// Fl_Help_Link structure...
//

struct Fl_Help_Link
{
    char filename[192],	// Reference filename
    name[32];	// Link target (blank if none)
    int	x,		// X offset of link text
        y,		// Y offset of link text
        w,		// Width of link text
        h;		// Height of link text
};

//
// Fl_Help_Target structure...
//

struct Fl_Help_Target
{
    char name[32];	// Target name
    int	 y;		// Y offset of target
};

//
// Fl_Simple_Html class...
//

class Fl_Simple_Html : public Fl_Group	//// Help viewer widget
{
    Fl_Image_Cache cache; //Image cache

    enum { RIGHT = -1, CENTER, LEFT };	// Alignments

    char title_[1024];		// Title string
    Fl_Color defcolor_,		// Default text color
        bgcolor_,		// Background color
    textcolor_,		// Text color
    linkcolor_;		// Link color
    Fl_Font	textfont_;		// Default font for text
    uchar textsize_;		// Default font size

    const char	*value_;		// HTML text value

    int	nblocks_,		// Number of blocks/paragraphs
        ablocks_;		// Allocated blocks
    Fl_Help_Block *blocks_;		// Blocks

    int	nfonts_;		// Number of fonts in stack
    Fl_Font		fonts_[100];		// Font stack
    uchar		fontss_[100];		// sizes

    Fl_Help_Func *link_;			// Link transform function

    int	nlinks_,		// Number of links
        alinks_;		// Allocated links
    Fl_Help_Link *links_;		// Links

    int	ntargets_,		// Number of targets
        atargets_;		// Allocated targets
    Fl_Help_Target *targets_;		// Targets

    char	directory_[1024];	// Directory for current file
    char	filename_[1024];	// Current filename
    char	prevfilename_[1024];	// Prev filename

    int		topline_,		// Top line in document
        leftline_,		// Lefthand position
    size_,			// Total document length
    hsize_;			// Maximum document width

    Fl_Scrollbar	scrollbar_,		// Vertical scrollbar for document
        hscrollbar_;		// Horizontal scrollbar

    Fl_Help_Block *add_block(const char *s, int xx, int yy, int ww, int hh, uchar border = 0);
    void		add_link(const char *n, int xx, int yy, int ww, int hh);
    void		add_target(const char *n, int yy);
    static int	compare_targets(const Fl_Help_Target *t0, const Fl_Help_Target *t1);
    int			do_align(Fl_Help_Block *block, int line, int xx, int a, int &l);
    void		draw();
    void		format();
    void		format_table(int *table_width, int *columns, const char *table);
    int			get_align(const char *p, int a);
    const char	*get_attr(const char *p, const char *n, char *buf, int bufsize);
    Fl_Color	get_color(const char *n, Fl_Color c);
    Fl_Image	*get_image(const char *name, int W, int H);
    int			get_length(const char *l);
    int			handle(int);

    void initfont(Fl_Font &f, uchar &s) {
        nfonts_ = 0;
        fl_font(f = fonts_[0] = textfont_, s = fontss_[0] = textsize_);
    }
    void pushfont(Fl_Font f, uchar s) {
        if (nfonts_ < 99) nfonts_ ++;
        fl_font(fonts_[nfonts_] = f, fontss_[nfonts_] = s);
    }
    void popfont(Fl_Font &f, uchar &s) {
        if (nfonts_ > 0) nfonts_ --;
        fl_font(f = fonts_[nfonts_], s = fontss_[nfonts_]);
    }

public:

    Fl_Simple_Html(int xx, int yy, int ww, int hh, const char *l = 0);
    ~Fl_Simple_Html();
    const char	*directory() const {
        if (directory_[0]) return (directory_);
        else return ((const char *)0);
    }
    const char	*filename() const {
        if (filename_[0]) return (filename_);
        else return ((const char *)0);
    }
    const char	*prev_filename() const {
        if (prevfilename_[0]) return (prevfilename_);
        else return ((const char *)0);
    }
    void		link(Fl_Help_Func *fn) { link_ = fn; }
    int			load(const char *f);
    void		layout();
    int			size() const { return (size_); }
    void		textcolor(Fl_Color c) { if(textcolor_ == defcolor_) textcolor_ = c; defcolor_ = c; }
    Fl_Color	textcolor() const { return (defcolor_); }
    void		textfont(Fl_Font f) { textfont_ = f; format(); }
    Fl_Font		textfont() const { return (textfont_); }
    void		textsize(uchar s) { textsize_ = s; format(); }
    uchar		textsize() const { return (textsize_); }
    const char	*title() { return (title_); }
    void		topline(const char *n);
    void		topline(int);
    int			topline() const { return (topline_); }
    void		leftline(int);
    int			leftline() const { return (leftline_); }
    void		value(const char *v);
    const char	*value() const { return (value_); }
};

#endif
