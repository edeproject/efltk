#include <efltk/Fl.h>
#include <efltk/Fl_Images.h>
#include <efltk/Fl_Help_Dialog.h>

#include <efltk/Fl_Locale.h>
#include <config.h>
int main(int  argc, char *argv[])
{
    fl_init_locale_support("efltk", PREFIX"/share/locale");
    fl_init_images_lib();

    Fl_Help_Dialog book(500, 400, "Help Book");

    if (argc < 2)
        book.load("index.html");
    else
        book.load(argv[1]);

    book.show();

    return Fl::run();
}
