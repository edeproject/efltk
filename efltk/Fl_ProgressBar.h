#ifndef FL_PROGRESSBAR_H_
#define FL_PROGRESSBAR_H_

#include <efltk/Fl_Widget.h>
#include <efltk/Fl.h>
#include <efltk/fl_draw.h>

class FL_API Fl_ProgressBar : public Fl_Widget
{
protected:
    double mMin;
    double mMax;
    double mPresent;
    double mStep;
    bool mShowPct;
    Fl_Color mTextColor;
    void draw();

public:
    static Fl_Named_Style* default_style;

    Fl_ProgressBar(int x, int y, int w, int h, const char *lbl = 0);

    void range(double min, double max, double step = 1)  { mMin = min; mMax = max; mStep = step; };

    double minimum()	{ return mMin; }
    double maximum()	{ return mMax; }
    void minimum(double nm) { mMin = nm; };
    void maximum(double nm) { mMax = nm; };

    void step(double step)		{ mPresent += step; redraw(); };
    double step()		{ return mStep; }

    double position()	{ return mPresent; }
    void position(double pos) 	{ mPresent = pos; redraw(); }

    void showtext(bool st)	{ mShowPct = st; }
    bool showtext()		{ return mShowPct; }

    void textcolor(Fl_Color col)	{ mTextColor = col; }
    Fl_Color textcolor() 	{ return mTextColor; }
};

#endif

