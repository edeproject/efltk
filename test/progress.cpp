#include <efltk/Fl.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_ProgressBar.h>

Fl_Window* w;

static void ptimer(void *o)
{
    Fl_ProgressBar *pbar = (Fl_ProgressBar *)o;
    if(pbar->position() < 100)
    {
        pbar->step(1);
        Fl::add_timeout(0.1, ptimer, (void *)pbar);
    }
    else
        w->hide();
}

int main(int argc, char **argv)
{
    w = new Fl_Window(400, 100);

    Fl_ProgressBar* pbar = new Fl_ProgressBar(25, 25, 330, 25, "Simple Progress Bar");
    pbar->label_font(pbar->label_font()+1);
    pbar->box(FL_ENGRAVED_BOX);
    pbar->clear_flag(FL_ALIGN_MASK);
    pbar->set_flag(FL_ALIGN_BOTTOM);
    pbar->selection_color(FL_BLUE);
    pbar->color(FL_WHITE);
    pbar->textcolor(FL_RED);

    w->end();

    Fl::add_timeout(0.1, ptimer, (void *)pbar);
    w->show(argc, argv);
    return Fl::run();
}

