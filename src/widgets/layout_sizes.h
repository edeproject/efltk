/*
*
* $Author$
* $Revision$
* $Log$
* Revision 1.1  2003/04/19 21:43:07  parshin
* New module - should compute layout sizes and resize widget correctly in both - Fl_Split and Fl_Group.
*
*/

#ifndef __LAYOUT_SIZE_H__
#define __LAYOUT_SIZE_H__

void widget_layout_width(const Fl_Widget *w);
void widget_layout_height(const Fl_Widget *w);
void widget_layout_resize(Fl_Widget *w,int x,int y,int w,int h);

#endif
