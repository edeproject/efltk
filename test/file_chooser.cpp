#include <efltk/Fl.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Menu_Button.h>
#include <efltk/Fl_Browser.h>
#include <efltk/Fl_Renderer.h>
#include <efltk/Fl_Images.h>
#include <efltk/Fl_File_Dialog.h>

#include <efltk/Fl_Locale.h>

Fl_Browser *list;

char file_types[] = "All Files, *, C++ Files, *.{cpp|cxx|C}, Header Files, *.{h|H|hpp}, Text Files, *.txt";

void sel(Fl_Widget *, void *)
{
    char **files = (char **)fl_select_files(0, file_types);
    if(files) {
        list->clear();
        list->begin();
        for(int a=0; files[a]!=0; a++) {
            if(files[a]) {
                Fl_Item *i = new Fl_Item();
                i->copy_label(files[a]);
                delete []files[a];
            }
        }

        list->end();
        list->relayout();
    }
}

void sel1(Fl_Widget *, void *)
{
    char *file = (char *)fl_select_file(0, file_types);
    if(file) {
        list->clear();
        list->begin();
        Fl_Item *i = new Fl_Item();
        i->copy_label(file);
        delete []file;
        list->end();
        list->relayout();
    }
}

void dir(Fl_Widget *, void *)
{
    char *dir = (char *)fl_select_dir();
    if(dir) {
        list->clear();
        list->begin();
        Fl_Item *i = new Fl_Item();
        i->copy_label(dir);
        delete []dir;
        list->end();
        list->relayout();
    }
}

void save(Fl_Widget *, void *)
{
	char *file = (char *)fl_save_file(0, file_types);
    if(file) {
        list->clear();
        list->begin();
        Fl_Item *i = new Fl_Item();
        i->copy_label(file);
        delete []file;
        list->end();
        list->relayout();
    }
}

#include <config.h>
int main()
{
    fl_init_locale_support("efltk", PREFIX"/share/locale");
    fl_init_images_lib();

    Fl_Window w(300,300,"FileDialog Test");
    w.begin();

    Fl_Button b1(10,10,50,40,"Select\nFiles");
    b1.callback(sel);

    Fl_Button b2(10,60,50,40,"Select\n1 File");
    b2.callback(sel1);

    Fl_Button b4(10, 110, 50,40,"Select\n Dir");
    b4.callback(dir);

    Fl_Button b3(10, 160, 50,40,"Save\n File");
    b3.callback(save);

    list = new Fl_Browser(70,10,220,280);
    list->end();

    w.resizable(list);
    w.show();
    w.end();

    return Fl::run();
}

