#include <efltk/Fl_ProgressBar.h>
#include <stdio.h>

Fl_ProgressBar::Fl_ProgressBar(int x, int y, int w, int h, const char *lbl)
    : Fl_Widget(x,y,w,h,lbl)
{
    mMin = mPresent = 0;
    mMax = 100;
    mShowPct = true;
    box(FL_DOWN_BOX);
    selection_color(FL_BLUE);
    color(FL_WHITE);
    textcolor(FL_RED);
}

void Fl_ProgressBar::draw()
{
    int bdx, bdy;
    double pct;
    if(damage() & FL_DAMAGE_ALL) draw_box();

    int X = 0, Y = 0;
    bdx = box()->dx();
    bdy = box()->dy();

    fl_color(selection_color());
    if(mPresent > mMax)
        mPresent = mMax;
    if(mPresent < mMin)
        mPresent = mMin;
    pct = (mPresent - mMin) / mMax;
    fl_rectf(X + bdx, Y + bdy, (int)(((double)w() - 2*bdx) * pct), h() - (2*bdy + 1));
    if(mShowPct)
    {
        char buffer[30];
        sprintf(buffer, "%d%%", (int) (pct * 100));
        fl_color(textcolor());
        fl_font(this->label_font(), this->label_size());
        fl_draw(buffer, X + (w() - fl_width(buffer))/2, Y + fl_height() + (((h() - 2*bdy) - fl_height())/2));
    }
}
