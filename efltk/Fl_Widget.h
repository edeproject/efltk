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

#ifndef _FL_WIDGET_H_
#define _FL_WIDGET_H_

#include "Fl_Style.h"
#include "Fl_Exception.h"
#include "Fl_Data_Source.h"

class FL_API Fl_Widget;
class FL_API Fl_Window;
class FL_API Fl_Image;
class FL_API Fl_Group;
class FL_API Fl_Device;

typedef void (Fl_Callback )(Fl_Widget*, void*);
typedef Fl_Callback* Fl_Callback_p; // needed for BORLAND
typedef void (Fl_Callback0)(Fl_Widget*);
typedef void (Fl_Callback1)(Fl_Widget*, long);

/** 
 * Fl_Widget is the base class for all widgets in FLTK. You can't create one 
 * of these because the constructor is not public. However you can subclass it.

 * Unless otherwise noted, the property setting methods such as  color(n) 
 * or label(s) do not call redraw(), even if they change the widget's appearance. 
 * This is to make the setting of several properties faster and to allow most 
 * of them to be small inline functions. It is up to the calling program to call 
 * redraw() after changing any visible properties.
 */
class FL_API Fl_Widget {
    friend class Fl_Device;
public:
    /// values for widget_type()                        
    enum {
        RESERVED_TYPE = 0x64,       /**< Widget is reserved type */
        GROUP_TYPE  = 0xe0,         /**< Widget is group type */
        WINDOW_TYPE = 0xf0          /**< Widget is window type */
    };

    uchar   widget_type()       {return widget_type_; }
    void    widget_type(uchar t){widget_type_ = t;}
    bool    is_group() const    {return widget_type_ >= GROUP_TYPE;}
    bool    is_window() const   {return widget_type_ >= WINDOW_TYPE;}

    uchar   type() const        {return type_;}
    void    type(uchar t)       {type_ = t;}

    virtual void draw();
    virtual int  handle(int);
    virtual void layout();
    virtual void preferred_size(int& w, int& h) const;

    virtual ~Fl_Widget();
    int send(int event);

    static Fl_Named_Style* default_style;
    const Fl_Style* style() const {return style_;}
    void    style(const Fl_Style* s) {style_ = s;}
    void    style(const Fl_Style& s) {style_ = &s;}
    bool    copy_style(const Fl_Style* s);

    static void default_glyph(const Fl_Widget*,int,int,int,int,int,Fl_Flags);

    Fl_Group* parent() const    {return parent_;}
    void    parent(Fl_Group* w) {parent_ = w;}
    Fl_Window* window() const;

    int     x() const       {return x_;}
    void    x(int v)        {x_ = v;}
    int     y() const       {return y_;}
    void    y(int v)        {y_ = v;}
    int     w() const       {return w_;}
    void    w(int v)        {w_ = v;}
    int     width();
    int     h() const       {return h_;}
    void    h(int v)        {h_ = v;}
    int     height();
    bool    resize(int,int,int,int) ;
    bool    position(int X,int Y)   { return resize(X,Y,w_,h_);}
    bool    size(int W,int H)   { return resize(x_,y_,W,H);}

    const Fl_String &label() const  { return label_; }
    void    label(const Fl_String &l) { label_ = l; }
    void    label(const char *l)      { label_ = l ? l : ""; }
    void    copy_label(const char *a) { label(a); }
    void    copy_label(const Fl_String &a) { label(a); }

    /// By default, label has no width limit
    void    label_width(int lw) { label_width_=lw; }
    int     label_width() const { return label_width_; }
    int     label_height() const;
    void    measure_label(int& w, int& h) const;    

    const Fl_String &tooltip() const   { return tooltip_; }
    void    tooltip(const char *t)       { tooltip_ = t ? t : ""; }
    void    tooltip(const Fl_String &t)  { tooltip_ = t; }

    const Fl_String &field_name() const  { return field_name_; }
    void    field_name(const char *f)      { field_name_ = f ? f : ""; }
    void    field_name(const Fl_String &f) { field_name_ = f; }

