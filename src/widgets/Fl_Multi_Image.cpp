#include <efltk/Fl_Multi_Image.h>

void Fl_Multi_Image::measure(int& w, int& h)
{
    images[0]->measure(w,h);
}

void Fl_Multi_Image::draw(int x, int y, int w, int h, Fl_Flags f)
{
    int which = 0;
    for (int i = 1; i < MAXIMAGES; i++) {
        if (!images[i]) break;
        // Test to make sure all the requested flags are on:
        if ((f & flags[i]) == flags[i]) {
            which = i;
        }
    }
    images[which]->draw(x,y,w,h,0);
}
