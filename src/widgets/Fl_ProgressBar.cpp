#include <efltk/Fl_ProgressBar.h>
#include <stdio.h>

static void revert(Fl_Style *s) {
    s->box = FL_DOWN_BOX;
    s->button_box = FL_FLAT_BOX;
    s->button_color = FL_BLUE;
    s->text_color = FL_RED;
    s->color = FL_WHITE;
}

static Fl_Named_Style style("ProgressBar", revert, &Fl_ProgressBar::default_style);
Fl_Named_Style* Fl_ProgressBar::default_style = &::style;

// Traditional ctor
Fl_ProgressBar::Fl_ProgressBar(int x, int y, int w, int h, const char *lbl)
: Fl_Widget(x,y,w,h,lbl)
{
    style(default_style);
    mMin = mPresent = 0;
    mMax = 100;
    mShowPct = true;
}

// New style ctor
Fl_ProgressBar::Fl_ProgressBar(const char* l,int layout_size,Fl_Align layout_al,int label_w)
: Fl_Widget(l,layout_size,layout_al,label_w)
{
    style(default_style);
    mMin = mPresent = 0;
    mMax = 100;
    mShowPct = true;
}

void Fl_ProgressBar::draw()
{
    int bdx, bdy;
    float pct;
    if(damage() & FL_DAMAGE_ALL) draw_box();

    bdx = box()->dx();
    bdy = box()->dy();

    if(mPresent > mMax)
        mPresent = mMax;
    if(mPresent < mMin)
        mPresent = mMin;
    pct = (mPresent - mMin) / mMax;

    button_box()->draw(bdx, bdy, int(((float)w() - 2*bdx) * pct), h()-box()->dh(), button_color(), 0);
    if(mShowPct)
    {
        char buffer[30];
        sprintf(buffer, "%d%%", (int) (pct * 100));
        fl_color(text_color());
        fl_font(text_font(), float(text_size()));
        fl_draw(buffer, 0, 0, w(), h(), FL_ALIGN_CENTER);
    }
}
