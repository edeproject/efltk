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

#ifndef _FL_TOOL_BAR_H_
#define _FL_TOOL_BAR_H_

#include "Fl_Bar.h"
#include "Fl_Button.h"
#include "Fl_Menu_Button.h"
#include "Fl_Divider.h"

class Fl_Tool_Button;

/**
 * Tool bar for eFLTK applications. Toolbar usually contains shortcuts to menu actions,
 * such as "Open File".
 * Items are normally represented as buttons, either normal or toggles.
 * However, it is possible to add any kind of widget to tool bar group.
 *
 * Fl_Tool_Bar provides simple interface for adding buttons.
 * It is recommended to use these functions, this way you can get
 * maximum usability for tool bar.
 */
class Fl_Tool_Bar : public Fl_Bar
{
public:
    /** Named style for toolbar. Name: "Tool Bar" */
    static Fl_Named_Style* default_style;

    /**
     * Size of toolbar button icons.
     */
    enum TbSize {
        TB_SIZE_SMALL = 0, ///< Small size, default small icon size is 20x20
        TB_SIZE_BIG,       ///< Big size, default big icon size is 32x32
        TB_SIZE_DEFAULT    ///< Select small/big regarding to system default.
    };

    /**
     * Creates new toolbar widget using the given position, size, and label string.
     */
    Fl_Tool_Bar(int x, int y, int w, int h, const char *label=0);

    /**
     * Creates new toolbar widget using the label, size, alignment, and label width.
     */
    Fl_Tool_Bar(const char* l = 0,int layout_size=30,Fl_Align layout_al=FL_ALIGN_TOP,int label_w=-1);

    /** Destructor */
    ~Fl_Tool_Bar();

    /**
     * Default callback for tool bar buttons. This sets 'button' to be
     * current item() of tool bar and makes this->do_callback()
     */
    static void default_callback(Fl_Widget *button, void *arg);

    /**
     * Add normal button to tool bar.
     * @param image Button image
     * @param id argument for button, usually unique for each button.
     * @param label Label of button
     * @param tip Tooltip of button
     */
    Fl_Tool_Button *add_button(Fl_Image *image, long id, const char *label=0, const char *tip=0);
    /**
     * Add normal button to tool bar.
     * @param label Label of button
     * @param tip Tooltip of button
     * @param image Button image
     * @param cb Callback for button. If NULL, Fl_Tool_Bar::default_callback is used.
     * @param data User data for this button
     */
    Fl_Tool_Button *add_button(const char *label, const char *tip, Fl_Image *image=0, Fl_Callback *cb=0, void *data=0);

    /**
     * Add toggle button to tool bar.
     * @param image Button image
     * @param id argument for button, usually unique for each button.
     * @param label Label of button
     * @param tip Tooltip of button
     */
    Fl_Tool_Button *add_toggle(Fl_Image *image, long id, const char *label=0, const char *tip=0);
    /**
     * Add toggle button to tool bar.
     * @param label Label of button
     * @param tip Tooltip of button
     * @param image Button image
     * @param cb Callback for button. If NULL, Fl_Tool_Bar::default_callback is used.
     * @param data User data for this button
     */
    Fl_Tool_Button *add_toggle(const char *label, const char *tip, Fl_Image *image=0, Fl_Callback *cb=0, void *data=0);

    /**
     * Add divider to tool bar.
     */
    Fl_Divider *add_divider();

    /** Returns current item, this should be used ONLY is Fl_Tool_Bar::callback function */
    Fl_Widget *item() const { return m_item; }
    /** Set current item, used internally. */
    void item(Fl_Widget *i) { m_item = i; }

    /** void Fl_Widget::draw() */
    virtual void draw();

    /** void Fl_Widget::layout() */
    virtual void layout();

    /** int Fl_Widget::handle(int event) */
    virtual int handle(int ev);

    /** Returns preferred size for tool bar, regarding to its state. */
    virtual void preferred_size(int &w, int &h) const;

    /** Default open/close glyph */
    static void button_glyph(const Fl_Widget* widget, int glyph, int x,int y,int w,int h, Fl_Flags flags);

    /**
     * This function is obsolete, you should use layout_spacing() instead.
     * Spacing between items.
     */
    int spacing() const { return layout_spacing(); }
    /**
     * This function is obsolete, you should use layout_spacing() instead.
     * Set spacing between items.
     */
    void spacing(int v) { layout_spacing(v); }