    Fl_Image* image() const { return image_; }
    void    image(Fl_Image* a)  { image_ = a; }
    void    image(Fl_Image& a)  { image_ = &a; }

    int shortcut() const        {return shortcut_;}
    void shortcut(int s)        {shortcut_ = s;}  

    Fl_Callback_p callback() const { return callback_; }
    void    callback(Fl_Callback* c, void* p) { callback_=c; user_data_=p; }
    void    callback(Fl_Callback* c) { callback_=c; }
    void    callback(Fl_Callback0*c) { callback_=(Fl_Callback*)c; }
    void    callback(Fl_Callback1*c, long p=0) { callback_=(Fl_Callback*)c; user_data_=(void*)p; }  

    void*   user_data() const   { return user_data_; }
    void    user_data(void* v)  { user_data_ = v; }
    long    argument() const    { return (long)user_data_; }
    void    argument(long v)    { user_data_ = (void*)v; }
    uchar   when() const        { return when_; }
    void    when(uchar i)       { when_ = i; }
    void    event(uchar e)      { event_ = e; }
    uchar   event()             { return event_; }

    static void default_callback(Fl_Widget*, void*);
    void    do_callback(uchar event) { do_callback(this, user_data_, event);}
    void    do_callback(Fl_Widget* o, void* arg, uchar event);
    void    do_callback(Fl_Widget* o, long arg, uchar event);
    int     test_shortcut() const   ;
    bool    contains(const Fl_Widget*) const;
    bool    inside(const Fl_Widget* o) const {return o && o->contains(this);}
    bool    pushed() const      ;
    bool    focused() const     ;
    bool    belowmouse() const  ;

    Fl_Flags layout_align()     { return layout_flags_; }
    void layout_align(Fl_Flags f) { layout_flags_ = f; }

    Fl_Flags flags() const      {return flags_;}
    Fl_Flags flags(Fl_Flags f)  {return flags_ = f;}
    Fl_Flags set_flag(int c)    {return flags_ |= c;}
    Fl_Flags clear_flag(int c)  {return flags_ &= ~c;}
    Fl_Flags invert_flag(int c) {return flags_ ^= c;}

    Fl_Flags align() const      {return flags_&FL_ALIGN_MASK;}
    void    align(unsigned a)   {flags_ = (flags_ & (~FL_ALIGN_MASK)) | a;}
    bool    visible() const     {return !(flags_&FL_INVISIBLE);}
    bool    visible_r() const   ;
    void    show()          ;
    void    hide()          ;
    void    set_visible()       {flags_ &= ~FL_INVISIBLE;}
    void    clear_visible()     {flags_ |= FL_INVISIBLE;}
    bool    active() const      {return !(flags_&FL_INACTIVE);}
    bool    active_r() const    ;
    void    activate()      ;
    void    activate(int b)     {if (b) activate(); else deactivate();}
    void    deactivate()        ;
    bool    output() const      {return (flags_&FL_OUTPUT)!=0;}
    void    set_output()        {flags_ |= FL_OUTPUT;}
    void    clear_output()      {flags_ &= ~FL_OUTPUT;}
    bool    takesevents() const {return !(flags_&(FL_OUTPUT|FL_INVISIBLE|FL_INACTIVE));}
    bool    changed() const     {return (flags_&FL_CHANGED)!=0;}
    void    set_changed()       {flags_ |= FL_CHANGED;}
    void    clear_changed()     {flags_ &= ~FL_CHANGED;}
    bool    value() const       {return (flags_&FL_VALUE)!=0;}
    void    set_value()         {flags_ |= FL_VALUE;}
    void    clear_value()       {flags_ &= ~FL_VALUE;}
    bool    selected() const    {return (flags_&FL_SELECTED)!=0;}
    void    set_selected()      {flags_ |= FL_SELECTED;}
    void    clear_selected()    {flags_ &= ~FL_SELECTED;}
    bool    click_to_focus()    {return (flags_ & FL_CLICK_TO_FOCUS) != 0;}
    void    set_click_to_focus(){flags_ |= FL_CLICK_TO_FOCUS;}
    void    clear_click_to_focus()  {flags_ &= ~FL_CLICK_TO_FOCUS;}

