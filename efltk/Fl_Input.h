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

#ifndef _FL_INPUT_H_
#define _FL_INPUT_H_

#include "Fl_Widget.h"
#include "Enumerations.h"

/** Fl_Input */
class FL_API Fl_Input : public Fl_Widget {
public:
    enum { // values for type()
        NORMAL = 0,
    // this hole was used by float & int types
        SECRET = 3,
        MULTILINE = 4,
    // 5 and 6 not used now...
        INPUT_TYPE = 7,
        READ_ONLY = 8,
        WORDWRAP = 16,
    };

    /** Creates new input widget using the given position, size, and label string. */
    Fl_Input(int, int, int, int, const char* = 0);

    /** Creates new input widget using the label, size, alignment, and label width. */
    Fl_Input(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=100);

    /** Destructor */
    virtual ~Fl_Input();

    static Fl_Named_Style* default_style;

    int input_type() const {return type() & INPUT_TYPE; }
    void input_type(int t) { type(t | readonly()); }

    int text_align() const {return text_align_; }
    void text_align(int v){ text_align_ = v; }

    int readonly() const { return (type() & READ_ONLY); }
    void readonly(int b) { if (b) type(type() | READ_ONLY); else type(type() & ~READ_ONLY); }

    int wordwrap() const { return (type() & WORDWRAP); }
    void wordwrap(int b) { if (b) type(type() | WORDWRAP); else type(type() & ~WORDWRAP); }

    virtual void preferred_size(int& w, int& h) const;

    virtual void reset() { value(""); }

    virtual void draw();
    virtual void draw(int x, int y, int w, int h);
    virtual int handle(int);
    virtual int handle(int event, int x, int y, int w, int h);

    bool value(const char*);
    bool value(const char*, int);

    bool static_value(const char*);
    bool static_value(const char*, int);

    const char* value() const {return value_;}

    char index(int i) const {return value_[i];}
    int size() const {return size_;}
    int maximum_size() const { return maximum_size_; }
    void maximum_size(int m) { maximum_size_ = m; }

    // Data source support
    virtual bool load_data(Fl_Data_Source *ds);
    virtual bool save_data(Fl_Data_Source *ds);

    int position() const {return position_;}
    int mark() const {return mark_;}
    void position(int p, int m);
    void position(int p) {position(p, p);}
    void up_down_position(int position, bool extend);
    void mark(int m) { position(position(), m);}

    virtual bool replace(int, int, const char*, int);
    bool cut() {return replace(position(), mark(), 0, 0);}
    bool cut(int n) {return replace(position(), position()+n, 0, 0);}
    bool cut(int a, int b) {return replace(a, b, 0, 0);}
    bool insert(const char* t, int l=0){return replace(position_, mark_, t, l);}
    bool replace(int a, int b, char c) {return replace(a,b,&c,1);}
    bool copy(bool clipboard = true);
    bool undo();
    void maybe_do_callback();

    int word_start(int i) const;
    int word_end(int i) const;
    int line_start(int i) const;
    int line_end(int i) const;
    int mouse_position(int, int, int, int) const;
    int xscroll() const {return xscroll_;}
    int yscroll() const {return yscroll_;}

private:

    const char* value_;
    char* buffer;

    int size_;
    int maximum_size_;
    int bufsize;
    int position_;
    int mark_;
    int xscroll_, yscroll_;
    int mu_p;
    int inside_label_width;
    uchar text_align_;

    /** ctor initializer */
    void ctor_init();

    const char* expand(const char*, char*, int) const;
    float expandpos(const char*, const char*, const char*, int*) const;
    void minimal_update(int, int);
    void minimal_update(int p);
    void erase_cursor_at(int p);
    void put_in_buffer(int newsize);

    void setfont() const;

    bool handle_key();
    bool key_is_shortcut();
    void shift_position(int p);
    void shift_up_down_position(int p);

};

#endif
