#ifndef FL_PROGRESSBAR_H_
#define FL_PROGRESSBAR_H_

#include <efltk/Fl_Widget.h>
#include <efltk/Fl.h>
#include <efltk/fl_draw.h>

class FL_API Fl_ProgressBar : public Fl_Widget
{
protected:
    float mMin, mMax;
    float mPresent, mStep;
    bool mShowPct;

public:
    static Fl_Named_Style* default_style;

    Fl_ProgressBar(int x, int y, int w, int h, const char *lbl = 0);

    void range(float min, float max, float step = 1)  { mMin = min; mMax = max; mStep = step; };

    float minimum()	{ return mMin; }
    float maximum()	{ return mMax; }
    void minimum(float nm) { mMin = nm; };
    void maximum(float nm) { mMax = nm; };

    void step(float step) { mPresent += step; redraw(); };
    float step()	  { return mStep; }

    void  value(float v) { mPresent = v; redraw(); }
    float value() const  { return mPresent; }

    void showtext(bool st) { mShowPct = st; }
    bool showtext()	   { return mShowPct; }

    virtual void draw();

    // Out-dated! use value() instead of these!
    float position()	     { return mPresent; }
    void position(float pos) { mPresent = pos; redraw(); }
};

#endif

