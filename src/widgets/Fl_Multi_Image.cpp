#include <efltk/Fl_Multi_Image.h>

void Fl_Multi_Image::measure(int& w, int& h)
{
    images[0]->measure(w,h);
}

void Fl_Multi_Image::_draw(int dx, int dy, int dw, int dh,
                           int sx, int sy, int sw, int sh,
                           Fl_Flags f)
{
    int which = 0;
    for (int i = 1; i < MAXIMAGES; i++) {
        if (!images[i]) break;
        // Test to make sure all the requested flags are on:
        if ((f & flags[i]) == flags[i]) {
            which = i;
        }
    }
    images[which]->draw(dx,dy,dw,dh,sx,sy,sw,sh,0);
}
