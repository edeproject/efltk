//
// Boxtype demo for eFLTK
//
// $Id$
//

#include <efltk/Fl.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Box.h>

int N = 0;
#define W 150
#define H 50
#define ROWS 7

Fl_Window *window;

void bt(const char *name, Fl_Boxtype type, int square=0)
{
    int x = N%4;
    int y = N/4;
    N++;
    x = x*W+10;
    y = y*H+10;
    Fl_Box *b = new Fl_Box(x,y,square ? H-20 : W-20,H-20,name);
    b->box(type);
    b->label_size(11);
    if (square) {
        b->align(FL_ALIGN_RIGHT);
    }
}

int main(int argc, char ** argv)
{
    window = new Fl_Window(4*W,ROWS*H);
    window->box(FL_FLAT_BOX);
    window->color(12);// light blue

    bt("FL_NO_BOX",FL_NO_BOX);
    bt("FL_FLAT_BOX",FL_FLAT_BOX);
    //  N += 2; // go to start of next row to line up boxes & frames
    bt("FL_ENGRAVED_BOX",FL_ENGRAVED_BOX);
    bt("FL_EMBOSSED_BOX",FL_EMBOSSED_BOX);

    //bt("FL_DIV_UP_BOX", FL_DIV_UP_BOX);
    //bt("FL_DIV_DOWN_BOX", FL_DIV_DOWN_BOX); WHERE IS THIS?!?!
    bt("FL_UP_BOX",FL_UP_BOX);
    bt("FL_DOWN_BOX",FL_DOWN_BOX);
    bt("FL_THIN_UP_BOX",FL_THIN_UP_BOX);
    bt("FL_THIN_DOWN_BOX",FL_THIN_DOWN_BOX);

    bt("FL_BORDER_BOX",FL_BORDER_BOX);
    bt("FL_SHADOW_BOX",FL_SHADOW_BOX);
    bt("FL_ROUNDED_BOX",FL_ROUNDED_BOX);
    bt("FL_RSHADOW_BOX",FL_RSHADOW_BOX);
    bt("FL_RFLAT_BOX",FL_RFLAT_BOX);
    bt("FL_OVAL_BOX",FL_OVAL_BOX);
    bt("FL_OSHADOW_BOX",FL_OSHADOW_BOX);
    bt("FL_OFLAT_BOX",FL_OFLAT_BOX);
    bt("FL_ROUND_UP_BOX",FL_ROUND_UP_BOX);
    bt("FL_ROUND_DOWN_BOX",FL_ROUND_DOWN_BOX);
    bt("FL_DIAMOND_UP_BOX",FL_DIAMOND_UP_BOX);
    bt("FL_DIAMOND_DOWN_BOX",FL_DIAMOND_DOWN_BOX);
    bt("FL_PLASTIC_UP_BOX", FL_PLASTIC_UP_BOX);
    bt("FL_PLASTIC_DOWN_BOX", FL_PLASTIC_DOWN_BOX);

    bt("FL_VERT_SHADE_UP_BOX", FL_VERT_SHADE_UP_BOX);
    bt("FL_VERT_SHADE_FLAT_BOX", FL_VERT_SHADE_FLAT_BOX);

    bt("FL_HOR_SHADE_UP_BOX", FL_VERT_SHADE_UP_BOX);
    bt("FL_HOR_SHADE_FLAT_BOX", FL_VERT_SHADE_FLAT_BOX);

    bt("FL_DOTTED_FRAME", FL_DOTTED_FRAME);
    bt("FL_BORDER_FRAME", FL_BORDER_FRAME);

    window->resizable(window);
    window->end();
    window->show(argc,argv);

    return Fl::run();
}
