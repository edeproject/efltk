#ifndef __FL_SPLIT_H__
#define __FL_SPLIT_H__

#include <efltk/Fl_Box.h>

class Fl_Split: public Fl_Box
{
      Fl_Widget * ref_;
      int dir_;
    public:
      Fl_Split(Fl_Widget * _ref_,int layout_size=5);
      int handle(int ev);
};

#endif