    /**
     * Set default button sizes for ALL tool bars.
     * @see enum TbSize
     */
    static void set_icon_size(TbSize size, int w, int h) { m_icon_sizes[size][0] = w; m_icon_sizes[size][1] = h; }
    /**
     * Get default button sizes.
     * @see enum TbSize
     */
    static void get_icon_size(TbSize size, int &w, int &h) { w = m_icon_sizes[size][0]; h = m_icon_sizes[size][1]; }

    /**
     * Return current size mode.
     * @see enum TbSize
     */
    TbSize tb_size() const { return (m_tb_size==TB_SIZE_DEFAULT) ? default_tb_size() : m_tb_size; }
    /**
     * Set size mode.
     * @see enum TbSize
     */
    void tb_size(TbSize s) { m_tb_size = s; }

    /**
     * Return default size mode.
     * @see enum TbSize
     */
    static TbSize default_tb_size() { return m_tb_def_size; }
    /**
     * Set default size mode for ALL tool bars.
     * @see enum TbSize
     */
    static void default_tb_size(TbSize s) { m_tb_def_size = s; }

private:
    TbSize m_tb_size;
    static TbSize m_tb_def_size;
    static int m_icon_sizes[2][2];

    Fl_Widget *m_item;

    Fl_Menu_ *m_menu;
    Fl_Widget *m_menubut, *m_right;

    static void cb_menu(Fl_Widget *w, void *data);

    void ctor_init();
};

class Fl_Tool_Button : public Fl_Button
{
public:
    /** Named style for tool button. Name: "Tool Button" */
    static Fl_Named_Style* default_style;

    /**
     * Text position modes.
     */
    enum TbTextPos {
        POS_BOTTOM = 1, ///< Text placed at bottom of the image
        POS_RIGHT,      ///< Text placed at right of the image
        POS_DEFAULT     ///< Default placement, regarding to system default.
    };

    /**
     * Text show modes.
     */
    enum TbShowMode {
        SHOW_TEXT = 1, ///< Show only text
        SHOW_IMAGE,    ///< Show only image
        SHOW_BOTH,     ///< Show both
        SHOW_AUTO,     ///< Shows image if available, otherwise label
        SHOW_DEFAULT   ///< Show text/image regarding to system default.
    };

    /** Create tool button for Fl_Tool_Bar 'bar' */
    Fl_Tool_Button(Fl_Tool_Bar *bar);
    virtual ~Fl_Tool_Button();

    /**
     * Create tool button woth given parameters.
     * @param bar parent Fl_Tool_Bar for button
     * @param image Button image
     * @param label Label of button
     * @param tip Tooltip of button
     * @param id argument for button, usually unique for each button.
     */
    static Fl_Tool_Button *create(Fl_Tool_Bar *bar, Fl_Image *image, const char *label, const char *tooltip, long id);

    /**
     * Create tool button woth given parameters.
     * @param bar parent Fl_Tool_Bar for button
     * @param image Button image
     * @param label Label of button
     * @param tip Tooltip of button
     * @param cb Callback for button. If NULL, Fl_Tool_Bar::default_callback is used.
     * @param data User data for this button
     */
    static Fl_Tool_Button *create(Fl_Tool_Bar *bar, Fl_Image *image, const char *label, const char *tooltip, Fl_Callback *cb, void *data);

    /** void Fl_Widget::draw() */
    virtual void draw();

    /** void Fl_Widget::layout() */
    virtual void layout();

    virtual void preferred_size(int &w, int &h) const;

    /**
     * Returns current show mode.
     */
    TbShowMode showmode() const { return m_showmode; }
    /**
     * Set current show mode.
     */
    void showmode(TbShowMode s) { m_showmode = s; }

    /**
     * Returns current text position mode
     */
    TbTextPos textpos() const { return m_textpos; }
    /**
     * Set current text position mode
     */
    void textpos(TbTextPos p) { m_textpos = p; }

    /**
     * Returns default show mode for tool buttons.
     */
    static TbShowMode default_showmode() { return m_def_showmode; }
    /**
     * Set default show mode for ALL tool buttons.
     */
    static void default_showmode(TbShowMode s) { m_def_showmode = s; }

    /**
     * Returns default text position mode for tool buttons.
     */
    static TbTextPos default_textpos() { return m_def_textpos; }
    /**
     * Set default text position mode for ALL tool buttons.
     */
    static void default_textpos(TbTextPos p) { m_def_textpos = p; }

private:
    Fl_Tool_Bar *m_bar;
    TbShowMode m_showmode;
    TbTextPos m_textpos;

    Fl_Image *small, *big;

    static TbShowMode m_def_showmode;
    static TbTextPos m_def_textpos;
};

#endif
