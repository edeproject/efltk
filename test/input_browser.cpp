#include <efltk/Fl.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Input_Browser.h>

int main(int argc,char *argv[]) {
    Fl_Window   window(300,200,"Fl_Input_Browser test");
    window.layout_spacing(4);

    Fl_Input_Browser    inp1("Inp Browser 1");
    inp1.add("This|is|only|a|test");

    Fl_Input_Browser    inp2("Inp Browser 2");
    inp2.add("This|is|another|test");

    window.end();    
    window.show(argc,argv);
    Fl::run();
}