    bool    take_focus();
    void    throw_focus();

    void    redraw();
    void    redraw(uchar c);
    void    redraw_label();
    void    redraw(int,int,int,int);
    uchar   damage() const      {return damage_;}
    void    set_damage(uchar c) {damage_ = c;} // should be called damage(c)

    void    relayout();
    void    relayout(uchar damage);
    uchar   layout_damage() const {return layout_damage_;}
    void    layout_damage(uchar c)  {layout_damage_ = c;}

    void    make_current() const;

    void    draw_frame() const;
    void    draw_box() const;
    void    draw_glyph(int t, int x,int y,int w,int h, Fl_Flags f) const { glyph()(this,t,x,y,w,h,f); }
    void    draw_label(int x,int y,int w,int h, Fl_Flags) const;
    void    draw_inside_label(int x,int y,int w,int h, Fl_Flags) const ;
    void    draw_inside_label() const;

    Fl_Boxtype  box()               const;
    Fl_Boxtype  button_box()        const;
    Fl_Boxtype  focus_box()         const;
    Fl_Glyph    glyph()             const;
    Fl_Font     label_font()        const;
    Fl_Font     text_font()         const;
    Fl_Labeltype label_type()       const;
    Fl_Color    color()             const;
    Fl_Color    label_color()       const;
    Fl_Color    selection_color()   const;
    Fl_Color    selection_text_color()  const;
    Fl_Color    button_color()      const;
    Fl_Color    highlight_color()   const;
    Fl_Color    highlight_label_color() const;
    Fl_Color    text_color()        const;
    unsigned    label_size()        const;
    unsigned    text_size()         const;
    unsigned    leading()           const;
    Fl_Flags    scrollbar_align()   const {return style()->scrollbar_align;}
    unsigned    scrollbar_width()   const {return style()->scrollbar_width;}

    void box(Fl_Boxtype);
    void button_box(Fl_Boxtype);
    void focus_box(Fl_Boxtype);
    void glyph(Fl_Glyph);
    void label_font(Fl_Font);
    void text_font(Fl_Font);
    void label_type(Fl_Labeltype);
    void color(Fl_Color);
    void label_color(Fl_Color);
    void selection_color(Fl_Color);
    void selection_text_color(Fl_Color);
    void button_color(Fl_Color);
    void highlight_color(Fl_Color);
    void highlight_label_color(Fl_Color);
    void text_color(Fl_Color a);
    void label_size(unsigned a);
    void text_size(unsigned a);
    void leading(unsigned a);

    // Data source support
    virtual bool load_data(Fl_Data_Source *ds) { return true; }
    virtual bool save_data(Fl_Data_Source *ds) const { return true; }

protected:
    /**
     * This is the protected constructor for an Fl_Widget, but all derived
     * widgets have a matching public constructor. It takes a value for
     * x(), y(), w() , h(), and an optional value for  label().
     */
    Fl_Widget(int,int,int,int,const char* =0);
    Fl_Widget(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=100);

private:
    // disable the copy assignment/constructors:
    Fl_Widget & operator=(const Fl_Widget &);
    Fl_Widget(const Fl_Widget &);

    void ctor_init(int,int,int,int,const char*);

    unsigned        flags_;
    int             shortcut_; // encode in the label?
    int             x_,y_,w_,h_;
    uchar           type_, widget_type_;
    uchar           damage_;
    uchar           layout_damage_, layout_flags_;
    uchar           when_;
    uchar           event_;

    Fl_String field_name_; // data source support
    Fl_String tooltip_; // make this into another widget?
    Fl_String label_;
    short label_width_;
    Fl_Image* image_;
    Fl_Group* parent_;
    const Fl_Style* style_;

    Fl_Callback *callback_;
    void *user_data_;  
};

#endif
